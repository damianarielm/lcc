/// Looking at a.out formats
///
/// First task:
/// Look at mips COFF stuff:
/// Print out the contents of a file and do the following:
///    For data, print the value and give relocation information
///    For code, disassemble and give relocation information
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "coff.h"
#include "extern/syms.h"
#include "threads/copyright.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ReadStruct(f, s) (fread(&(s), sizeof (s), 1, (f)) == 1)

#define MAX_DATA    10000
#define MAX_RELOCS  1000

typedef struct data {
    uint32_t  data[MAX_DATA];
    coffReloc reloc[MAX_RELOCS];
    unsigned  length;
    unsigned  relocs;
} data;

#define MAX_SECTIONS  10
#define MAX_SYMBOLS   300
#define MAX_SSPACE    20000

coffFileHeader fileHeader;
coffOptHeader optHeader;
coffSectionHeader sectionHeader[MAX_SECTIONS];
data section[MAX_SECTIONS];

static HDRR symbolHeader;
static EXTR symbols[MAX_SYMBOLS];
static char sspace[MAX_SSPACE];

static const char *SYMBOL_TYPE[] = {
    "Nil", "Global", "Static", "Param", "Local", "Label", "Proc", "Block",
    "End", "Member", "Type", "File", "Register", "Forward", "StaticProc",
    "Constant" };

static const char *STORAGE_CLASS[] = {
    "Nil", "Text", "Data", "Bss", "Register", "Abs", "Undefined", "CdbLocal",
    "Bits", "CdbSystem", "RegImage", "Info", "UserStruct", "SData", "SBss",
    "RData", "Var", "Common", "SCommon", "VarRegister", "Variant",
    "SUndefined", "Init" };

static unsigned column = 1;

void
MyPrintf(const char *format, ...)
{
    va_list ap;
    char buffer[100];

    va_start(ap, format);
    vsnprintf(buffer, sizeof buffer, format, ap);
    va_end(ap);

    printf("%s", buffer);

    for (unsigned i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '\n')
            column = 1;
        else if (buffer[i] == '\t')
            column = ((column + 7) & ~7) + 1;
        else
            column += 1;
    }
}

static int
MyTab(unsigned n)
{
    while (column < n) {
        putchar(' ');
        column++;
    }
    return column == n;
}

static const char *SECTION_NAME[] = {
    "(null)", ".text", ".rdata", ".data", ".sdata", ".sbss", ".bss",
    ".init", ".lit8", ".lit4"
};

static const char *RELOC_TYPE[] = {
    "abs", "16", "32", "26", "hi16", "lo16", "gpdata", "gplit"
};

static void
PrintReloc(int vaddr, int i, int j)
{
    for (unsigned k = 0; k < section[i].relocs; k++) {
        coffReloc *rp;
        rp = &section[i].reloc[k];

        if (vaddr == rp->virtAddr) {
            MyTab(57);
            if (rp->extern_) {
                if (rp->symbolIndex >= MAX_SYMBOLS)
                    printf("sym $%u", rp->symbolIndex);
                else
                    printf("\"%s\"",
                           &sspace[symbols[rp->symbolIndex].asym.iss]);
            } else
                printf("%s", SECTION_NAME[rp->symbolIndex]);
            printf(" %s", RELOC_TYPE[rp->type]);
            break;
        }
    }
    printf("\n");
}

#define printf  MyPrintf
#include "d.c"

static void
PrintSection(int i)
{
    bool is_text;
    long pc;
    long word;
    char *s;

    printf("Section %s (size %u, relocs %u):\n", sectionHeader[i].name,
           sectionHeader[i].size, section[i].relocs);
    is_text = strncmp(sectionHeader[i].name, ".text", 5) == 0;

    for (unsigned j = 0, pc = sectionHeader[i].virtAddr;
         j < section[i].length; j++) {
        word = section[i].data[j];
        if (is_text)
            DumpAscii(word, pc);
        else {
            printf("%08x: %08x  ", pc, word);
            s = (char *) &word;
            for (unsigned k = 0; k < 4; k++)
                if (isprint(s[k]))
                    printf("%c", s[k]);
                else
                    printf(".");
            printf("\t%d", word);
        }
        PrintReloc(pc, i, j);
        pc += 4;
    }
}

