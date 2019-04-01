/// Copyright (c) 2018-2019 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "coff_section.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>


#define FAIL(rv, s)         \
    {                       \
        if (error != NULL)  \
            *error = (s);   \
        return (rv);        \
    }

size_t CoffSectionAddr(const coffSectionHeader *sh)
{
    return sh->physAddr;
}

bool
CoffSectionEmpty(const coffSectionHeader *sh)
{
    return CoffSectionSize(sh) == 0;
}

char *
CoffSectionName(const coffSectionHeader *sh)
{
    assert(sh != NULL);

    char *s;
    s = malloc(sizeof sh->name + 1);
    if (s == NULL)
        return s;

    memcpy(s, sh->name, sizeof sh->name);
    s[sizeof sh->name] = '\0';
    return s;
}

size_t
CoffSectionSize(const coffSectionHeader *sh)
{
    assert(sh != NULL);
    return sh->size;
}

void
CoffSectionPrint(const coffSectionHeader *sh)
{
    assert(sh != NULL);

    char *name;
    name = CoffSectionName(sh);
    printf("    %s: filepos 0x%X, mempos 0x%X, size %u bytes\n",
           name, sh->sectionPtr, sh->physAddr, sh->size);
    free(name);
}

char *
CoffSectionRead(const coffSectionHeader *sh, FILE *f, char **error)
{
    assert(sh != NULL);
    assert(f != NULL);

    fseek(f, sh->sectionPtr, SEEK_SET);
    char *buffer = malloc(sh->size);
    if (buffer == NULL)
        FAIL(NULL, "Could not allocate memory");
    if (fread(buffer, sh->size, 1, f) != 1)
        FAIL(NULL, "File is too short");
    return buffer;
}
