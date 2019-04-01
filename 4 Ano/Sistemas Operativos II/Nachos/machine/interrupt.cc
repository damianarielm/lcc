/// Routines to simulate hardware interrupts.
///
/// The hardware provides a routine (`SetLevel`) to enable or disable
/// interrupts.
///
/// In order to emulate the hardware, we need to keep track of all interrupts
/// the hardware devices would cause, and when they are supposed to occur.
///
/// This module also keeps track of simulated time.  Time advances only when
/// the following occur:
/// * interrupts are re-enabled;
/// * a user instruction is executed;
/// * there is nothing in the ready queue.
///
/// DO NOT CHANGE -- part of the machine emulation
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "interrupt.hh"
#include "threads/system.hh"

#include <limits.h>


// String definitions for debugging messages

static const char *INT_LEVEL_NAMES[] = { "disabled", "enabled" };
static const char *INT_TYPE_NAMES[]  = {
    "timer", "disk", "console write", "console read",
    "network send", "network recv"
};

static inline bool
IsIntStatus(IntStatus s)
{
    return 0 <= s && s < NUM_INT_STATUS;
}

static inline bool
IsIntType(IntType t)
{
    return 0 <= t && t < NUM_INT_TYPES;
}

/// Initialize a hardware device interrupt that is to be scheduled to occur
/// in the near future.
///
/// * `func` is the procedure to call when the interrupt occurs.
/// * `param` is the argument to pass to the procedure.
/// * `time` is when (in simulated time) the interrupt is to occur.
/// * `kind` is the hardware device that generated the interrupt.
PendingInterrupt::PendingInterrupt(VoidFunctionPtr func, void *param,
                                   unsigned time, IntType kind)
{
    ASSERT(func != nullptr);
    ASSERT(IsIntType(kind));

    handler = func;
    arg     = param;
    when    = time;
    type    = kind;
}

/// Initialize the simulation of hardware device interrupts.
///
/// Interrupts start disabled, with no interrupts pending, etc.
Interrupt::Interrupt()
{
    level         = INT_OFF;
    pending       = new List<PendingInterrupt *>;
    inHandler     = false;
    yieldOnReturn = false;
    status        = SYSTEM_MODE;
}

/// De-allocate the data structures needed by the interrupt simulation.
Interrupt::~Interrupt()
{
    while (!pending->IsEmpty())
        delete pending->Pop();
    delete pending;
}

/// Change interrupts to be enabled or disabled, without advancing the
/// simulated time (normally, enabling interrupts advances the time).
///
/// Used internally.
///
/// * `old` is the old interrupt status.
/// * `now` is the new interrupt status.
void
Interrupt::ChangeLevel(IntStatus old, IntStatus now)
{
    ASSERT(IsIntStatus(old));
    ASSERT(IsIntStatus(now));

    level = now;
    DEBUG('i', "Interrupts %s\n", INT_LEVEL_NAMES[now]);
}

/// Change interrupts to be enabled or disabled, and if interrupts are being
/// enabled, advance simulated time by calling `OneTick`.
///
/// Returns the old interrupt status.
///
/// * `now` is the new interrupt status.
IntStatus
Interrupt::SetLevel(IntStatus now)
{
    ASSERT(IsIntStatus(now));

    IntStatus old = level;

    /// Interrupt handlers are prohibited from enabling interrupts.
    ASSERT(now == INT_OFF || !inHandler);

    ChangeLevel(old, now);  /// Change to new state.
    if (now == INT_ON && old == INT_OFF)
        OneTick();  /// Advance simulated time.
    return old;
}

/// Turn interrupts on.  Who cares what they used to be?
///
/// Used in `ThreadRoot`, to turn interrupts on when first starting up a
/// thread.
void
Interrupt::Enable()
{
    SetLevel(INT_ON);
}

