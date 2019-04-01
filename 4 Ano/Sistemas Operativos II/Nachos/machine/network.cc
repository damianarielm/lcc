/// Routines to simulate a network interface, using UNIX sockets to deliver
/// packets between multiple invocations of nachos.
///
/// DO NOT CHANGE -- part of the machine emulation
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "threads/system.hh"


/// Dummy functions because C++ cannot call member functions indirectly.

static void
NetworkReadPoll(void *arg)
{
    ASSERT(arg != nullptr);
    Network *net = (Network *) arg;
    net->CheckPktAvail();
}

static void
NetworkSendDone(void *arg)
{
    ASSERT(arg != nullptr);
    Network *net = (Network *) arg;
    net->SendDone();
}

/// Initialize the network emulation.
///
/// * `addr` is used to generate the socket name.
/// * `reliability` says whether we drop packets to emulate unreliable links.
/// * `readAvail`, `writeDone`, `callArg` -- analogous to console.
Network::Network(NetworkAddress addr, double reliability,
                 VoidFunctionPtr readAvail, VoidFunctionPtr writeDone,
                 void *callArg)
{
    ASSERT(readAvail != nullptr);
    ASSERT(writeDone != nullptr);

    ident = addr;
    if (reliability < 0)
        chanceToWork = 0;
    else if (reliability > 1)
        chanceToWork = 1;
    else
        chanceToWork = reliability;

    // Set up the stuff to emulate asynchronous interrupts.
    writeHandler = writeDone;
    readHandler = readAvail;
    handlerArg = callArg;
    sendBusy = false;
    inHdr.length = 0;

    sock = OpenSocket();
    snprintf(sockName, sizeof sockName, "SOCKET_%u", (unsigned) addr);
    AssignNameToSocket(sockName, sock);     // Bind socket to a filename in the
                     // current directory.

    // Start polling for incoming packets.
    interrupt->Schedule(NetworkReadPoll, this,
                        NETWORK_TIME, NETWORK_RECV_INT);
}

Network::~Network()
{
    CloseSocket(sock);
    DeAssignNameToSocket(sockName);
}

/// If a packet is already buffered, we simply delay reading the incoming
/// packet.  In real life, the incoming packet might be dropped if we cannot
/// read it in time.
void
Network::CheckPktAvail()
{
    // Schedule the next time to poll for a packet.
    interrupt->Schedule(NetworkReadPoll, this,
                        NETWORK_TIME, NETWORK_RECV_INT);

    if (inHdr.length != 0)  // Do nothing if packet is already buffered.
        return;
    if (!PollSocket(sock))  // Do nothing if no packet to be read.
        return;

    // Otherwise, read packet in.
    char *buffer = new char [MAX_WIRE_SIZE];
    ReadFromSocket(sock, buffer, MAX_WIRE_SIZE);

    // Divide packet into header and data.
    inHdr = *(PacketHeader *) buffer;
    ASSERT(inHdr.to == ident && inHdr.length <= MAX_PACKET_SIZE);
    memcpy(inbox, buffer + sizeof (PacketHeader), inHdr.length);
    delete [] buffer;

    DEBUG('n', "Network received packet from %d, length %u...\n",
          (int) inHdr.from, inHdr.length);
    stats->numPacketsRecvd++;

    // Tell post office that the packet has arrived.
    (*readHandler)(handlerArg);
}

/// Notify user that another packet can be sent.
void
Network::SendDone()
{
    sendBusy = false;
    stats->numPacketsSent++;
    (*writeHandler)(handlerArg);
}

/// Send a packet by concatenating hdr and data, and schedule an interrupt to
/// tell the user when the next packet can be sent.
///
/// Note we always pad out a packet to `MAX_WIRE_SIZE` before putting it into
/// the socket, because it is simpler at the receive end.
void
Network::Send(PacketHeader hdr, const char *data)
{
    ASSERT(data != nullptr);

    char toName[32];

    snprintf(toName, sizeof toName, "SOCKET_%u", (unsigned) hdr.to);

    ASSERT(!sendBusy && hdr.length > 0
           && hdr.length <= MAX_PACKET_SIZE && hdr.from == ident);
    DEBUG('n', "Sending to addr %u, %u bytes... ", hdr.to, hdr.length);

    interrupt->Schedule(NetworkSendDone, this,
                        NETWORK_TIME, NETWORK_SEND_INT);

    if (Random() % 100 >= chanceToWork * 100) { // Emulate a lost packet.
        DEBUG('n', "oops, lost it!\n");
        return;
    }

    // Concatenate `hdr` and `data` into a single buffer, and send it out.
    char *buffer = new char [MAX_WIRE_SIZE];
    *(PacketHeader *) buffer = hdr;
    memcpy(buffer + sizeof (PacketHeader), data, hdr.length);
    SendToSocket(sock, buffer, MAX_WIRE_SIZE, toName);
    delete [] buffer;
}

// Read a packet, if one is buffered.
PacketHeader
Network::Receive(char *data)
{
    ASSERT(data != nullptr);

    PacketHeader hdr = inHdr;

    inHdr.length = 0;
    if (hdr.length != 0)
        memmove(data, inbox, hdr.length);
    return hdr;
}
