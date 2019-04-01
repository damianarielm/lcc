/// Data structures for opening, closing, reading and writing to individual
/// files.  The operations supported are similar to the UNIX ones -- type
/// `man open` to the UNIX prompt.
///
/// There are two implementations.  One is a `STUB` that directly turns the
/// file operations into the underlying UNIX operations.  (cf. comment in
/// `filesys.hh`).
///
/// The other is the “real” implementation, that turns these operations into
/// read and write disk sector requests.  In this baseline implementation of
/// the file system, we do not worry about concurrent accesses to the file
/// system by different threads -- this is part of the assignment.
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_FILESYS_OPENFILE__HH
#define NACHOS_FILESYS_OPENFILE__HH


#include "lib/utility.hh"


#ifdef FILESYS_STUB  // Temporarily implement calls to Nachos file system as
                     // calls to UNIX!  See definitions listed under `#else`.
class OpenFile {
public:

    /// Open the file.
    OpenFile(int f)
    {
        file = f;
        currentOffset = 0;
    }

    /// Close the file.
    ~OpenFile()
    {
        Close(file);
    }

    int ReadAt(char *into, unsigned numBytes, unsigned position)
    {
        ASSERT(into != nullptr);
        ASSERT(numBytes > 0);
        Lseek(file, position, 0);
        return ReadPartial(file, into, numBytes);
    }
    int WriteAt(const char *from, unsigned numBytes, unsigned position)
    {
        ASSERT(from != nullptr);
        ASSERT(numBytes > 0);
        Lseek(file, position, 0);
        WriteFile(file, from, numBytes);
        return numBytes;
    }
    int Read(char *into, unsigned numBytes)
    {
        ASSERT(into != nullptr);
        ASSERT(numBytes > 0);
        int numRead = ReadAt(into, numBytes, currentOffset);
        currentOffset += numRead;
        return numRead;
    }
    int Write(const char *from, unsigned numBytes)
    {
        ASSERT(from != nullptr);
        ASSERT(numBytes > 0);
        int numWritten = WriteAt(from, numBytes, currentOffset);
        currentOffset += numWritten;
        return numWritten;
    }

    unsigned Length() const
    {
        Lseek(file, 0, 2);
        return Tell(file);
    }

private:
    int file;
    unsigned currentOffset;
};

#else // FILESYS
class FileHeader;

class OpenFile {
public:

    /// Open a file whose header is located at `sector` on the disk.
    OpenFile(int sector);

    /// Close the file.
    ~OpenFile();

    /// Set the position from which to start reading/writing -- UNIX `lseek`.
    void Seek(unsigned position);

    /// Read/write bytes from the file, starting at the implicit position.
    /// Return the # actually read/written, and increment position in file.

    int Read(char *into, unsigned numBytes);
    int Write(const char *from, unsigned numBytes);

    /// Read/write bytes from the file, bypassing the implicit position.

    int ReadAt(char *into, unsigned numBytes, unsigned position);
    int WriteAt(const char *from, unsigned numBytes, unsigned position);

    // Return the number of bytes in the file (this interface is simpler than
    // the UNIX idiom -- `lseek` to end of file, `tell`, `lseek` back).
    unsigned Length() const;

  private:
    FileHeader *hdr;  ///< Header for this file.
    unsigned seekPosition;  ///< Current position within the file.
};

#endif


#endif