/// Advance simulated time and check if there are any pending
/// interrupts to be called.
///
/// Two things can cause `OneTick` to be called:
/// * interrupts are re-enabled;
/// * a user instruction is executed.
void
Interrupt::OneTick()
{
    MachineStatus old = status;

    // Advance simulated time.
    if (status == SYSTEM_MODE) {
        stats->totalTicks += SYSTEM_TICK;
    stats->systemTicks += SYSTEM_TICK;
    } else {  // USER_PROGRAM
    stats->totalTicks += USER_TICK;
    stats->userTicks += USER_TICK;
    }
    DEBUG('i', "== Tick %u ==\n", stats->totalTicks);

    // Check any pending interrupts are now ready to fire.
    ChangeLevel(INT_ON, INT_OFF);  // First, turn off interrupts (interrupt
                                   // handlers run with interrupts disabled).
    while (CheckIfDue(false))      // Check for pending interrupts.
        ;
    ChangeLevel(INT_OFF, INT_ON);  // Re-enable interrupts.
    if (yieldOnReturn) {           // If the timer device handler asked for a
                                   // context switch, ok to do it now.
        yieldOnReturn = false;
        status = SYSTEM_MODE;      // Yield is a kernel routine.
        currentThread->Yield();
        status = old;
    }
}

/// Called from within an interrupt handler, to cause a context switch (for
/// example, on a time slice) in the interrupted thread, when the handler
/// returns.
///
/// We cannot do the context switch here, because that would switch out the
/// interrupt handler, and we want to switch out the interrupted thread.
void
Interrupt::YieldOnReturn()
{
    //ASSERT(inHandler);
    yieldOnReturn = true;
}

/// Routine called when there is nothing in the ready queue.
///
/// Since something has to be running in order to put a thread on the ready
/// queue, the only thing to do is to advance simulated time until the next
/// scheduled hardware interrupt.
///
/// If there are no pending interrupts, stop.  There is nothing more for us
/// to do.
void
Interrupt::Idle()
{
    DEBUG('i', "Machine idling; checking for interrupts.\n");
    status = IDLE_MODE;
    if (CheckIfDue(true)) {        // Check for any pending interrupts.
        while (CheckIfDue(false))  // Check for any other pending interrupts.
        yieldOnReturn = false;     // Since there is nothing in the ready
                                   // queue, the yield is automatic.
        status = SYSTEM_MODE;
        return;                    // Return in case there is now a runnable
                                   // thread.
    }

    // If there are no pending interrupts, and nothing is on the ready queue,
    // it is time to stop.  If the console or the network is operating, there
    // are *always* pending interrupts, so this code is not reached.
    // Instead, the halt must be invoked by the user program.

    DEBUG('i', "Machine idle.  No interrupts to do.\n");
    printf("No threads ready or runnable, and no pending interrupts.\n");
    printf("Assuming the program completed.\n");
    Halt();
}

/// Shut down Nachos cleanly, printing out performance statistics.
void
Interrupt::Halt()
{
    printf("Machine halting!\n\n");
    stats->Print();
    Cleanup();  // Never returns.
}

#ifdef DFS_TICKS_FIX
/// Restart the total ticks statistic and the pending interrupts list.
///
/// This function makes sure Nachos keeps working even after overflowing the
/// tick counter.  After some time (when `totalTicks` reach the maximum
/// positive number) Nachos would schedule a pending interrupt at a negative
/// time, and after that, it would hang.
void
Interrupt::RestartTicks()
{
    List<PendingInterrupt *> *oldPending = pending;
    pending = new List<PendingInterrupt *>;

    PendingInterrupt *i;
    unsigned          oldWhen = 0;
    while ((i = oldPending->SortedPop((int *) &oldWhen)) != nullptr)
    {
        unsigned newWhen = oldWhen - stats->totalTicks;
        pending->SortedInsert(i, newWhen);
        DEBUG('x', "Interrupt at time %u re-scheduled at new time %u.\n",
              oldWhen, newWhen);
    }

    delete oldPending;
    stats->totalTicks = 0;
    stats->tickResets += 1;
}
#endif

