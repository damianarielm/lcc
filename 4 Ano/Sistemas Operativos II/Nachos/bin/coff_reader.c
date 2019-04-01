/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2017-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "coff_reader.h"
#include <assert.h>
#include <stdlib.h>


/// Routines for converting words and short words to and from the simulated
/// machine's format of little endian.  These end up being NOPs when the host
/// machine is little endian.

static uint32_t
WordToHost(uint32_t word)
{
#ifdef HOST_IS_BIG_ENDIAN
    uint32_t result;
    result  = (word >> 24) & 0x000000ff;
    result |= (word >>  8) & 0x0000ff00;
    result |= (word <<  8) & 0x00ff0000;
    result |= (word << 24) & 0xff000000;
    return result;
#else
    return word;
#endif
}

static uint16_t
ShortToHost(uint16_t shortword)
{
#if HOST_IS_BIG_ENDIAN
     uint16_t result;
     result  = (shortword << 8) & 0xff00;
     result |= (shortword >> 8) & 0x00ff;
     return result;
#else
     return shortword;
#endif
}

#define FAIL(rv, s)         \
    {                       \
        if (error != NULL)  \
            *error = (s);   \
        return (rv);        \
    }

bool
CoffReaderLoad(coffReaderData *d, FILE *f, char **error)
{
    assert(f != NULL);
    assert(d != NULL);

    // Read in the file header and check the magic number.
    coffFileHeader *fh = &d->fileH;
    if (fread(fh, sizeof *fh, 1, f) != 1)
        FAIL(false, "File is too short");
    fh->magic = ShortToHost(fh->magic);
    fh->nSections = ShortToHost(fh->nSections);
    if (fh->magic != COFF_MIPSELMAGIC)
        FAIL(false, "File is not a MIPSEL COFF file");

    // Read in the optional header and check the magic number.
    coffOptHeader *oh = &d->optH;
    if (fread(oh, sizeof *oh, 1, f) != 1)
        FAIL(false, "File is too short");
    oh->magic = ShortToHost(oh->magic);
    if (oh->magic != COFF_OMAGIC)
        FAIL(false, "File is not an OMAGIC file");

    /// Read in the section headers.
    unsigned nsh = fh->nSections;
    d->sections = malloc(nsh * sizeof *d->sections);
    if (d->sections == NULL)
        FAIL(false, "Could not allocate memory");
    if (fread((char *) d->sections, nsh * sizeof *d->sections, 1, f) != 1)
        FAIL(false, "File is too short");

    for (unsigned i = 0; i < nsh; i++) {
        coffSectionHeader *sh = &d->sections[i];
        sh->physAddr   = WordToHost(sh->physAddr);
        sh->size       = WordToHost(sh->size);
        sh->sectionPtr = WordToHost(sh->sectionPtr);
    }

    d->current = 0;
    return true;
}

void
CoffReaderUnload(coffReaderData *d)
{
    assert(d != NULL);
    assert(d->sections != NULL);
      // Avoid unloading from an empty structure.

    free(d->sections);
    d->sections = NULL;
}

coffSectionHeader *
CoffReaderNextSection(coffReaderData *d)
{
    assert(d != NULL);
    assert(d->sections != NULL);
    assert(d->current <= d->fileH.nSections);

    if (d->current == d->fileH.nSections) {
        d->current = 0;
        return NULL;
    } else
        return &d->sections[d->current++];
}
