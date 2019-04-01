/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_BIN_INSTR__H
#define NACHOS_BIN_INSTR__H


// Instruction formats

#define rd(i)     (((i) >> 11) & 0x1F)
#define rt(i)     (((i) >> 16) & 0x1F)
#define rs(i)     (((i) >> 21) & 0x1F)
#define shamt(i)  (((i) >>  6) & 0x1F)
#define immed(i)  (((i) & 0x8000) ? (i) | (-0x8000) : (i) & 0x7FFF)

#define off26(i)  (((i) & ((1 << 26) - 1)) << 2)
#define top4(i)   ((i) & (~((1 << 28) - 1)))
#define off16(i)  (immed(i) << 2)

#define extend(i, hibitmask)  \
    (((i) & (hibitmask)) ? ((i) | -(hibitmask)) : (i))


#endif
