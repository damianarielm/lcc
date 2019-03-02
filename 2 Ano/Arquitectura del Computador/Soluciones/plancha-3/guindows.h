#ifndef __GUINDOWS_H
#define __GUINDOWS_H

#include <setjmp.h>

typedef jmp_buf task;
#define TRANSFER(o,d) (setjmp(o)==0?(longjmp(d,1),0):0);
extern void stack(task, void (*pf)());

#endif//__GUINDOWS_H
