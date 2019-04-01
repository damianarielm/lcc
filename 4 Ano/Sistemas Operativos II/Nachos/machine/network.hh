/// Data structures to emulate a physical network connection.
///
/// The network provides the abstraction of ordered, unreliable, fixed-size
/// packet delivery to other machines on the network.
///
/// You may note that the interface to the network is similar to the console
/// device -- both are full duplex channels.
///
/// DO NOT CHANGE -- part of the machine emulation
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_MACHINE_NETWORK__HH
#define NACHOS_MACHINE_NETWORK__HH


#include "lib/utility.hh"


/// Network address -- uniquely identifies a machine.
///
/// This machine's ID is given on the command line.
typedef int NetworkAddress;

/// The following class defines the network packet header.
///
/// The packet header is prepended to the data payload by the `Network`
/// driver, before the packet is sent over the wire.  The format on the wire
/// is:
/// 1. packet header (`PacketHeader`);
/// 2. data (containing `MailHeader` from the `PostOffice`!).
class PacketHeader {
public:
    NetworkAddress to;  ///< Destination machine ID.
    NetworkAddress from;  ///< source machine ID.
    unsigned length;  ///< Bytes of packet data, excluding the packet header
                      ///< (but including the `MailHeader` prepended by the
                      ///< by the post office).
};

/// Largest packet that can go out on the wire.
const unsigned MAX_WIRE_SIZE = 64;

/// Data “payload” of the largest packet.
const unsigned MAX_PACKET_SIZE = MAX_WIRE_SIZE - sizeof (PacketHeader);


/// The following class defines a physical network device.
///
/// The network is capable of delivering fixed sized packets, in order but
/// unreliably, to other machines connected to the network.
///
/// The “reliability” of the network can be specified to the constructor.
/// This number, between 0 and 1, is the chance that the network will lose
/// a packet.  Note that you can change the seed for the random number
/// generator, by changing the arguments to `RandomInit` in `Initialize`.
/// The random number generator is used to choose which packets to drop.
class Network {
public:

    /// Allocate and initialize network driver.
    Network(NetworkAddress addr, double reliability,
            VoidFunctionPtr readAvail, VoidFunctionPtr writeDone,
            void *callArg);

    /// De-allocate the network driver data.
    ~Network();

    /// Send the packet data to a remote machine, specified by `hdr`.
    ///
    /// Returns immediately.
    ///
    /// `writeHandler` is invoked once the next packet can be sent.  Note
    /// that `writeHandler` is called whether or not the packet is dropped.
    ///
    /// Also note that the `from` field of the `PacketHeader` is filled in
    /// automatically by `Send`.
    void Send(PacketHeader hdr, const char *data);

    /// Poll the network for incoming messages.
    ///
    /// If there is a packet waiting, copy the packet into `data` and return
    /// the header.  If no packet is waiting, return a header with length 0.
    PacketHeader Receive(char *data);

    /// Interrupt handler, called when message is sent.
    void SendDone();

    /// Check if there is an incoming packet.
    void CheckPktAvail();

private:

    /// This machine's network address.
    NetworkAddress ident;

    /// Likelihood packet will be dropped.
    double chanceToWork;

    /// UNIX socket number for incoming packets.
    int sock;

    /// File name corresponding to UNIX socket.
    char sockName[32];

    /// Interrupt handler, signalling next packet can be sent.
    VoidFunctionPtr writeHandler;

    /// Interrupt handler, signalling packet has arrived.
    VoidFunctionPtr readHandler;

    /// Argument to be passed to interrupt handler (pointer to post office).
    void *handlerArg;

    /// Packet is being sent.
    bool sendBusy;

    /// Packet has arrived, can be pulled off of network.
    bool packetAvail;

    /// Information about arrived packet.
    PacketHeader inHdr;

    /// Data for arrived packet.
    char inbox[MAX_PACKET_SIZE];
};


#endif
