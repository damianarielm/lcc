/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "int.h"

#include <syscall.h>

#include <stdio.h>


extern int  Reg[];
extern char mem[];
extern int  Traptrace;


/// Convert a user pointer to the real address.
/// Used in the interpreter.
static char *
UserPointerToAddress(int ptr)
{
    return (char *) ((int) mem - memoffset + ptr);
}

int
UserPointerToFd(int fd)
{
    if (fd > 2) {
        //printf("No general file descriptors yet.\n");
        //exit(2);
    }
    return fd;  // Assume we can handle it for now.
}

/// Handle system calls.
void
SystemBreak(void)
{
    if (Traptrace)
        printf("**breakpoint ");
    SystemTrap();
}

void
SystemTrap(void)
{
    int         o0, o1, o2;  // User out register values.
    int         syscallno;
    extern long lseek();

    if (Traptrace) {
        printf("**System call %d\n", Reg[2]);
        DumpReg();
    }

    //if (Reg[1] == 0) {  // SYS_indir
    //    syscallno = Reg[8];  // Out register 0.
    //    o0 = Reg[9];
    //    o1 = Reg[10];
    //    o2 = Reg[11];
    //}
    //else
    {
        syscallno = Reg[2];
        o0 = Reg[4];
        o1 = Reg[5];
        o2 = Reg[6];
    }

    switch (syscallno) {
        case SYS_exit:         // 1
            printstatistics();
            fflush(stdout);
            exit(0);
            break;
        case SYS_read:         // 3
            Reg[1] = read(UserPointerToFd(o0), UserPointerToAddress(o1), o2);
            break;
        case SYS_write:        // 4
            Reg[1] = write(UserPointerToFd(o0),
                           UserPointerToAddress(o1), o2);
            break;

        case SYS_open:         // 5
            Reg[1] = open(UserPointerToAddress(o0), o1, o2);
            break;

        case SYS_close:        // 6
            Reg[1] = 0;  // Hack
            break;

        case 17:               // 17
            // Old sbreak. where did it go?
            Reg[1] = (o0 / 8192 + 1) * 8192;
            break;

        case SYS_lseek:        // 19
            Reg[1] = (int) lseek(UserPointerToFd(o0), (long) o1, o2);
            break;

        case SYS_ioctl:        // 54
        {  /* Copied from sas -- I do not understand yet. */
           /* See Dave Weaver. */
#define IOCPARM_MASK  0x7F  /* Parameters must be < 128 bytes. */
            int size = (o1 >> 16) & IOCPARM_MASK;
            char ioctl_group = (o1 >> 8) & 0x00FF;
            if (ioctl_group == 't' && size == 8)
            {
                size = 6;
                o1 = (o1 & ~(IOCPARM_MASK << 16)) | (size << 16);
            }
        }
        Reg[1] = ioctl(UserPointerToFd(o0), o1, UserPointerToAddress(o2));
        Reg[1] = 0;  // Hack.
        break;

        case SYS_fstat:        // 62
            Reg[1] = fstat(o1, o2);
            break;

        case SYS_getpagesize:  // 64
            Reg[1] = getpagesize();
            break;

        default:
            printf("Unknown System call %d\n", syscallno);
            if (!Traptrace)
                DumpReg();
            exit(2);
            break;
    }
    if (Traptrace) {
        printf("**Afterwards:\n");
        DumpReg();
    }
}
