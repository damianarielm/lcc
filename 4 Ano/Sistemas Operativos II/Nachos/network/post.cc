/// Routines to deliver incoming network messages to the correct “address” --
/// a mailbox, or a holding area for incoming messages.
///
/// This module operates just like the US postal service (in other words, it
/// works, but it is slow, and you cannot really be sure if your mail really
/// got through!).
///
/// Note that once we prepend the `MailHdr` to the outgoing message data, the
/// combination (`MailHdr` plus data) looks like “data” to the Network
/// device.
///
/// The implementation synchronizes incoming messages with threads waiting
/// for those messages.
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "post.hh"


/// Initialize a single mail message, by concatenating the headers to
/// the data.
///
/// * `pktH` -- source, destination machine ID's.
/// * `mailH` -- source, destination mailbox ID's.
/// * `data` is the payload data.
Mail::Mail(PacketHeader pktH, MailHeader mailH, const char *msgData)
{
    ASSERT(msgData != nullptr);
    ASSERT(mailH.length <= MAX_MAIL_SIZE);

    pktHdr  = pktH;
    mailHdr = mailH;
    memmove(data, msgData, mailHdr.length);
}

/// Initialize a single mail box within the post office, so that it can
/// receive incoming messages.
///
/// Just initialize a list of messages, representing the mailbox.
MailBox::MailBox()
{
    messages = new SynchList<Mail *>;
}

/// De-allocate a single mail box within the post office.
///
/// Just delete the mailbox, and throw away all the queued messages in the
/// mailbox.
MailBox::~MailBox()
{
    delete messages;
}

/// Print the message header -- the destination machine ID and mailbox
/// #, source machine ID and mailbox #, and message length.
///
/// * `pktHdr` -- source, destination machine ID's.
/// * `mailHdr` -- source, destination mailbox ID's.
static void
PrintHeader(PacketHeader pktHdr, MailHeader mailHdr)
{
    printf("From (%d, %d) to (%d, %d) bytes %u\n",
           pktHdr.from, mailHdr.from, pktHdr.to, mailHdr.to, mailHdr.length);
}

/// Add a message to the mailbox.
///
/// If anyone is waiting for message arrival, wake them up!
///
/// We need to reconstruct the `Mail` message (by concatenating the headers
/// to the data), to simplify queueing the message on the `SynchList`.
///
/// * `pktHdr` -- source, destination machine ID's.
/// * `mailHdr` -- source, destination mailbox ID's.
/// * `data` is the payload message data.
void
MailBox::Put(PacketHeader pktHdr, MailHeader mailHdr, const char *data)
{
    ASSERT(data != nullptr);

    Mail *mail = new Mail(pktHdr, mailHdr, data);
    messages->Append(mail);  // Put on the end of the list of arrived
                             // messages, and wake up any waiters.
}

/// Get a message from a mailbox, parsing it into the packet header, mailbox
/// header, and data.
///
/// The calling thread waits if there are no messages in the mailbox.
///
/// * `pktHdr` is the address to put: source, destination machine ID's.
/// * `mailHdr` is the address to put: source, destination mailbox ID's.
/// * `data` is the address to put: payload message data.
void
MailBox::Get(PacketHeader *pktHdr, MailHeader *mailHdr, char *data)
{
    ASSERT(pktHdr != nullptr);
    ASSERT(mailHdr != nullptr);
    ASSERT(data != nullptr);

    DEBUG('n', "Waiting for mail in mailbox\n");
    Mail *mail = messages->Pop();  // Remove message from list;
                                   // will wait if list is empty.

    *pktHdr  = mail->pktHdr;
    *mailHdr = mail->mailHdr;
    if (debug.IsEnabled('n')) {
        printf("Got mail from mailbox: ");
        PrintHeader(*pktHdr, *mailHdr);
    }
    memmove(data, mail->data, mail->mailHdr.length);
      // Copy the message data into the caller's buffer.
    delete mail;  // We have copied out the stuff we need, we can now discard
                  // the message.
}

/// PostalHelper, ReadAvail, WriteDone
///
/// Dummy functions because C++ cannot indirectly invoke member functions.
/// The first is forked as part of the “postal worker” thread; the later two
/// are called by the network interrupt handler.
///
/// * `arg` is a pointer to the post office managing the `Network`.

static void
PostalHelper(void *arg)
{
    ASSERT(arg != nullptr);
    PostOffice *po = (PostOffice *) arg;
    po->PostalDelivery();
}

static void
ReadAvail(void *arg)
{
    ASSERT(arg != nullptr);
    PostOffice *po = (PostOffice *) arg;
    po->IncomingPacket();
}

static void
WriteDone(void *arg)
{
    ASSERT(arg != nullptr);
    PostOffice *po = (PostOffice *) arg;
    po->PacketSent();
}

