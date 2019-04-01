/// Nachos system call interface.
///
/// These are Nachos kernel operations that can be invoked from user
/// programs, by trapping to the kernel via the `syscall` instruction.
///
/// This file is included by user programs and by the Nachos kernel.
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_USERPROG_SYSCALL__H
#define NACHOS_USERPROG_SYSCALL__H


/// System call codes.
///
/// Used by the stubs to tell the kernel which system call is being asked
/// for.

#define SC_HALT     0
#define SC_EXIT     1
#define SC_EXEC     2
#define SC_JOIN     3
#define SC_FORK     4
#define SC_YIELD    5
#define SC_CREATE  10
#define SC_REMOVE  11
#define SC_OPEN    12
#define SC_CLOSE   13
#define SC_READ    14
#define SC_WRITE   15


#ifndef IN_ASM

/// The system call interface.  These are the operations the Nachos kernel
/// needs to support, to be able to run user programs.
///
/// Each of these is invoked by a user program by simply calling the
/// procedure; an assembly language stub stuffs the system call code into a
/// register, and traps to the kernel.  The kernel procedures are then
/// invoked in the Nachos kernel, after appropriate error checking, from the
/// system call entry point in exception.cc.

/// Stop Nachos, and print out performance stats.
void Halt();


/// Address space control operations: `Exit`, `Exec`, and `Join`.

/// This user program is done (`status = 0` means exited normally).
void Exit(int status);

/// A unique identifier for an executing user program (address space).
typedef int SpaceId;

/// Run the executable, stored in the Nachos file `name`, and return the
/// address space identifier.
SpaceId Exec(char *name);

/// Only return once the the user program `id` has finished.
///
/// Return the exit status.
int Join(SpaceId id);


/// User-level thread operations: `Fork` and `Yield`.  To allow multiple
/// threads to run within a user program.

/// Fork a thread to run a procedure (`func`) in the *same* address space as
/// the current thread.
void Fork(void (*func)(void));

/// Yield the CPU to another runnable thread, whether in this address space
/// or not.
void Yield();


/// File system operations: `Create`, `Open`, `Read`, `Write`, `Close`.
///
/// These functions are patterned after UNIX -- files represent both files
/// *and* hardware I/O devices.
///
/// If this assignment is done before doing the file system assignment, note
/// that the Nachos file system has a stub implementation, which will work
/// for the purposes of testing out these routines.

/// A unique identifier for an open Nachos file.
typedef int OpenFileId;

/// When an address space starts up, it has two open files, representing
/// keyboard input and display output (in UNIX terms, stdin and stdout).
/// Read and Write can be used directly on these, without first opening the
/// console device.

#define CONSOLE_INPUT   0
#define CONSOLE_OUTPUT  1

/// Create a Nachos file, with `name`.
void Create(const char *name);

/// Remove the Nachos file named `name`.
int Remove(const char *name);

/// Open the Nachos file `name`, and return an `OpenFileId` that can be used
/// to read and write to the file.
OpenFileId Open(const char *name);

/// Write `size` bytes from `buffer` to the open file.
void Write(const char *buffer, int size, OpenFileId id);

/// Read `size` bytes from the open file into `buffer`.
///
/// Return the number of bytes actually read -- if the open file is not long
/// enough, or if it is an I/O device, and there are not enough characters to
/// read, return whatever is available (for I/O devices, you should always
/// wait until you can return at least one character).
int Read(char *buffer, int size, OpenFileId id);

/// Close the file, we are done reading and writing to it.
void Close(OpenFileId id);


#endif


#endif
