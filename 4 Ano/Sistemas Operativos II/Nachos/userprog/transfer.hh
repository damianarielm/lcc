/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2019 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_USERPROG_TRANSFER__HH
#define NACHOS_USERPROG_TRANSFER__HH


/// Copy a byte array from virtual machine to host.
void ReadBufferFromUser(int userAddress, char *outBuffer,
                        unsigned byteCount);

/// Copy a C string from virtual machine to host.
bool ReadStringFromUser(int userAddress, char *outString,
                        unsigned maxByteCount);

/// Copy a byte array from host to virtual machine.
void WriteBufferToUser(const char *buffer, unsigned byteCount);

/// Copy a C string from host to virtual machine.
void WriteStringToUser(const char *string, int userAddress);


#endif
