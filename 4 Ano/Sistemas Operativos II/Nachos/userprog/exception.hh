/// Copyright (c) 2019 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_USERPROG_EXCEPTION__HH
#define NACHOS_USERPROG_EXCEPTION__HH


/// Set exception handlers for every exception type.
///
/// Exception handlers are the entry points into the Nachos kernel.  They
/// are called when a user program is executing, and either does a system
/// call, or generates an addressing or arithmetic exception.
void SetExceptionHandlers();


#endif
