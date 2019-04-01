/// Data structures to emulate a physical disk.
///
/// A physical disk can accept (one at a time) requests to read/write a disk
/// sector; when the request is satisfied, the CPU gets an interrupt, and the
/// next request can be sent to the disk.
///
/// Disk contents are preserved across machine crashes, but if a file system
/// operation (eg, create a file) is in progress when the system shuts down,
/// the file system may be corrupted.
///
/// DO NOT CHANGE -- part of the machine emulation
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_MACHINE_DISK__HH
#define NACHOS_MACHINE_DISK__HH


#include "lib/utility.hh"


/// The following class defines a physical disk I/O device.
///
/// The disk has a single surface, split up into “tracks”, and each track
/// split up into "sectors" (the same number of sectors on each track, and
/// each sector has the same number of bytes of storage).
///
/// Addressing is by sector number -- each sector on the disk is given a
/// unique number: `track * SECTORS_PER_TRACK + offset` within a track.
///
/// As with other I/O devices, the raw physical disk is an asynchronous
/// device -- requests to read or write portions of the disk return
/// immediately, and an interrupt is invoked later to signal that the
/// operation completed.
///
/// The physical disk is in fact simulated via operations on a UNIX file.
///
/// To make life a little more realistic, the simulated time for each
/// operation reflects a “track buffer” -- RAM to store the contents of the
/// current track as the disk head passes by.  The idea is that the disk
/// always transfers to the track buffer, in case that data is requested
/// later on.  This has the benefit of eliminating the need for "skip-sector"
/// scheduling -- a read request which comes in shortly after the head has
/// passed the beginning of the sector can be satisfied more quickly, because
/// its contents are in the track buffer.  Most disks these days now come
/// with a track buffer.
///
/// The track buffer simulation can be disabled by compiling with
/// `-DNOTRACKBUF`.

const unsigned SECTOR_SIZE = 128;       ///< Number of bytes per disk sector.
const unsigned SECTORS_PER_TRACK = 32;  ///< Number of sectors per disk
                                        ///< track.
const unsigned NUM_TRACKS = 32;         ///< Number of tracks per disk.
const unsigned NUM_SECTORS = SECTORS_PER_TRACK * NUM_TRACKS;
  ///< Total # of sectors per disk.

class Disk {
public:
    /// Create a simulated disk.
    ///
    /// Invoke `(*callWhenDone)(callArg)` every time a request completes.
    Disk(const char *name, VoidFunctionPtr callWhenDone, void *callArg);
    ~Disk();  // Deallocate the disk.

    /// Read/write an single disk sector.
    ///
    /// These routines send a request to the disk and return immediately.
    /// Only one request allowed at a time!

    void ReadRequest(unsigned sectorNumber, char *data);
    void WriteRequest(unsigned sectorNumber, const char *data);

    /// Interrupt handler, invoked when disk request finishes.
    void HandleInterrupt();

    /// Return how long a request to newSector will take.
    ///
    ///     (seek + rotational delay + transfer)
    int ComputeLatency(unsigned newSector, bool writing);

private:
    int fileno;  ///< UNIX file number for simulated disk.
    VoidFunctionPtr handler;  ///< Interrupt handler, to be invoked when any
                              ///< disk request finishes.
    void *handlerArg;  ///< Argument to interrupt handler.
    bool active;  ///< Is a disk operation in progress?
    unsigned lastSector;  ///< The previous disk request.
    int bufferInit;  ///< When the track buffer started being loaded.
                     // being loaded

    /// Time to get to the new track.
    unsigned TimeToSeek(unsigned newSector, unsigned *rotate);

    /// Number of sectors between `to` and `from`.
    unsigned ModuloDiff(unsigned to, unsigned from);

    void UpdateLast(unsigned newSector);
};


#endif
