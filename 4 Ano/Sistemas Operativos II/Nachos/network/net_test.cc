/// Test out message delivery between two "Nachos" machines, using the Post
/// Office to coordinate delivery.
///
/// Two caveats:
///
/// 1. Two copies of Nachos must be running, with machine ID's 0 and 1:
///        ./nachos -m 0 -o 1 &
///        ./nachos -m 1 -o 0 &
///
///  2. You need an implementation of condition variables, which is *not*
///     provided as part of the baseline threads implementation.  The Post
///     Office will not work without a correct implementation of condition
///     variables.
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "network.hh"
#include "post.hh"
#include "machine/interrupt.hh"
#include "threads/system.hh"


/// Test out message delivery, by doing the following:
///
/// 1. Send a message to the machine with ID "farAddr", at mail box #0.
/// 2. Wait for the other machine's message to arrive (in our mailbox #0).
/// 3. Send an acknowledgment for the other machine's message.
/// 4. Wait for an acknowledgement from the other machine to our original
///    message.
void
MailTest(int farAddr)
{
    PacketHeader outPktHdr, inPktHdr;
    MailHeader   outMailHdr, inMailHdr;
    const char *data = "Hello there!";
    const char *ack  = "Got it!";
    char buffer[MAX_MAIL_SIZE];

    // Construct packet, mail header for original message.
    // To: destination machine, mailbox 0.
    // From: our machine, reply to: mailbox 1.
    outPktHdr.to      = farAddr;
    outMailHdr.to     = 0;
    outMailHdr.from   = 1;
    outMailHdr.length = strlen(data) + 1;

    // Send the first message.
    postOffice->Send(outPktHdr, outMailHdr, data);

    // Wait for the first message from the other machine.
    postOffice->Receive(0, &inPktHdr, &inMailHdr, buffer);
    printf("Got \"%s\" from %d, box %d\n",
           buffer, inPktHdr.from, inMailHdr.from);
    fflush(stdout);

    // Send acknowledgement to the other machine (using “reply to” mailbox
    // in the message that just arrived.
    outPktHdr.to      = inPktHdr.from;
    outMailHdr.to     = inMailHdr.from;
    outMailHdr.length = strlen(ack) + 1;
    postOffice->Send(outPktHdr, outMailHdr, ack);

    // Wait for the ack from the other machine to the first message we sent.
    postOffice->Receive(1, &inPktHdr, &inMailHdr, buffer);
    printf("Got \"%s\" from %d, box %d\n",
           buffer, inPktHdr.from, inMailHdr.from);
    fflush(stdout);

    // Then we are done!
    interrupt->Halt();
}
