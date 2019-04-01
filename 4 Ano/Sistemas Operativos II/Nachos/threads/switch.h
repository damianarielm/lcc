/// Definitions needed for implementing context switching.
///
/// Context switching is inherently machine dependent, since the registers to
/// be saved, how to set up an initial call frame, etc, are all specific to a
/// processor architecture.
///
/// This file currently supports the i386 and AMD64 architectures.
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See copyright.h for copyright notice and limitation
/// of liability and disclaimer of warranty provisions.

#ifndef NACHOS_THREADS_SWITCH__H
#define NACHOS_THREADS_SWITCH__H


#ifdef HOST_i386

/// The offsets of the registers from the beginning of the thread object.
#define _ESP   0
#define _EAX   4
#define _EBX   8
#define _ECX  12
#define _EDX  16
#define _EBP  20
#define _ESI  24
#define _EDI  28
#define _PC   32

/// These definitions are used in `Thread::StackAllocate`.
#define PCState          (_PC  / 4 - 1)
#define FPState          (_EBP / 4 - 1)
#define InitialPCState   (_ESI / 4 - 1)
#define InitialArgState  (_EDX / 4 - 1)
#define WhenDonePCState  (_EDI / 4 - 1)
#define StartupPCState   (_ECX / 4 - 1)

#define InitialPC   %esi
#define InitialArg  %edx
#define WhenDonePC  %edi
#define StartupPC   %ecx

#elif defined(HOST_x86_64)

/// The offsets of the registers from the beginning of the thread object.
#define _RSP    0
#define _RAX    8
#define _RBX   16
#define _RCX   24
#define _RDX   32
#define _RBP   40
#define _RSI   48
#define _RDI   56
#define _PC    64
#define _R8    72
#define _R9    80
#define _R10   88
#define _R11   96
#define _R12  104
#define _R13  112
#define _R14  120
#define _R15  128

/// These definitions are used in `Thread::StackAllocate`.
#define PCState          (_PC  / 8 - 1)
#define FPState          (_RBP / 8 - 1)
#define InitialPCState   (_RSI / 8 - 1)
#define InitialArgState  (_RBX / 8 - 1)
#define WhenDonePCState  (_RDI / 8 - 1)
#define StartupPCState   (_RAX / 8 - 1)

#else
#error "Architecture not recognized!"
#endif


#endif
