/// Data structures for managing the translation from virtual page # ->
/// physical page #, used for managing physical memory on behalf of user
/// programs.
///
/// The data structures in this file are “dual-use” - they serve both as a
/// page table entry, and as an entry in a software-managed translation
/// lookaside buffer (TLB).  Either way, each entry is of the form: *<virtual
/// page #, physical page #>*.
///
/// DO NOT CHANGE -- part of the machine emulation
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_MACHINE_TRANSLATIONENTRY__HH
#define NACHOS_MACHINE_TRANSLATIONENTRY__HH


#include "lib/utility.hh"


/// The following class defines an entry in a translation table -- either
/// in a page table or a TLB.
///
/// Each entry defines a mapping from one virtual page to one physical page.
///
/// In addition, there are some extra bits for access control (valid and
/// read-only) and some bits for usage information (use and dirty).
class TranslationEntry {
public:

    /// The page number in virtual memory.
    unsigned virtualPage;

    /// The page number in real memory (relative to the start of
    /// `mainMemory`).
    unsigned physicalPage;

    /// If this bit is set, the translation is ignored.
    ///
    /// (In other words, the entry has not been initialized.)
    bool valid;

    /// If this bit is set, the user program is not allowed to modify the
    /// contents of the page.
    bool readOnly;

    /// This bit is set by the hardware every time the page is referenced or
    /// modified.
    bool use;

    /// This bit is set by the hardware every time the page is modified.
    bool dirty;

};


#endif
