/// Data structures for simulating the execution of user programs running on
/// top of Nachos.
///
/// User programs are loaded into `mainMemory`; to Nachos, this looks just
/// like an array of bytes.  Of course, the Nachos kernel is in memory too --
/// but as in most machines these days, the kernel is loaded into a separate
/// memory region from user programs, and accesses to kernel memory are not
/// translated or paged.
///
/// In Nachos, user programs are executed one instruction at a time, by the
/// simulator.  Each memory reference is translated, checked for errors, etc.
///
/// DO NOT CHANGE -- part of the machine emulation
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_MACHINE_MACHINE__HH
#define NACHOS_MACHINE_MACHINE__HH


#include "exception_type.hh"
#include "mmu.hh"
#include "single_stepper.hh"
#include "lib/utility.hh"


// User program CPU state.  The full set of MIPS registers, plus a few
// more because we need to be able to start/stop a user program between
// any two instructions (thus we need to keep track of things like load
// delay slots, etc.)
enum {
    STACK_REG      = 29,  ///< User's stack pointer.
    RET_ADDR_REG   = 31,  ///< Holds return address for procedure calls.
    HI_REG         = 32,  ///< Double register to hold multiply result.
    LO_REG         = 33,
    PC_REG         = 34,  ///< Current program counter.
    NEXT_PC_REG    = 35,  ///< Next program counter (for branch delay).
    PREV_PC_REG    = 36,  ///< Previous program counter (for debugging).
    LOAD_REG       = 37,  ///< The register target of a delayed load.
    LOAD_VALUE_REG = 38,  ///< The value to be loaded by a delayed load.
    BAD_VADDR_REG  = 39,  ///< The failing virtual address on an exception.

    NUM_GP_REGS    = 32,  ///< 32 general purpose registers on MIPS.
    NUM_TOTAL_REGS = 40
};

class Instruction;

typedef void (*ExceptionHandler)(ExceptionType);

/// The following class defines the simulated host workstation hardware, as
/// seen by user programs -- the CPU registers, main memory, etc.
///
/// User programs should not be able to tell that they are running on our
/// simulator or on the real hardware, except:
/// * we do not support floating point instructions;
/// * the system call interface to Nachos is not the same as UNIX (10 system
///   calls in Nachos vs. 200 in UNIX!).
/// If we were to implement more of the UNIX system calls, we ought to be
/// able to run Nachos on top of Nachos!
///
/// The procedures in this class are defined in `machine.cc`, `mipssim.cc`,
/// and `translate.cc`.
class Machine {
public:

    /// Initialize the simulation of the hardware for running user programs.
    Machine(SingleStepper *st);

    /// Routines callable by the Nachos kernel.

    /// Run a user program.
    void Run();

    const int *GetRegisters() const;

    MMU *GetMMU();

    /// Read the contents of a CPU register.
    int ReadRegister(unsigned num) const;

    /// Store a value into a CPU register.
    void WriteRegister(unsigned num, int value);

    /// Wrappers for MMU methods.  These wrappers raise an exception in the
    /// machine if needed.

    bool ReadMem(unsigned addr, unsigned size, int *value);

    bool WriteMem(unsigned addr, unsigned size, int value);

    /// Print the user CPU and memory state.
    void DumpState();

    /// Routines internal to the machine simulation -- DO NOT call these.

    /// Fetch one instruction of a user program.
    ///
    /// Return false if an exception occurs, true otherwise.
    bool FetchInstruction(Instruction *instr);

    /// Run a certain instruction of a user program.
    void ExecInstruction(const Instruction *instr);

    /// Do a pending delayed load (modifying a reg).
    void DelayedLoad(unsigned nextReg, int nextVal);

    /// Trap to the Nachos kernel, because of a system call or other
    /// exception.
    void RaiseException(ExceptionType et, unsigned badVAddr);

    /// Register an exception handler: a callback kernel function to invoke
    /// when an exception of a certain type is raised.
    ///
    /// Such handlers are the entry points into the kernel.  The exception
    /// type is passed to the handler as an argument, so the same handler
    /// can be assigned to multiple exception types.
    void SetHandler(ExceptionType et, ExceptionHandler handler);

private:
    SingleStepper *singleStepper;  ///< Drop back into the method of a
                                   ///< provided object (may be a debugger)
                                   ///< after each simulated instruction.

    /// Private data structures.
    int registers[NUM_TOTAL_REGS];  ///< CPU registers, for executing user
                                    ///< programs.

    MMU mmu; ///< Memory management unit.

    ExceptionHandler handlers[NUM_EXCEPTION_TYPES];  ///< Exception handlers.
};


#endif
