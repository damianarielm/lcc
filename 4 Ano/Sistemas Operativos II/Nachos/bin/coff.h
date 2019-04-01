/// Data structures that describe the MIPS COFF format.
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_BIN_COFF__H
#define NACHOS_BIN_COFF__H


#include <stdint.h>


#define COFF_MIPSELMAGIC  0x0162

#define COFF_OMAGIC   0407
#define COFF_SOMAGIC  0x0701

typedef struct coffFileHeader {
    uint16_t magic;      /// Magic number.
    uint16_t nSections;  /// Number of sections.
    int32_t  timeDate;   /// Time & date stamp.
    uint32_t symbolPtr;  /// File pointer to symbolic header.
    uint32_t nSymbols;   /// Size of symbolic header.
    uint16_t optHeader;  /// Size of optional header.
    uint16_t flags;      /// Flags.
} coffFileHeader;

typedef struct coffOptHeader {
    uint16_t magic;       /// See above.
    int16_t  vStamp;      /// Version stamp.
    uint32_t textSize;    /// Text size in bytes, padded to DW boundary.
    uint32_t dataSize;    /// Initialized data "  ".
    uint32_t bssSize;     /// Uninitialized data "   ".
    uint32_t entry;       /// Entry point.
    uint32_t textStart;   /// Base of text used for this file.
    uint32_t dataStart;   /// Base of data used for this file.
    uint32_t bssStart;    /// Base of bss used for this file.
    uint32_t gprMask;     /// General purpose register mask.
    uint32_t cprMask[4];  /// Co-processor register masks.
    int32_t  gpValue;     /// The gp value used for this object.
} coffOptHeader;

typedef struct coffSectionHeader {
    char     name[8];     /// Section name.
    uint32_t physAddr;    /// Physical address, aliased s_nlib.
    uint32_t virtAddr;    /// Virtual address.
    uint32_t size;        /// Section size.
    uint32_t sectionPtr;  /// File pointer to raw data for section.
    uint32_t relocPtr;    /// File pointer to relocation.
    uint32_t lnnoPtr;     /// File pointer to gp histogram.
    uint16_t nReloc;      /// Number of relocation entries.
    uint16_t nLnno;       /// Number of gp histogram entries.
    uint32_t flags;       /// Flags.
} coffSectionHeader;

typedef struct coffReloc {
    uint32_t virtAddr;           // (Virtual) address of reference.
    uint32_t symbolIndex;        // Index into symbol table.
    uint16_t type;               // Relocation type.
    unsigned symbolIndex_ : 24,  // Index into symbol table.
             reserved     : 3,
             type_        : 4,   // Relocation type.
             extern_      : 1;   // If 1, `symbolIndex` is an index into the
                                 // external symbol table, else `symbolIndex`
                                 // is a section number.

} coffReloc;


#endif
