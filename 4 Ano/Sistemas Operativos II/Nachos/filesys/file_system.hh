/// Data structures to represent the Nachos file system.
///
/// A file system is a set of files stored on disk, organized into
/// directories.  Operations on the file system have to do with “naming” --
/// creating, opening, and deleting files, given a textual file name.
/// Operations on an individual “open” file (read, write, close) are to be
/// found in the `OpenFile` class (`openfile.h`).
///
/// We define two separate implementations of the file system:
///
/// * The `STUB` version just re-defines the Nachos file system operations as
///   operations on the native UNIX file system on the machine running the
///   Nachos simulation.  This is provided in case the multiprogramming and
///   virtual memory assignments (which make use of the file system) are done
///   before the file system assignment.
///
/// * The other version is a “real” file system, built on top of a disk
///   simulator.  The disk is simulated using the native UNIX file system (in
///   a file named `DISK`).
///
///   In the "real" implementation, there are two key data structures used in
///   the file system.  There is a single “root” directory, listing all of
///   the files in the file system; unlike UNIX, the baseline system does not
///   provide a hierarchical directory structure.  In addition, there is a
///   bitmap for allocating disk sectors.  Both the root directory and the
///   bitmap are themselves stored as files in the Nachos file system -- this
///   causes an interesting bootstrap problem when the simulated disk is
///   initialized.
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_FILESYS_FILESYSTEM__HH
#define NACHOS_FILESYS_FILESYSTEM__HH


#include "open_file.hh"


#ifdef FILESYS_STUB  // Temporarily implement file system calls as calls to
                     // UNIX, until the real file system implementation is
                     // available.
class FileSystem {
public:

    FileSystem(bool format) {}

    ~FileSystem() {}

    bool Create(const char *name, unsigned initialSize)
    {
        ASSERT(name != nullptr);

        int fileDescriptor = OpenForWrite(name);
        if (fileDescriptor == -1)
            return false;
        Close(fileDescriptor);
        return true;
    }

    OpenFile *Open(const char *name)
    {
        ASSERT(name != nullptr);

        int fileDescriptor = OpenForReadWrite(name, false);
        if (fileDescriptor == -1)
            return nullptr;
        return new OpenFile(fileDescriptor);
    }

    bool Remove(const char *name)
    {
        ASSERT(name != nullptr);
        return Unlink(name) == 0;
    }

};

#else  // FILESYS
class FileSystem {
public:

    /// Initialize the file system.  Must be called *after* `synchDisk` has
    /// been initialized.
    ///
    /// If `format`, there is nothing on the disk, so initialize the
    /// directory and the bitmap of free blocks.
    FileSystem(bool format);

    ~FileSystem();

    /// Create a file (UNIX `creat`).
    bool Create(const char *name, unsigned initialSize);

    /// Open a file (UNIX `open`).
    OpenFile *Open(const char *name);

    /// Delete a file (UNIX `unlink`).
    bool Remove(const char *name);

    /// List all the files in the file system.
    void List();

    /// Check the filesystem.
    bool Check();

    /// List all the files and their contents.
    void Print();

private:
    OpenFile *freeMapFile;  ///< Bit map of free disk blocks, represented as a
                            ///< file.
    OpenFile *directoryFile;  ///< “Root” directory -- list of file names,
                              ///< represented as a file.
};

#endif


#endif
