/// MIPS instruction disassembler
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "copyright.h"
#include "int.h"

#include <include/filehdr.h>
#include <include/scnhdr.h>
#include <include/syms.h>
#include <include/ldfcn.h>

#include <stdio.h>
#include <string.h>


static FILE   *fp;
static LDFILE *ldPtr;
static SCNHDR textHeader, rdataHeader, dataHeader,
              sdataHeader, sbssHeader, bssHeader;

static char filename[1000] = "a.out";  // Default a.out file.
static char self[256];                 // Name of invoking program.

static char mem[MEMSIZE];  // Main memory. Use `malloc` later.
static int TRACE, Traptrace, Regtrace;
static int ASSOC = 1, RAND = 0, LRD = 0;
static unsigned NROWS = 64, LINESIZE = 4;
static unsigned pc;

void
main(int argc, char *argv[])
{
    char *fakeargv[3];

    strncpy(self, argv[0], sizeof self);
    while (argc > 1 && argv[1][0] == '-') {
        argc--;
        argv++;
        for (const char *s = argv[0] + 1; *s != '\0'; ++s)
            switch (*s) {}
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
        argc++;
    }
    Disasm(memoffset, argc - 1, argv + 1);  // Where things normally start.
}

#define LOADSECTION(head)  LoadSection(&head);

static void
LoadSection(SCNHDR *hd)
{
    unsigned pc;
    if (hd->s_scnptr != 0) {
        //printf("loading %s\n", hd->s_name);
        pc = hd->s_vaddr;
        FSEEK(ldptr, hd->s_scnptr, 0);
        for (unsigned i = 0; i < hd->s_size; ++i) {
            if (pc - memoffset >= MEMSIZE) {
                printf("MEMSIZE too small. Fix and recompile.\n");
                exit(1);
            }
            *(char *) (mem - memoffset + pc++) = getc(fp);
        }
    }
}

static void
LoadProgram(char *filename)
{
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

    if (ldnshread(ldptr, ".text", &textHeader) != 1)
        printf("text section header missing\n");
    else
        LOADSECTION(textHeader)

    if (ldnshread(ldptr, ".rdata", &rdataHeader) != 1)
        printf("rdata section header missing\n");
    else
        LOADSECTION(rdataHeader)

    if (ldnshread(ldptr, ".data", &dataHeader) != 1)
        printf("data section header missing\n");
    else
        LOADSECTION(dataHeader)

    if (ldnshread(ldptr, ".sdata", &sdataHeader) != 1)
        printf("sdata section header missing\n");
    else
        LOADSECTION(sdataHeader)

    if (ldnshread(ldptr, ".sbss", &sbssHeader) != 1)
        printf("sbss section header missing\n");
    else
        LOADSECTION(sbssHeader)

    if (ldnshread(ldptr, ".bss", &bssHeader) != 1)
        printf("bss section header missing\n");
    else
        LOADSECTION(bssHeader)

    // BSS is already zeroed (statically-allocated memory).  This version
    // ignores relocation information.
}

static void
Disasm(unsigned startpc, int argc, char *argv[])
{
    pc = memoffset;
    for (unsigned i = 0; i < textHeader.s_size; i += 4) {
        Dis1(pc);
        pc += 4;
    }
}

static void
Dis1(int xpc)
{
    unsigned instruction;

    instruction = Fetch(pc);
    DumpAscii(instruction, pc);
    printf("\n");
}
