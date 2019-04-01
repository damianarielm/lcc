/// Routines for converting Words and Short Words to and from the simulated
/// machine's format of little endian.  If the host machine is little endian
/// (DEC and Intel), these end up being NOPs.
///
/// What is stored in each format:
///
/// Host byte ordering
///     User registers and kernel data structures.
/// Simulated machine byte ordering
///     Main memory.
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_MACHINE_ENDIANNESS__HH
#define NACHOS_MACHINE_ENDIANNESS__HH


unsigned WordToHost(unsigned word);
unsigned short ShortToHost(unsigned short shortword);
unsigned WordToMachine(unsigned word);
unsigned short ShortToMachine(unsigned short shortword);


#endif
