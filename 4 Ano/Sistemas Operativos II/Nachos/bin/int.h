/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_BIN_INT__H
#define NACHOS_BIN_INT__H


#define MEMSIZE    (1 << 24)
#define memoffset  0x10000000

// Centralized memory-access primitives
#define AMark(x)  (x)
#define IMark(x)  (x)

#define IFetch(addr)   (*(int *)           (&(mem - memoffset)[IMark(addr)]))
#define Fetch(addr)    (*(int *)           (&(mem - memoffset)[AMark(addr)]))
#define SFetch(addr)   (*(short *)         (&(mem - memoffset)[AMark(addr)]))
#define USFetch(addr)  \
    (*(unsigned short *) (&(mem - memoffset)[AMark(addr)]))
#define CFetch(addr)   (*(char *)          (&(mem - memoffset)[AMark(addr)]))
#define UCFetch(addr)  (*(unsigned char *) (&(mem - memoffset)[AMark(addr)]))

#define Store(addr, i)  \
    (*(int *) &(mem - memoffset)[AMark(addr)] = (i))
#define SStore(addr, i)  \
    (*(short *) &(mem - memoffset)[AMark(addr)] = (i))
#define CStore(addr, i)  \
    ((mem - memoffset)[AMark(addr)] = (i))


#endif
