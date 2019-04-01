/// Data structures for providing the abstraction of unreliable, ordered,
/// fixed-size message delivery to mailboxes on other (directly connected)
/// machines.  Messages can be dropped by the network, but they are never
/// corrupted.
///
/// The US Post Office delivers mail to the addressed mailbox.  By analogy,
/// our post office delivers packets to a specific buffer (`MailBox`), based
/// on the mailbox number stored in the packet header.  Mail waits in the box
/// until a thread asks for it; if the mailbox is empty, threads can wait for
/// mail to arrive in it.
///
/// Thus, the service our post office provides is to de-multiplex incoming
/// packets, delivering them to the appropriate thread.
///
/// With each message, you get a return address, which consists of a “from
/// address”, which is the id of the machine that sent the message, and a
/// “from box”, which is the number of a mailbox on the sending machine to
/// which you can send an acknowledgement, if your protocol requires this.
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#ifndef NACHOS_NETWORK_POST__HH
#define NACHOS_NETWORK_POST__HH


#include "network.hh"
#include "threads/synch_list.hh"


/// Mailbox address -- uniquely identifies a mailbox on a given machine.
///
/// A mailbox is just a place for temporary storage for messages.
typedef int MailBoxAddress;

/// The following class defines part of the message header.
///
/// This is prepended to the message by the `PostOffice`, before the message
/// is sent to the `Network`.
class MailHeader {
public:
    MailBoxAddress to;      ///< Destination mail box.
    MailBoxAddress from;    ///< Mail box to reply to.
    unsigned       length;  ///< Bytes of message data (excluding the mail
                            ///< header).
};

/// Maximum “payload” -- real data -- that can included in a single message.
/// Excluding the `MailHeader` and the `PacketHeader`.
const unsigned MAX_MAIL_SIZE = MAX_PACKET_SIZE - sizeof (MailHeader);

/// The following class defines the format of an incoming/outgoing `Mail`
/// message.
///
/// The message format is layered:
/// 1. network header (`PacketHeader`);
/// 2. post office header (`MailHeader`);
/// 3. data.
class Mail {
public:

    /// Initialize a mail message by concatenating the headers to the data.
    Mail(PacketHeader pktH, MailHeader mailH, const char *msgData);

    PacketHeader pktHdr;               ///< Header appended by `Network`.
    MailHeader   mailHdr;              ///< Header appended by `PostOffice`.
    char         data[MAX_MAIL_SIZE];  ///< Payload -- message data.
};

/// The following class defines a single mailbox, or temporary storage
/// for messages.
///
/// Incoming messages are put by the `PostOffice` into the appropriate
/// mailbox, and these messages can then be retrieved by threads on this
/// machine.
class MailBox {
public:

    /// Allocate and initialize mail box.
    MailBox();

    /// De-allocate mail box.
    ~MailBox();

    /// Atomically put a message into the mailbox.
    void Put(PacketHeader pktHdr, MailHeader mailHdr, const char *data);

    /// Atomically get a message out of the mailbox (and wait if there is no
    /// message to get!).
    void Get(PacketHeader *pktHdr, MailHeader *mailHdr, char *data);

private:

    /// A mailbox is just a list of arrived messages.
    SynchList<Mail *> *messages;

};

/// The following class defines a “post office”, or a collection of
/// mailboxes.
///
/// The post office is a synchronization object that provides two main
/// operations: `Send` -- send a message to a mailbox on a remote machine,
/// and `Receive` -- wait until a message is in the mailbox, then remove and
/// return it.
///
/// Incoming messages are put by the `PostOffice` into the appropriate
/// mailbox, waking up any threads waiting on `Receive`.
class PostOffice {
public:

    /// Allocate and initialize post office.
    ///
    /// * `reliability` is how many packets get dropped by the underlying
    ///   network.
    PostOffice(NetworkAddress addr, double reliability, int nBoxes);

    // De-allocate post office data.
    ~PostOffice();

    /// Send a message to a mailbox on a remote machine.
    ///
    /// The `fromBox` in the `MailHeader` is the return box for ack's.
    void Send(PacketHeader pktHdr, MailHeader mailHdr, const char *data);

    // Retrieve a message from `box`.
    //
    // Wait if there is no message in the box.
    void Receive(int box, PacketHeader *pktHdr,
                 MailHeader *mailHdr, char *data);

    // Wait for incoming messages, and then put them in the correct mailbox.
    void PostalDelivery();

    // Interrupt handler, called when outgoing packet has been put on
    // network; next packet can now be sent.
    void PacketSent();

    /// Interrupt handler, called when incoming packet has arrived and can be
    /// pulled off of network (i.e., time to call `PostalDelivery`).
    void IncomingPacket();

private:

    /// Physical network connection.
    Network *network;

    /// Network address of this machine.
    NetworkAddress netAddr;

    // Table of mail boxes to hold incoming mail.
    MailBox *boxes;

    // Number of mail boxes.
    int numBoxes;

    // `V`'ed when message has arrived from network.
    Semaphore *messageAvailable;

    // `V`'ed when next message can be sent to network.
    Semaphore *messageSent;

    // Only one outgoing message at a time.
    Lock *sendLock;

};


#endif
