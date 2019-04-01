/// Data structures defining the Nachos Object Code Format
///
/// Basically, we only know about three types of segments: code (read-only),
/// initialized data, and unitialized data.

#ifndef NACHOS_BIN_NOFF__H
#define NACHOS_BIN_NOFF__H


#include <stdint.h>


#define NOFF_MAGIC  0xBADFAD  // Magic number denoting Nachos object code
                              // file.

typedef struct noffSegment {
    uint32_t virtualAddr;  // Location of segment in virtual address space.
    uint32_t inFileAddr;   // Location of segment in this file.
    uint32_t size;         // Size of segment.
} noffSegment;

typedef struct noffHeader {
    uint32_t noffMagic;      // Should be `NOFF_MAGIC`.
    noffSegment code;        // Executable code segment.
    noffSegment initData;    // Initialized data segment.
    noffSegment uninitData;  // Uninitialized data segment -- should be
                             // zeroed before use.
} noffHeader;


#endif
