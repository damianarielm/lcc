/// DO NOT CHANGE -- part of the machine emulation
///
/// Copyright (c) 2019 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "exception_type.hh"
#include "lib/utility.hh"


const char *ExceptionTypeToString(ExceptionType et)
{
    switch (et) {
        case NO_EXCEPTION:
            return "no exception";
        case SYSCALL_EXCEPTION:
            return "system call";
        case PAGE_FAULT_EXCEPTION:
            return "page/TLB entry fault";
        case READ_ONLY_EXCEPTION:
            return "read-only page";
        case BUS_ERROR_EXCEPTION:
            return "memory bus error";
        case ADDRESS_ERROR_EXCEPTION:
            return "address error";
        case OVERFLOW_EXCEPTION:
            return "overflow";
        case ILLEGAL_INSTR_EXCEPTION:
            return "illegal instruction";
        default:
            ASSERT(false);
    }
    return nullptr;
}
