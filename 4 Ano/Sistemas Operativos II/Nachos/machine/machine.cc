/// Routines for simulating the execution of user programs.
///
/// DO NOT CHANGE -- part of the machine emulation
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "machine.hh"
#include "threads/system.hh"


static inline bool
IsExceptionType(ExceptionType t)
{
    return 0 <= t && t < NUM_EXCEPTION_TYPES;
}

/// Check to be sure that the host really uses the format it says it does,
/// for storing the bytes of an integer.  Stop on error.
static void
CheckEndian()
{
    union checkIt {
        char     charWord[4];
        unsigned intWord;
    } check;

    check.charWord[0] = 1;
    check.charWord[1] = 2;
    check.charWord[2] = 3;
    check.charWord[3] = 4;

#ifdef HOST_IS_BIG_ENDIAN
    ASSERT(check.intWord == 0x01020304);
#else
    ASSERT(check.intWord == 0x04030201);
#endif
}

/// Initialize the simulation of user program execution.
///
/// * `st` -- pointer to an object that performs single stepping, for
///   dropping into it after each user instruction is executed; if null,
///   execute normally, without single stepping.
Machine::Machine(SingleStepper *st)
{
    for (unsigned i = 0; i < NUM_TOTAL_REGS; i++)
        registers[i] = 0;

    for (unsigned i = 0; i < NUM_EXCEPTION_TYPES; i++)
        handlers[i] = nullptr;

    singleStepper = st;
    CheckEndian();
}

const int *
Machine::GetRegisters() const
{
    return registers;
}

MMU *
Machine::GetMMU()
{
    return &mmu;
}

/// Fetch or write the contents of a user program register.
int
Machine::ReadRegister(unsigned num) const
{
    ASSERT(num < NUM_TOTAL_REGS);
    return registers[num];
}

void
Machine::WriteRegister(unsigned num, int value)
{
    ASSERT(num < NUM_TOTAL_REGS);
    //DEBUG('m', "WriteRegister %u, value %d\n", num, value);

    // Register 0 never changes its value: it is always 0.
    if (num != 0)
        registers[num] = value;
}

bool
Machine::ReadMem(unsigned addr, unsigned size, int *value)
{
    ExceptionType e = mmu.ReadMem(addr, size, value);
    if (e != NO_EXCEPTION) {
        RaiseException(e, addr);
        return false;
    }
    return true;
}

bool
Machine::WriteMem(unsigned addr, unsigned size, int value)
{
    ExceptionType e = mmu.WriteMem(addr, size, value);
    if (e != NO_EXCEPTION) {
        RaiseException(e, addr);
        return false;
    }
    return true;
}

/// Transfer control to the Nachos kernel from user mode, because the user
/// program either invoked a system call, or some exception occured (such as
/// the address translation failed).
///
/// * `et` is the cause of the kernel trap
/// * `badVaddr` is the virtual address causing the trap, if appropriate.
void
Machine::RaiseException(ExceptionType et, unsigned badVAddr)
{
    ASSERT(IsExceptionType(et));
    ASSERT(handlers[et] != nullptr);  // There must be a handler associated.

    DEBUG('m', "Exception: %s\n", ExceptionTypeToString(et));

    //ASSERT(interrupt->GetStatus() == USER_MODE);
    registers[BAD_VADDR_REG] = badVAddr;
    DelayedLoad(0, 0);  // Finish anything in progress.

    // Call the associated handler with interrupts enabled in system mode.
    interrupt->SetStatus(SYSTEM_MODE);
    (*handlers[et])(et);
    interrupt->SetStatus(USER_MODE);
}

void
Machine::SetHandler(ExceptionType et, ExceptionHandler handler)
{
    ASSERT(IsExceptionType(et));
    ASSERT(handler != nullptr);

    handlers[et] = handler;
}
