/// Copyright (c) 2017-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_BIN_COFF_READER__H
#define NACHOS_BIN_COFF_READER__H


#include "coff.h"

#include <stdbool.h>
#include <stdio.h>


typedef struct coffReaderData {
    coffFileHeader fileH;
    coffOptHeader optH;
    coffSectionHeader *sections;
    unsigned current;  // Index of current section.
} coffReaderData;

bool CoffReaderLoad(coffReaderData *d, FILE *f, char **error);

void CoffReaderUnload(coffReaderData *d);

coffSectionHeader *CoffReaderNextSection(coffReaderData *d);


#endif