/// Arrange for the CPU to be interrupted when simulated time reaches `now +
/// when`.
///
/// Implementation: just put it on a sorted list.
///
/// NOTE: the Nachos kernel should not call this routine directly.  Instead,
/// it is only called by the hardware device simulators.
///
/// * `handler` is the procedure to call when the interrupt occurs.
/// * `arg` is the argument to pass to the procedure.
/// * `fromNow` is how far in the future (in simulated time) the interrupt is
///   to occur.
/// * `type` is the hardware device that generated the interrupt.
void
Interrupt::Schedule(VoidFunctionPtr handler, void *arg,
                    unsigned fromNow, IntType type)
{
    ASSERT(handler != nullptr);
    ASSERT(fromNow > 0);
    ASSERT(IsIntType(type));

#ifdef DFS_TICKS_FIX
    if (UINT_MAX - stats->totalTicks < fromNow)
    {
        DEBUG('x', "WARNING: total tick count is too large"
                   " and will be reset.\n");
        RestartTicks();
    }
#else
    // Terminate Nachos if the ticks overflowed.
    ASSERT(UINT_MAX - stats->totalTicks > fromNow);
#endif

    unsigned when = stats->totalTicks + fromNow;
    PendingInterrupt *toOccur = new PendingInterrupt(handler, arg,
                                                     when, type);

    DEBUG('i', "Scheduling interrupt handler the %s at time = %u\n",
          INT_TYPE_NAMES[type], when);

    pending->SortedInsert(toOccur, when);
}

/// Check if an interrupt is scheduled to occur, and if so, fire it off.
///
/// Returns true, if we fired off any interrupt handlers
///
/// * `advanceClock` -- if true, there is nothing in the ready queue, so we
///   should simply advance the clock to when the next pending interrupt
///   would occur (if any).  If the pending interrupt is just the time-slice
///   daemon, however, then we are done!
bool
Interrupt::CheckIfDue(bool advanceClock)
{
    MachineStatus old = status;
    unsigned      when;

    ASSERT(level == INT_OFF);  // Interrupts need to be disabled, to invoke
                               // an interrupt handler.
    if (debug.IsEnabled('i'))
        DumpState();
    PendingInterrupt *toOccur = pending->SortedPop((int *) &when);

    if (toOccur == nullptr)  // No pending interrupts.
    return false;

    if (advanceClock && when > stats->totalTicks) {  // Advance the clock.
        stats->idleTicks += (when - stats->totalTicks);
        stats->totalTicks = when;
    } else if (when > stats->totalTicks) {  // Not time yet, put it back.
        pending->SortedInsert(toOccur, when);
        return false;
    }

    // Check if there is nothing more to do, and if so, quit.
    if (status == IDLE_MODE && toOccur->type == TIMER_INT
          && pending->IsEmpty()) {
        pending->SortedInsert(toOccur, when);
        return false;
    }

    DEBUG('i', "Invoking interrupt handler for the %s at time %u\n",
            INT_TYPE_NAMES[toOccur->type], toOccur->when);
#ifdef USER_PROGRAM
    if (machine != nullptr)
        machine->DelayedLoad(0, 0);
#endif
    inHandler = true;
    status = SYSTEM_MODE;  // Whatever we were doing, we are now going to be
                           // running in the kernel.
    (*toOccur->handler)(toOccur->arg);  // Call the interrupt handler.
    status = old;  // Restore the machine status.
    inHandler = false;
    delete toOccur;
    return true;
}

IntStatus
Interrupt::GetLevel() const
{
    return level;
}

MachineStatus
Interrupt::GetStatus() const
{
    return status;
}

void
Interrupt::SetStatus(MachineStatus st)
{
    status = st;
}

/// Print information about an interrupt that is scheduled to occur.  When,
/// where, why, etc.
static void
PrintPending(PendingInterrupt *pend)
{
    ASSERT(pend != nullptr);

    printf("    Handler %s, scheduled at %u\n",
           INT_TYPE_NAMES[pend->type], pend->when);
}

/// Print the complete interrupt state -- the status, and all interrupts that
/// are scheduled to occur in the future.
void
Interrupt::DumpState()
{
    printf("Time: %u, interrupts %s\n",
           stats->totalTicks, INT_LEVEL_NAMES[level]);
    if (pending->IsEmpty())
        printf("No pending interrupts\n");
    else {
        printf("Pending interrupts:\n");
        pending->Apply(PrintPending);
    }
}
