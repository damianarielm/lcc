/// DO NOT CHANGE -- part of the machine emulation
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_MACHINE_MMU__HH
#define NACHOS_MACHINE_MMU__HH


#include "exception_type.hh"
#include "disk.hh"
#include "translation_entry.hh"


/// Definitions related to the size, and format of user memory.

const unsigned PAGE_SIZE = SECTOR_SIZE;  ///< Set the page size equal to the
                                         ///< disk sector size, for
                                         ///< simplicity.
const unsigned NUM_PHYS_PAGES = 32;
const unsigned MEMORY_SIZE = NUM_PHYS_PAGES * PAGE_SIZE;
const unsigned TLB_SIZE = 4;  ///< if there is a TLB, make it small.


/// This class simulates an MMU (memory management unit) that can use either
/// page tables or a TLB.
class MMU {
public:
    // Initialize the MMU subsystem.
    MMU();

    // Deallocate data structures.
    ~MMU();

    /// Read or write 1, 2, or 4 bytes of virtual memory (at `addr`).  Return
    /// false if a correct translation could not be found.

    ExceptionType ReadMem(unsigned addr, unsigned size, int *value);

    ExceptionType WriteMem(unsigned addr, unsigned size, int value);

    /// Data structures -- all of these are accessible to Nachos kernel code.
    /// “Public” for convenience.
    ///
    /// Note that *all* communication between the user program and the kernel
    /// are in terms of these data structures, along with the already
    /// declared methods.

    char *mainMemory;  ///< Physical memory to store user program,
                       ///< code and data, while executing.

    /// NOTE: the hardware translation of virtual addresses in the user
    /// program to physical addresses (relative to the beginning of
    /// `mainMemory`) can be controlled by one of:
    /// * a traditional linear page table;
    /// * a software-loaded translation lookaside buffer (tlb) -- a cache of
    ///   mappings of virtual page #'s to physical page #'s.
    ///
    /// If `tlb` is null, the linear page table is used.
    /// If `tlb` is non-null, the Nachos kernel is responsible for managing
    /// the contents of the TLB.  But the kernel can use any data structure
    /// it wants (eg, segmented paging) for handling TLB cache misses.
    ///
    /// For simplicity, both the page table pointer and the TLB pointer are
    /// public.  However, while there can be multiple page tables (one per
    /// address space, stored in memory), there is only one TLB (implemented
    /// in hardware).  Thus the TLB pointer should be considered as
    /// *read-only*, although the contents of the TLB are free to be modified
    /// by the kernel software.

    TranslationEntry *tlb;  ///< This pointer should be considered
                            ///< “read-only” to Nachos kernel code.

    TranslationEntry *pageTable;
    unsigned pageTableSize;

private:

    /// Retrieve a page entry either from a page table or the TLB.
    ExceptionType RetrievePageEntry(unsigned vpn,
                                    TranslationEntry **entry) const;

    /// Translate an address, and check for alignment.
    ///
    /// Set the use and dirty bits in the translation entry appropriately,
    /// and return an exception code if the translation could not be
    /// completed.
    ExceptionType Translate(unsigned virtAddr, unsigned *physAddr,
                            unsigned size, bool writing);
};


#endif
