/// Copyright (c) 2018-2019 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_BIN_COFF_SECTION__H
#define NACHOS_BIN_COFF_SECTION__H


#include "coff.h"
#include <stdbool.h>
#include <stdio.h>


typedef coffSectionHeader CoffSection;

size_t CoffSectionAddr(const CoffSection *sh);

bool CoffSectionEmpty(const CoffSection *sh);

// Returns a dynamically allocated string.  It should be freed by the caller
// when no longer needed.
char *CoffSectionName(const CoffSection *sh);

size_t CoffSectionSize(const CoffSection *sh);

void CoffSectionPrint(const CoffSection *sh);

char *CoffSectionRead(const CoffSection *sh, FILE *f, char **error);


#endif
