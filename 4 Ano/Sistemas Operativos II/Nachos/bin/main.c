/// MIPS instruction interpreter
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "copyright.h"
#include "int.h"

#include <filehdr.h>
#include <scnhdr.h>
#include <syms.h>
#include <ldfcn.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static FILE   *fp;
static LDFILE *ldptr;
static SCNHDR  texthead, rdatahead, datahead, sdatahead, sbsshead, bsshead;

static char filename[1000] = "a.out";  // Default a.out file.
static char self[256];                 // Name of invoking program.

char mem[MEMSIZE];  // Main memory. Use `malloc` later.
int  TRACE, Traptrace, Regtrace;
int  NROWS = 64, ASSOC = 1, LINESIZE = 4, RAND = 0, LRD = 0;

void
main(int argc, char *argv[])
{
    char *s;
    char *fakeargv[3];

    strncpy(self, argv[0], sizeof self);
    while (argc > 1 && argv[1][0] == '-') {
        --argc; ++argv;
        for (s = argv[0] + 1; *s != '\0'; ++s)
            switch (*s) {
                case 't':
                    TRACE = 1;
                    break;
                case 'T':
                    Traptrace = 1;
                    break;
                case 'r':
                    Regtrace = 1;
                    break;
                case 'm':
                    NROWS = atoi(*++argv);
                    ASSOC = atoi(*++argv);
                    LINESIZE = atoi(*++argv);
                    RAND = (*++argv)[0] == 'r';
                    LRD = (*argv)[0] == 'l'
                          && (*argv)[1] == 'r'
                          && (*argv)[2] == 'd';
                    argc -= 4;
                    break;
            }
    }

    if (argc >= 2)
        strncpy(filename, argv[1], sizeof filename);
    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "%s: Could not open '%s'\n", self, filename);
        exit(0);
    }
    fclose(fp);
    LoadProgram(filename);
    if (argv[1] == NULL) {
        fakeargv[1] = "a.out";
        fakeargv[2] = NULL;
        argv = fakeargv;
        ++argc;
    }
    RunProgram(memoffset, argc - 1, argv + 1);
      // Where things normally start.
}

static char *
String(const char *s)
{
    char *p;
    size_t size = strlen(s) + 1;

    p = malloc(size);
    strncpy(p, s, size);
    return p;
}

#define LOADSECTION(head)                                       \
    if (head.s_scnptr != 0) {                                   \
        /*printf("loading %s\n", head.s_name);*/                \
        pc = head.s_vaddr;                                      \
        FSEEK(ldptr, head.s_scnptr, 0);                         \
        for (i = 0; i < head.s_size; ++i)                       \
            *(char *) ((mem - memoffset) + pc++) = getc(fp);    \
        if (pc - memoffset >= MEMSIZE) {                        \
            printf("MEMSIZE too small. Fix and recompile.\n");  \
            exit(1);                                            \
        }                                                       \
    }

void
LoadProgram(char *filename)
{
    int  pc, i, j, strindex, stl;
    char str[1111];
    int  rc1, rc2;

    ldptr = ldopen(filename, NULL);
    if (ldptr == NULL) {
        fprintf(stderr, "%s: Load read error on %s\n", self, filename);
        exit(0);
    }
    if (TYPE(ldptr) != 0x162) {
        fprintf(stderr,
                "big-endian object file (little-endian interp)\n");
        exit(0);
    }

    if (ldnshread(ldptr, ".text", &texthead) != 1)
        printf("text section header missing\n");
    else
        LOADSECTION(texthead)

    if (ldnshread(ldptr, ".rdata", &rdatahead) != 1)
        printf("rdata section header missing\n");
    else
        LOADSECTION(rdatahead)

    if (ldnshread(ldptr, ".data", &datahead) != 1)
        printf("data section header missing\n");
    else
        LOADSECTION(datahead)

    if (ldnshread(ldptr, ".sdata", &sdatahead) != 1)
        printf("sdata section header missing\n");
    else
        LOADSECTION(sdatahead)

    if (ldnshread(ldptr, ".sbss", &sbsshead) != 1)
        printf("sbss section header missing\n");
    else
        LOADSECTION(sbsshead)

    if (ldnshread(ldptr, ".bss", &bsshead) != 1)
        printf("bss section header missing\n");
    else
        LOADSECTION(bsshead)

    // BSS is already zeroed (statically-allocated memeroy).  This version
    // ignores relocation information.
}
