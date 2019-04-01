/// Copyright (c) 2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_USERPROG_DEBUGGER__HH
#define NACHOS_USERPROG_DEBUGGER__HH


#include "debugger_command_manager.hh"
#include "machine/machine.hh"


class Debugger : public SingleStepper {
public:
    Debugger();

    virtual ~Debugger();

    /// Invoke the user program debugger.
    ///
    /// Returns whether to continue single-stepping or not.
    virtual bool Step();

private:
    static const unsigned BUFFER_SIZE = 80;

    char buffer[BUFFER_SIZE];
    DebuggerCommandManager manager;
    int previousRegisters[NUM_TOTAL_REGS];
    unsigned runUntilTime;  ///< Drop back into the debugger when simulated
                            ///< time reaches this value.
};


#endif
