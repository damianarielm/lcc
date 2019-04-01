/// Data structures for gathering statistics about Nachos performance.
///
/// DO NOT CHANGE -- these stats are maintained by the machine emulation
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_MACHINE_STATS__HH
#define NACHOS_MACHINE_STATS__HH


/// The following class defines the statistics that are to be kept about
/// Nachos behavior -- how much time (ticks) elapsed, how many user
/// instructions executed, etc.
///
/// The fields in this class are public to make it easier to update.
class Statistics {
public:

    /// Total time running Nachos.
    unsigned totalTicks;

    /// Time spent idle (no threads to run).
    unsigned idleTicks;

    /// Time spent executing system code.
    unsigned systemTicks;

    /// Time spent executing user code (this is also equal to # of user
    /// instructions executed).
    unsigned userTicks;

    /// Number of disk read requests.
    unsigned numDiskReads;

    /// Number of disk write requests.
    unsigned numDiskWrites;

    /// Number of characters read from the keyboard.
    unsigned numConsoleCharsRead;

    /// Number of characters written to the display.
    unsigned numConsoleCharsWritten;

    /// Number of virtual memory page faults.
    unsigned numPageFaults;

    /// Number of packets sent over the network.
    unsigned numPacketsSent;

    /// Number of packets received over the network.
    unsigned numPacketsRecvd;

#ifdef DFS_TICKS_FIX
    /// Number of times the tick count gets reset.
    unsigned long tickResets;
#endif

    /// Initialize everything to zero.
    Statistics();

    /// Print collected statistics.
    void Print();
};

/// Constants used to reflect the relative time an operation would take in a
/// real system.
///
/// A “tick” is a just a unit of time -- if you like, a microsecond.
///
/// Since Nachos kernel code is directly executed, and the time spent in the
/// kernel measured by the number of calls to enable interrupts, these time
/// constants are none too exact.

const unsigned USER_TICK     = 1;
  ///< Advance for each user-level instruction.
const unsigned SYSTEM_TICK   = 10;
  ///< Advance each time interrupts are enabled.
const unsigned ROTATION_TIME = 500;
  ///< Time disk takes to rotate one sector.
const unsigned SEEK_TIME     = 500;
  ///< Time disk takes to seek past one track.
const unsigned CONSOLE_TIME  = 100;
  ///< Time to read or write one character.
const unsigned NETWORK_TIME  = 100;
  ///< Time to send or receive one packet.
const unsigned TIMER_TICKS   = 100;
  ///< (Average) time between timer interrupts.


#endif
