/// Data structures to emulate a hardware timer.
///
/// A hardware timer generates a CPU interrupt every X milliseconds.
/// This means it can be used for implementing time-slicing, or for
/// having a thread go to sleep for a specific period of time.
///
/// We emulate a hardware timer by scheduling an interrupt to occur every
/// time `stats->totalTicks` has increased by `TIMER_TICKS`.
///
/// In order to introduce some randomness into time-slicing, if `doRandom` is
/// set, then the interrupt comes after a random number of ticks.
///
/// DO NOT CHANGE -- part of the machine emulation
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_MACHINE_TIMER__HH
#define NACHOS_MACHINE_TIMER__HH


#include "lib/utility.hh"


/// The following class defines a hardware timer.
class Timer {
public:

    /// Initialize the timer, to call the interrupt handler `timerHandler`
    /// every time slice.
    Timer(VoidFunctionPtr timerHandler, void *callArg, bool doRandom);

    ~Timer() {}

    /// Internal routines to the timer emulation -- DO NOT call these.

    /// Called internally when the hardware timer generates an interrupt.
    void TimerExpired();

    /// Figure out when the timer will generate its next interrupt.
    int TimeOfNextInterrupt();

private:
    bool randomize;  ///< Set if we need to use a random timeout delay.
    VoidFunctionPtr handler;  ///< Timer interrupt handler.
    void *arg;  ///< Argument to pass to interrupt handler.

};


#endif
