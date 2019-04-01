/// Data structures to emulate low-level interrupt hardware.
///
/// The hardware provides a routine (`SetLevel`) to enable or disable
/// interrupts.
///
/// In order to emulate the hardware, we need to keep track of all interrupts
/// the hardware devices would cause, and when they are supposed to occur.
///
/// This module also keeps track of simulated time.  Time advances
/// only when the following occur:
///
/// * interrupts are re-enabled;
/// * a user instruction is executed;
/// * there is nothing in the ready queue.
///
/// As a result, unlike real hardware, interrupts (and thus time-slice
/// context switches) cannot occur anywhere in the code where interrupts are
/// enabled, but rather only at those places in the code where simulated time
/// advances (so that it becomes time to invoke an interrupt in the hardware
/// simulation).
///
/// NOTE: this means that incorrectly synchronized code may work fine on this
/// hardware simulation (even with randomized time slices), but it would not
/// work on real hardware.  (Just because we cannot always detect when your
/// program would fail in real life, does not mean it is ok to write
/// incorrectly synchronized code!)
///
/// DO NOT CHANGE -- part of the machine emulation
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_MACHINE_INTERRUPT__HH
#define NACHOS_MACHINE_INTERRUPT__HH


#include "lib/list.hh"


/// Interrupts can be disabled (`INT_OFF`) or enabled (`INT_ON`).
enum IntStatus {
    INT_OFF,
    INT_ON,
    NUM_INT_STATUS
};

/// Nachos can be running kernel code (`SYSTEM_MODE`), user code
/// (`USER_MODE`), or there can be no runnable thread, because the ready list
/// is empty (`IDLE_MODE`).
enum MachineStatus {
    IDLE_MODE,
    SYSTEM_MODE,
    USER_MODE,
    NUM_MACHINE_STATUS
};

/// `IntType` records which hardware device generated an interrupt.  In
/// Nachos, we support a hardware timer device, a disk, a console display and
/// keyboard, and a network.
enum IntType {
    TIMER_INT,
    DISK_INT,
    CONSOLE_WRITE_INT,
    CONSOLE_READ_INT,
    NETWORK_SEND_INT,
    NETWORK_RECV_INT,
    NUM_INT_TYPES
};

/// The following class defines an interrupt that is scheduled to occur in
/// the future.
///
/// The internal data structures are left public to make it simpler to
/// manipulate.
class PendingInterrupt {
public:

    /// initialize an interrupt that will occur in the future.
    PendingInterrupt(VoidFunctionPtr func, void *param,
                     unsigned time, IntType kind);

    VoidFunctionPtr handler;  ///< The function (in the hardware device
                              ///< emulator) to call when the interrupt
                              ///< occurs.
    void *arg;  ///< The argument to the function.
    unsigned when;  ///< When the interrupt is supposed to fire.
    IntType type;  ///< For debugging.
};

/// The following class defines the data structures for the simulation
/// of hardware interrupts.
///
/// We record whether interrupts are enabled or disabled, and any hardware
/// interrupts that are scheduled to occur in the future.
class Interrupt {
public:

    /// Initialize the interrupt simulation.
    Interrupt();

    /// De-allocate data structures.
    ~Interrupt();

    /// Disable or enable interrupts and return previous setting.
    IntStatus SetLevel(IntStatus level);

    /// Enable interrupts.
    void Enable();

    /// Return whether interrupts are enabled or disabled.
    IntStatus GetLevel() const;

    // The ready queue is empty, roll simulated time forward until the next
    // interrupt.
    void Idle();

    // Quit and print out stats.
    void Halt();

    // Cause a context switch on return from an interrupt handler.
    void YieldOnReturn();

    // Idle, kernel, user.
    MachineStatus GetStatus() const;

    void SetStatus(MachineStatus st);

    // Print interrupt state.
    void DumpState();


    /// NOTE: the following are internal to the hardware simulation code.
    /// DO NOT call these directly.  I should make them “private”,
    /// but they need to be public since they are called by the
    /// hardware device simulators.

    /// Schedule an interrupt to occur at time ``when''.
    ///
    /// This is called by the hardware device simulators.
    void Schedule(VoidFunctionPtr handler, void *arg,
                  unsigned when, IntType type);

    /// Advance simulated time.
    void OneTick();

private:
    IntStatus level;  ///< Are interrupts enabled or disabled?
    List<PendingInterrupt *> *pending;  ///< The list of interrupts scheduled
                                        ///< to occur in the future.
    bool inHandler;  ///< True if we are running an interrupt handler.
    bool yieldOnReturn;  ///< True if we are to context switch on return from
                         ///< the interrupt handler.
    MachineStatus status;  ///< Idle, kernel mode, user mode.

    /// These functions are internal to the interrupt simulation code.

    /// Check if an interrupt is supposed to occur now.
    bool CheckIfDue(bool advanceClock);

    /// SetLevel, without advancing the simulated time.
    void ChangeLevel(IntStatus old,
                     IntStatus now);

#ifdef DFS_TICKS_FIX
    /// Restart total ticks and the pending interrupt list.
    void RestartTicks();
#endif

};


#endif
