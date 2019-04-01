/// Routines to simulate a physical disk device; reading and writing to the
/// disk is simulated as reading and writing to a UNIX file.  See `disk.hh`
/// for details about the behavior of disks (and therefore about the behavior
/// of this simulation).
///
/// Disk operations are asynchronous, so we have to invoke an interrupt
/// handler when the simulated operation completes.
///
/// DO NOT CHANGE -- part of the machine emulation
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "disk.hh"
#include "threads/system.hh"


/// We put this at the front of the UNIX file representing the
/// disk, to make it less likely we will accidentally treat a useful file
/// as a disk (which would probably trash the file's contents).
static const unsigned MAGIC_NUMBER = 0x456789AB;
static const unsigned MAGIC_SIZE = sizeof (int);

static const unsigned DISK_SIZE = MAGIC_SIZE + NUM_SECTORS * SECTOR_SIZE;

/// dummy procedure because we cannot take a pointer of a member function
static void
DiskDone(void *arg)
{
    ASSERT(arg != nullptr);
    ((Disk *) arg)->HandleInterrupt();
}

/// Initialize a simulated disk.  Open the UNIX file (creating it if it
/// does not exist), and check the magic number to make sure it is ok to
/// treat it as Nachos disk storage.
//
/// * `name` is the text name of the file simulating the Nachos disk.
/// * `callWhenDone` is an interrupt handler to be called when disk
///   read/write request completes.
/// * `callArg` is an argument to pass the interrupt handler.
Disk::Disk(const char *name, VoidFunctionPtr callWhenDone, void *callArg)
{
    ASSERT(name != nullptr);
    ASSERT(callWhenDone != nullptr);

    int magicNum;
    int tmp = 0;

    DEBUG('d', "Initializing the disk, 0x%X 0x%X\n", callWhenDone, callArg);
    handler    = callWhenDone;
    handlerArg = callArg;
    lastSector = 0;
    bufferInit = 0;

    fileno = OpenForReadWrite(name, false);
    if (fileno >= 0) {  // File exists, check magic number.
        Read(fileno, (char *) &magicNum, MAGIC_SIZE);
        ASSERT(magicNum == MAGIC_NUMBER);
    } else {            // File does not exist, create it.
        fileno = OpenForWrite(name);
        magicNum = MAGIC_NUMBER;
        WriteFile(fileno, (char *) &magicNum, MAGIC_SIZE);
          // Write magic number.

        // Need to write at end of file, so that reads will not return EOF.
        Lseek(fileno, DISK_SIZE - sizeof (int), 0);
        WriteFile(fileno, (char *) &tmp, sizeof (int));
    }
    active = false;
}

/// Clean up disk simulation, by closing the UNIX file representing the disk.
Disk::~Disk()
{
    Close(fileno);
}

/// Dump the data in a disk read/write request, for debugging.
static void
PrintSector(bool writing, unsigned sector, const char *data)
{
    ASSERT(data != nullptr);

    int *p = (int *) data;

    if (writing)
        printf("Writing sector: %u\n", sector);
    else
        printf("Reading sector: %u\n", sector);
    for (unsigned i = 0; i < SECTOR_SIZE / sizeof (int); i++)
        printf("%X ", p[i]);
    printf("\n");
}

/// Disk::ReadRequest/WriteRequest
///
/// Simulate a request to read/write a single disk sector.
///
/// Do the read/write immediately to the UNIX file.  Set up an interrupt
/// handler to be called later, that will notify the caller when the
/// simulator says the operation has completed.
///
/// Note that a disk only allows an entire sector to be read/written, not
/// part of a sector.
///
/// * `sectorNumber` is the disk sector to read/write.
/// * `data` are the bytes to be written, the buffer to hold the incoming
///   bytes.
void
Disk::ReadRequest(unsigned sectorNumber, char *data)
{
    ASSERT(data != nullptr);

    int ticks = ComputeLatency(sectorNumber, false);

    ASSERT(!active);  // only one request at a time
    ASSERT(sectorNumber >= 0 && sectorNumber < NUM_SECTORS);

    DEBUG('d', "Reading from sector %u\n", sectorNumber);
    Lseek(fileno, SECTOR_SIZE * sectorNumber + MAGIC_SIZE, 0);
    Read(fileno, data, SECTOR_SIZE);
    if (debug.IsEnabled('d'))
        PrintSector(false, sectorNumber, data);

    active = true;
    UpdateLast(sectorNumber);
    stats->numDiskReads++;
    interrupt->Schedule(DiskDone, this, ticks, DISK_INT);
}