int
main(int argc, char *argv[])
{
    char *filename = "a.out";
    FILE *f;
    long l;
/* EXTR filesym; */
    char buf[100];

    if (argc == 2)
        filename = argv[1];
    if ((f = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "out: could not open `%s`.\n", filename);
        perror("out");
        exit(1);
    }
    if (!ReadStruct(f, fileHeader)
          || !ReadStruct(f, optHeader)
          || fileHeader.magic != COFF_MIPSELMAGIC) {
        fprintf(stderr,
                "out: %s is not a MIPS Little-Endian COFF object file.\n",
                filename);
        exit(1);
    }
    if (fileHeader.nSections > MAX_SECTIONS) {
        fprintf(stderr, "out: too many COFF sections (%u, max %u).\n",
                fileHeader.nSections, MAX_SECTIONS);
        exit(1);
    }
    for (unsigned i = 0; i < fileHeader.nSections; i++) {
        ReadStruct(f, sectionHeader[i]);
        if (sectionHeader[i].size > MAX_DATA * sizeof (long)
              && sectionHeader[i].sectionPtr != 0
              || sectionHeader[i].nReloc > MAX_RELOCS) {
            printf("section %s is too big.\n", sectionHeader[i].name);
            exit(1);
        }
    }
    for (unsigned i = 0; i < fileHeader.nSections; i++) {
        if (sectionHeader[i].sectionPtr != 0) {
            section[i].length = sectionHeader[i].size / 4;
            fseek(f, sectionHeader[i].sectionPtr, 0);
            fread(section[i].data, sizeof (long), section[i].length, f);
            section[i].relocs = sectionHeader[i].nReloc;
            fseek(f, sectionHeader[i].relocPtr, 0);
            fread(section[i].reloc, sizeof (coffReloc),
                  section[i].relocs, f);
        } else
            section[i].length = 0;
    }
    fseek(f, fileHeader.symbolPtr, 0);
    ReadStruct(f, symbolHeader);
    if (symbolHeader.iextMax > MAX_SYMBOLS)
        fprintf(stderr, "Too many symbols to store (%u, max %u).\n",
                symbolHeader.iextMax, MAX_SYMBOLS);
    fseek(f, symbolHeader.cbExtOffset, 0);
    for (unsigned i = 0; i < MAX_SYMBOLS && i < symbolHeader.iextMax; i++)
        ReadStruct(f, symbols[i]);
    if (symbolHeader.issExtMax > MAX_SSPACE) {
        fprintf(stderr, "Too large a string space (%u, max %u).\n",
                symbolHeader.issExtMax, MAX_SSPACE);
        exit(1);
    }
    fseek(f, symbolHeader.cbSsExtOffset, 0);
    fread(sspace, 1, symbolHeader.issExtMax, f);

    for (unsigned i = 0; i < fileHeader.nSections; i++)
        PrintSection(i);

    printf("External Symbols:\nValue\t Type\t\tStorage Class\tName\n");
    for (unsigned i = 0; i < MAX_SYMBOLS && i < symbolHeader.iextMax; i++) {
        SYMR *sym = &symbols[i].asym;
        if (sym->sc == scUndefined)
            MyPrintf("\t ");
        else
            MyPrintf("%08x ", sym->value);
        MyPrintf("%s", SYMBOL_TYPE[sym->st]);
        MyTab(25);
        MyPrintf("%s", STORAGE_CLASS[sym->sc]);
        MyTab(41);
        MyPrintf("%s\n", &sspace[sym->iss]);
    }

    return 0;
}