/// Initialize a post office as a collection of mailboxes.
///
/// Also initialize the network device, to allow post offices on different
/// machines to deliver messages to one another.
///
/// We use a separate thread “the postal worker” to wait for messages to
/// arrive, and deliver them to the correct mailbox.  Note that delivering
/// messages to the mailboxes cannot be done directly by the interrupt
/// handlers, because it requires a `Lock`.
///
/// * `addr` is this machine's network ID.
/// * `reliability` is the probability that a network packet will be
///   delivered (e.g., `reliability = 1` means the network never drops any
///   packets; `reliability = 0` means the network never delivers any
///   packets).
/// * `nBoxes` is the number of mail boxes in this `PostOffice`.
PostOffice::PostOffice(NetworkAddress addr, double reliability, int nBoxes)
{
    ASSERT(nBoxes > 0);

    // First, initialize the synchronization with the interrupt handlers.
    messageAvailable = new Semaphore("message available", 0);
    messageSent      = new Semaphore("message sent", 0);
    sendLock         = new Lock("message send lock");

    // Second, initialize the mailboxes.
    netAddr  = addr;
    numBoxes = nBoxes;
    boxes    = new MailBox[nBoxes];

    // Third, initialize the network; tell it which interrupt handlers to
    // call.
    network = new Network(addr, reliability, ReadAvail, WriteDone, this);

    // Finally, create a thread whose sole job is to wait for incoming
    // messages, and put them in the right mailbox.
    Thread *t = new Thread("postal worker");

    t->Fork(PostalHelper, this);
}

/// De-allocate the post office data structures.
PostOffice::~PostOffice()
{
    delete network;
    delete [] boxes;
    delete messageAvailable;
    delete messageSent;
    delete sendLock;
}

/// Wait for incoming messages, and put them in the right mailbox.
///
/// Incoming messages have had the `PacketHeader` stripped off, but the
/// `MailHeader` is still tacked on the front of the data.
void
PostOffice::PostalDelivery()
{
    PacketHeader pktHdr;
    MailHeader   mailHdr;
    char        *buffer = new char [MAX_PACKET_SIZE];

    for (;;) {
        // First, wait for a message.
        messageAvailable->P();
        pktHdr = network->Receive(buffer);

        mailHdr = *(MailHeader *) buffer;
        if (debug.IsEnabled('n')) {
            printf("Putting mail into mailbox: ");
            PrintHeader(pktHdr, mailHdr);
        }

        // Check that arriving message is legal!
        ASSERT(0 <= mailHdr.to && mailHdr.to < numBoxes);
        ASSERT(mailHdr.length <= MAX_MAIL_SIZE);

        // Put into mailbox.
        boxes[mailHdr.to].Put(pktHdr, mailHdr, buffer + sizeof (MailHeader));
    }
}

/// Concatenate the `MailHeader` to the front of the data, and pass the
/// result to the `Network` for delivery to the destination machine.
///
/// Note that the `MailHeader` + data looks just like normal payload data to
/// the `Network`.
///
/// * `pktHdr` -- source, destination machine ID's.
/// * `mailHdr` -- source, destination mailbox ID's.
/// * `data` is the payload message data.
void
PostOffice::Send(PacketHeader pktHdr, MailHeader mailHdr, const char *data)
{
    ASSERT(data != nullptr);

    char *buffer = new char [MAX_PACKET_SIZE];  // Space to hold concatenated
                                                // `mailHdr` + data.

    if (debug.IsEnabled('n')) {
        printf("Post send: ");
        PrintHeader(pktHdr, mailHdr);
    }
    ASSERT(mailHdr.length <= MAX_MAIL_SIZE);
    ASSERT(0 <= mailHdr.to && mailHdr.to < numBoxes);

    // Fill in `pktHdr`, for the `Network` layer.
    pktHdr.from = netAddr;
    pktHdr.length = mailHdr.length + sizeof (MailHeader);

    // Concatenate `MailHeader` and data.
    memmove(buffer, &mailHdr, sizeof (MailHeader));
    memmove(buffer + sizeof (MailHeader), data, mailHdr.length);

    sendLock->Acquire();  // Only one message can be sent to the network at
                          // any one time.
    network->Send(pktHdr, buffer);
    messageSent->P();  // Wait for interrupt to tell us ok to send the next
                       // message.
    sendLock->Release();

    delete [] buffer;  // We have sent the message, so we can delete our
                       // buffer.
}

/// Retrieve a message from a specific box if one is available, otherwise
/// wait for a message to arrive in the box.
///
/// Note that the `MailHeader` + data looks just like normal payload data to
/// the `Network`.
///
/// * `box` is the mailbox ID in which to look for message.
/// * `pktHdr` is the address to put: source, destination machine ID's.
/// * `mailHdr` is the address to put: source, destination mailbox ID's.
/// * `data` is the address to put: payload message data.
void
PostOffice::Receive(int box, PacketHeader *pktHdr,
                    MailHeader *mailHdr, char *data)
{
    ASSERT(pktHdr != nullptr);
    ASSERT(mailHdr != nullptr);
    ASSERT(data != nullptr);
    ASSERT(box >= 0 && box < numBoxes);

    boxes[box].Get(pktHdr, mailHdr, data);
    ASSERT(mailHdr->length <= MAX_MAIL_SIZE);
}

/// Interrupt handler, called when a packet arrives from the network.
///
/// Signal the PostalDelivery routine that it is time to get to work!
void
PostOffice::IncomingPacket()
{
    messageAvailable->V();
}

/// Interrupt handler, called when the next packet can be put onto the
/// network.
///
/// The name of this routine is a misnomer; if `reliability < 1`, the packet
/// could have been dropped by the network, so it will not get through.
void
PostOffice::PacketSent()
{
    messageSent->V();
}
