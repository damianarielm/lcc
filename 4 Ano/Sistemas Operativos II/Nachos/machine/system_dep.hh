/// System-dependent interface.
///
/// Nachos uses the routines defined here, rather than directly calling the
/// UNIX library functions, to simplify porting between versions of UNIX, and
/// even to other systems, such as MSDOS and the Macintosh.
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_MACHINE_SYSDEP__HH
#define NACHOS_MACHINE_SYSDEP__HH


#include <stddef.h>


/// Check file to see if there are any characters to be read.
///
/// If no characters in the file, return without waiting.
extern bool PollFile(int fd);

/// File operations: `open`/`read`/`write`/`lseek`/`close`, and check for
/// error.
///
/// For simulating the disk and the console devices.

extern int OpenForWrite(const char *name);

extern int OpenForReadWrite(const char *name, bool crashOnError);

extern void Read(int fd, char *buffer, size_t nBytes);

extern int ReadPartial(int fd, char *buffer, size_t nBytes);

extern void WriteFile(int fd, const char *buffer, size_t nBytes);

extern void Lseek(int fd, int offset, int whence);

extern int Tell(int fd);

extern void Close(int fd);

extern bool Unlink(const char *name);

/// Interprocess communication operations, for simulating the network.

extern int OpenSocket();

extern void CloseSocket(int sockID);

extern void AssignNameToSocket(const char *socketName, int sockID);

extern void DeAssignNameToSocket(const char *socketName);

extern bool PollSocket(int sockID);

extern void ReadFromSocket(int sockID, char *buffer, size_t packetSize);

extern void SendToSocket(int sockID, const char *buffer,
                         size_t packetSize, const char *toName);

/// Process control: `sleep`.

extern void Delay(unsigned seconds);

/// Initialize system so that `cleanUp` routine is called when user hits
/// Ctrl-C.
extern void CallOnUserAbort(VoidNoArgFunctionPtr cleanUp);

/// Initialize the pseudo random number generator.
extern void RandomInit(unsigned seed);

extern int Random();

/// Allocate, de-allocate an array, such that de-referencing just beyond
/// either end of the array will cause an error.

extern char *AllocBoundedArray(unsigned size);

extern void DeallocBoundedArray(const char *p, unsigned size);

/// Other C library routines that are used by Nachos.
/// These are assumed to be portable, so we do not include a wrapper.
extern "C" {
#include <stdlib.h>  // for `atoi`, `atof`, `abs`
#include <stdio.h>   // for `printf`, `fprintf`
#include <string.h>  // for `DEBUG`, etc.
}


#endif
