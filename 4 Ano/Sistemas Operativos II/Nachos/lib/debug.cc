/// Debugging routines.
///
/// Allows users to control whether to print debug statements, based on a
/// command line argument.
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "debug.hh"
#include "utility.hh"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>


Debug::Debug()
{
    flags = "";
}

bool
Debug::IsEnabled(char flag) const
{
    if (flags != nullptr)
        return strchr(flags, flag) != 0
               || strchr(flags, '+') != 0;
    else
        return false;
}

const char *
Debug::GetFlags() const
{
    return flags;
}

void
Debug::SetFlags(const char *new_flags)
{
    flags = new_flags;
}

void
Debug::Print(char flag, const char *format, ...) const
{
    ASSERT(format != nullptr);

    if (!IsEnabled(flag))
        return;

    fprintf(stderr, "[%c] ", flag);

    va_list ap;
    // You will get an unused variable message here -- ignore it.
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);

    fflush(stderr);
}

void
Debug::PrintCont(char flag, const char *format, ...) const
{
    ASSERT(format != nullptr);

    if (!IsEnabled(flag))
        return;

    va_list ap;
    // You will get an unused variable message here -- ignore it.
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);

    fflush(stderr);
}
