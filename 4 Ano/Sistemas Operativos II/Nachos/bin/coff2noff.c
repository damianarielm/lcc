/// This program reads in a COFF format file, and outputs a NOFF format file.
/// The NOFF format is essentially just a simpler version of the COFF file,
/// recording where each segment is in the NOFF file, and where it is to
/// go in the virtual address space.
///
/// Assumes coff file is linked with either:
///     gld with -N -Ttext 0
///     ld with  -N -T 0
/// to make sure the object file has no shared text.
///
/// Also assumes that the COFF file has at most 3 segments:
///    .text      -- read-only executable instructions
///    .data      -- initialized data
///    .bss/.sbss -- uninitialized data (should be zeroed on program startup)
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2019 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "coff_reader.h"
#include "coff_section.h"
#include "noff.h"
#include "threads/copyright.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <assert.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ReadStructOrDie(f, s)  ReadOrDie(f, (char *) &(s), sizeof (s))

static char *outFileName = NULL;

static void
Die(const char *format, ...)
{
    assert(format != NULL);

    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\n");

    unlink(outFileName);
    exit(1);
}

/// Read and check for error.
static void
ReadOrDie(FILE *f, char *buffer, size_t numBytes)
{
    assert(f != NULL);
    assert(buffer != NULL);

    if (fread(buffer, numBytes, 1, f) != 1)
        Die("File is too short");
}

/// Write and check for error.
static void
WriteOrDie(FILE *f, const char *buffer, size_t numBytes)
{
    assert(f != NULL);
    assert(buffer != NULL);

    if (fwrite(buffer, numBytes, 1, f) != 1)
        Die("Unable to write file");
}

void
main(int argc, char *argv[])
{
    FILE      *in, *out;
    int        inNoffFile;
    unsigned   numSections, i;
    char      *buffer;
    noffHeader noffH;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <coffFileName> <noffFileName>\n",
                argv[0]);
        exit(1);
    }

    /// Open the COFF file (input).
    in = fopen(argv[1], "rb");
    if (in == NULL) {
        perror(argv[1]);
        exit(1);
    }

    /// Open the NOFF file (output).
    out = fopen(argv[2], "wb");
    if (out == NULL) {
        perror(argv[2]);
        exit(1);
    }
    outFileName = argv[2];

    /// Load the COFF file.
    char *errorS;
    coffReaderData d;
    if (!CoffReaderLoad(&d, in, &errorS))
        Die(errorS);

    /// Initialize the NOFF header, in case not all the segments are defined
    /// in the COFF file.
    noffH.noffMagic       = NOFF_MAGIC;
    noffH.code.size       = 0;
    noffH.initData.size   = 0;
    noffH.uninitData.size = 0;

    /// Copy the segments in.
    CoffSection *sc;
    inNoffFile = sizeof noffH;
    fseek(out, inNoffFile, SEEK_SET);
    printf("Translating COFF sections into NOFF:\n");
    while ((sc = CoffReaderNextSection(&d)) != NULL) {
        CoffSectionPrint(sc);
        if (CoffSectionEmpty(sc))
            // Do nothing!
            continue;

        size_t addr = CoffSectionAddr(sc);
        char *name = CoffSectionName(sc);
        size_t size = CoffSectionSize(sc);

        if (!strcmp(name, ".text")) {
            noffH.code.virtualAddr = addr;
            noffH.code.inFileAddr  = inNoffFile;
            noffH.code.size        = size;
            if ((buffer = CoffSectionRead(sc, in, &errorS)) == NULL)
                Die(errorS);
            WriteOrDie(out, buffer, size);
            free(buffer);
            inNoffFile += size;
        } else if (!strcmp(name, ".data")
                     || !strcmp(name, ".rdata")) {
            /// Need to check if we have both `.data` and `.rdata` -- make
            /// sure one or the other is empty!
            if (noffH.initData.size != 0)
                Die("Cannot handle both data and rdata");
            noffH.initData.virtualAddr = addr;
            noffH.initData.inFileAddr  = inNoffFile;
            noffH.initData.size        = size;
            if ((buffer = CoffSectionRead(sc, in, &errorS)) == NULL)
                Die(errorS);
            WriteOrDie(out, buffer, size);
            free(buffer);
            inNoffFile += size;
        } else if (!strcmp(name, ".bss") || !strcmp(name, ".sbss")) {
            /// Need to check if we have both `.bss` and `.sbss` -- make sure
            /// they are contiguous.
            if (noffH.uninitData.size != 0) {
                if (addr == noffH.uninitData.virtualAddr +
                            noffH.uninitData.size)
                    Die("Cannot handle both bss and sbss");
                noffH.uninitData.size += size;
            } else {
                noffH.uninitData.virtualAddr = addr;
                noffH.uninitData.size        = size;
            }
            // We do not need to copy the uninitialized data!
        } else if (!strcmp(name, ".comment"))
            // Ignore.  This section contains build information.
            ;
        else if (!strcmp(name, ".pdr"))
            // Ignore.  This section is for debugging.
            //
            // For more information, see:
            // * https://gdb-patches.sourceware.narkive.com/3bt9szEg/rfa-mips-use-pdr-sections-generated-by-gas
            ;
        else if (!strcmp(name, ".reginfo"))
            // Ignore.  This section is specific to the System V MIPS ABI and
            // nothing really uses it.
            //
            // For information about it, see:
            // * System V Application Binary Interface, MIPS RISC processor
            //   supplement.
            //     ftp://www.linux-mips.org/pub/linux/mips/doc/ABI/mipsabi.pdf
            // * Discussion in the linux-mips mailing list.
            //     https://www.linux-mips.org/archives/linux-mips/2002-12/msg00190.html
            ;
        else
            //Die("Unknown segment type: `%s`", name);
            printf("WARNING: ignoring segment type \"%s\".\n", name);

        free(name);
    }

    fseek(out, 0, SEEK_SET);
    WriteOrDie(out, (const char *) &noffH, sizeof noffH);
    fclose(in);
    fclose(out);
    exit(0);
}
