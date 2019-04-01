/// Program that prints headers from NOFF files, for debugging purposes.
///
/// Copyright (c) 2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "noff.h"

#include <stdio.h>
#include <stdlib.h>


static void
PrintSegment(noffSegment *s, const char *description)
{
    printf("    %s segment:\n"
           "        Virtual address: %u (0x%X)\n"
           "        In-file address: %u (0x%X)\n"
           "        Size: %u bytes\n",
           description,
           s->virtualAddr, s->virtualAddr,
           s->inFileAddr, s->inFileAddr,
           s->size);
}

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <path to NOFF file>\n", argv[0]);
        return 1;
    }

    // Open the NOFF file.
    const char *path = argv[1];
    FILE *f = fopen(path, "rb");
    if (f == NULL) {
        perror(path);
        return 1;
    }

    // Read the file's header.
    noffHeader h;
    int rv = fread(&h, sizeof h, 1, f);
    if (rv != 1) {
        perror(path);
        fclose(f);
        return 1;
    }

    // Analyze the header and print the results.
    if (h.noffMagic == NOFF_MAGIC)
        printf("%s: NOFF file\n"
               "    Magic: 0x%X\n",
               path, h.noffMagic);
    else
        printf("%s: not a NOFF file\n"
               "    Magic: 0x%X (should be 0x%X)\n",
               path, h.noffMagic, NOFF_MAGIC);
    PrintSegment(&h.code, "Code");
    PrintSegment(&h.initData, "Initialized data");
    PrintSegment(&h.uninitData, "Uninitialized data");
    return 0;
}