void
Disk::WriteRequest(unsigned sectorNumber, const char *data)
{
    ASSERT(data != nullptr);

    int ticks = ComputeLatency(sectorNumber, true);

    ASSERT(!active);
    ASSERT(sectorNumber >= 0 && sectorNumber < NUM_SECTORS);

    DEBUG('d', "Writing to sector %u\n", sectorNumber);
    Lseek(fileno, SECTOR_SIZE * sectorNumber + MAGIC_SIZE, 0);
    WriteFile(fileno, data, SECTOR_SIZE);
    if (debug.IsEnabled('d'))
        PrintSector(true, sectorNumber, data);

    active = true;
    UpdateLast(sectorNumber);
    stats->numDiskWrites++;
    interrupt->Schedule(DiskDone, this, ticks, DISK_INT);
}

/// Called when it is time to invoke the disk interrupt handler, to tell the
/// Nachos kernel that the disk request is done.
void
Disk::HandleInterrupt()
{
    active = false;
    (*handler)(handlerArg);
}

static inline unsigned
Diff(unsigned a, unsigned b)
{
    return a > b ? a - b : b - a;
}

/// Returns how long it will take to position the disk head over the correct
/// track on the disk.  Since when we finish seeking, we are likely to be in
/// the middle of a sector that is rotating past the head, we also return how
/// long until the head is at the next sector boundary.
///
/// Disk seeks at one track per `SEEK_TIME` ticks (cf. `stats.hh`) and
/// rotates at one sector per `ROTATION_TIME` ticks.
unsigned
Disk::TimeToSeek(unsigned newSector, unsigned *rotation)
{
    ASSERT(rotation != nullptr);

    unsigned newTrack = newSector / SECTORS_PER_TRACK;
    unsigned oldTrack = lastSector / SECTORS_PER_TRACK;
    unsigned seek = Diff(newTrack, oldTrack) * SEEK_TIME;
      // How long will seek take?
    unsigned over = (stats->totalTicks + seek) % ROTATION_TIME;
      // Will we be in the middle of a sector when we finish the seek?

    *rotation = 0;
    if (over > 0)  // If so, need to round up to next full sector.
       *rotation = ROTATION_TIME - over;
    return seek;
}

/// Return number of sectors of rotational delay between target sector `to`
/// and current sector position `from`.
unsigned
Disk::ModuloDiff(unsigned to, unsigned from)
{
    unsigned toOffset   = to % SECTORS_PER_TRACK;
    unsigned fromOffset = from % SECTORS_PER_TRACK;

    return (toOffset - fromOffset + SECTORS_PER_TRACK) % SECTORS_PER_TRACK;
}

/// Return how long will it take to read/write a disk sector, from
/// the current position of the disk head.
///
///     Latency = seek time + rotational latency + transfer time
///
/// Disk seeks at one track per `SEEK_TIME` ticks (cf. `stats.hh`) and
/// rotates at one sector per `ROTATION_TIME` ticks.
///
/// To find the rotational latency, we first must figure out where the disk
/// head will be after the seek (if any).  We then figure out how long it
/// will take to rotate completely past newSector after that point.
///
/// The disk also has a "track buffer"; the disk continuously reads the
/// contents of the current disk track into the buffer.  This allows read
/// requests to the current track to be satisfied more quickly.  The contents
/// of the track buffer are discarded after every seek to a new track.
int
Disk::ComputeLatency(unsigned newSector, bool writing)
{
    unsigned rotation;
    unsigned seek      = TimeToSeek(newSector, &rotation);
    unsigned timeAfter = stats->totalTicks + seek + rotation;

#ifndef NOTRACKBUF  // Turn this on if you do not want the track buffer
                    // stuff.
    // Check if track buffer applies.
    if (!writing && seek == 0
        && (timeAfter - bufferInit) / ROTATION_TIME
           > ModuloDiff(newSector, bufferInit / ROTATION_TIME)) {
        DEBUG('d', "Request latency = %u\n", ROTATION_TIME);
        return ROTATION_TIME;
          // Time to transfer sector from the track buffer.
    }
#endif

    rotation += ModuloDiff(newSector, timeAfter / ROTATION_TIME)
                * ROTATION_TIME;

    DEBUG('d', "Request latency = %u\n", seek + rotation + ROTATION_TIME);
    return seek + rotation + ROTATION_TIME;
}

/// Keep track of the most recently requested sector.  So we can know what is
/// in the track buffer.
void
Disk::UpdateLast(unsigned newSector)
{
    unsigned rotate;
    unsigned seek = TimeToSeek(newSector, &rotate);

    if (seek != 0)
        bufferInit = stats->totalTicks + seek + rotate;
    lastSector = newSector;
    DEBUG('d', "Updating last sector = %u, %u\n", lastSector, bufferInit);
}
