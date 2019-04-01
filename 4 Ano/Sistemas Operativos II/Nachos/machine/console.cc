/// Routines to simulate a serial port to a console device.
///
/// A console has input (a keyboard) and output (a display).  These are each
/// simulated by operations on UNIX files.  The simulated device is
/// asynchronous, so we have to invoke the interrupt handler (after a
/// simulated delay), to signal that a byte has arrived and/or that a written
/// byte has departed.
///
/// DO NOT CHANGE -- part of the machine emulation
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "console.hh"
#include "threads/system.hh"


/// Dummy functions because C++ is weird about pointers to member functions.

static void
ConsoleReadPoll(void *c)
{
    ASSERT(c != nullptr);
    Console *console = (Console *) c;
    console->CheckCharAvail();
}

static void
ConsoleWriteDone(void *c)
{
    ASSERT(c != nullptr);
    Console *console = (Console *) c;
    console->WriteDone();
}

/// Initialize the simulation of a hardware console device.
///
/// * `readFile` is a UNIX file simulating the keyboard (when null, use
///   stdin).
/// * `writeFile` is a UNIX file simulating the display (when null, use
///   stdout).
/// * `readAvail` is the interrupt handler called when a character arrives
///   from the keyboard.
/// * `writeDone` is the interrupt handler called when a character has been
///   output, so that it is ok to request the next char be output.
Console::Console(const char *readFile, const char *writeFile,
        VoidFunctionPtr readAvail,
        VoidFunctionPtr writeDone, void *callArg)
{
    ASSERT(readAvail != nullptr);
    ASSERT(writeDone != nullptr);

    if (readFile == nullptr)
        readFileNo = 0;  // keyboard = stdin
    else
        readFileNo = OpenForReadWrite(readFile, true);
    // should be read-only
    if (writeFile == nullptr)
        writeFileNo = 1;  // display = stdout
    else
        writeFileNo = OpenForWrite(writeFile);

    // Set up the stuff to emulate asynchronous interrupts.
    writeHandler = writeDone;
    readHandler  = readAvail;
    handlerArg   = callArg;
    putBusy      = false;
    incoming     = EOF;

    // Start polling for incoming packets.
    interrupt->Schedule(ConsoleReadPoll, this,
                        CONSOLE_TIME, CONSOLE_READ_INT);
}

/// Clean up console emulation.
Console::~Console()
{
    if (readFileNo != 0)
        Close(readFileNo);
    if (writeFileNo != 1)
        Close(writeFileNo);
}

/// Periodically called to check if a character is available for
/// input from the simulated keyboard (eg, has it been typed?).
///
/// Only read it in if there is buffer space for it (if the previous
/// character has been grabbed out of the buffer by the Nachos kernel).
/// Invoke the “read” interrupt handler, once the character has been put into
/// the buffer.
    void
Console::CheckCharAvail()
{
    char c;

    // Schedule the next time to poll for a packet.
    interrupt->Schedule(ConsoleReadPoll, this,
            CONSOLE_TIME, CONSOLE_READ_INT);

    // Do nothing if character is already buffered, or none to be read.
    if (incoming != EOF || !PollFile(readFileNo))
        return;

    // Otherwise, read character and tell user about it.
    Read(readFileNo, &c, sizeof c);
    incoming = c;
    stats->numConsoleCharsRead++;
    (*readHandler)(handlerArg);
}

/// Internal routine called when it is time to invoke the interrupt handler
/// to tell the Nachos kernel that the output character has completed.
void
Console::WriteDone()
{
    putBusy = false;
    stats->numConsoleCharsWritten++;
    (*writeHandler)(handlerArg);
}

/// Read a character from the input buffer, if there is any there.
/// Either return the character, or EOF if none buffered.
char
Console::GetChar()
{
    char ch = incoming;

    incoming = EOF;
    return ch;
}

/// Write a character to the simulated display, schedule an interrupt to
/// occur in the future, and return.
void
Console::PutChar(char ch)
{
    ASSERT(!putBusy);
    WriteFile(writeFileNo, &ch, sizeof (char));
    putBusy = true;
    interrupt->Schedule(ConsoleWriteDone, this,
                        CONSOLE_TIME, CONSOLE_WRITE_INT);
}
