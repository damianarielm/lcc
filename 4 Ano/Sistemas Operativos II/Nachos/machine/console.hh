/// Data structures to simulate the behavior of a terminal I/O device.
///
/// A terminal has two parts -- a keyboard input, and a display output, each
/// of which produces/accepts characters sequentially.
///
/// The console hardware device is asynchronous.  When a character is written
/// to the device, the routine returns immediately, and an interrupt handler
/// is called later when the I/O completes.  For reads, an interrupt handler
/// is called when a character arrives.
///
/// The user of the device can specify the routines to be called when the
/// read/write interrupts occur.  There is a separate interrupt for read and
/// write, and the device is “duplex” -- a character can be outgoing and
/// incoming at the same time.
///
/// DO NOT CHANGE -- part of the machine emulation
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_MACHINE_CONSOLE__HH
#define NACHOS_MACHINE_CONSOLE__HH


#include "lib/utility.hh"


/// The following class defines a hardware console device.
///
/// Input and output to the device is simulated by reading and writing to
/// UNIX files (`readFile` and `writeFile`).
///
/// Since the device is asynchronous, the interrupt handler `readAvail` is
/// called when a character has arrived, ready to be read in.  The interrupt
/// handler `writeDone` is called when an output character has been “put”, so
/// that the next character can be written.
class Console {
public:

    /// Initialize the hardware console device.
    Console(const char *readFile, const char *writeFile,
            VoidFunctionPtr readAvail, VoidFunctionPtr writeDone,
            void *callArg);

    /// Clean up console emulation.
    ~Console();

    /// External interface -- Nachos kernel code can call these.

    /// Write `ch` to the console display, and return immediately.
    /// `writeHandler` is called when the I/O completes.
    void PutChar(char ch);

    /// Poll the console input.  If a char is available, return it.
    /// Otherwise, return EOF.  `readHandler` is called whenever there is a
    /// char to be gotten.
    char GetChar();

    // Internal emulation routines -- DO NOT call these.
    // Internal routines to signal I/O completion.

    void WriteDone();
    void CheckCharAvail();

  private:
    int readFileNo;  ///< UNIX file emulating the keyboard.
    int writeFileNo;  ///< UNIX file emulating the display.
    VoidFunctionPtr writeHandler;  ///< Interrupt handler to call when the
                                   ///< `PutChar` I/O completes.
    VoidFunctionPtr readHandler;  ///< Interrupt handler to call when a
                                  ///< character arrives from the keyboard.
    void *handlerArg;  ///< argument to be passed to the interrupt handlers.
    bool putBusy;  ///< Is a `PutChar` operation in progress?  If so, you
                   ///< cannot do another one!
    char incoming;  ///< Contains the character to be read, if there is one
                    ///< available.  Otherwise contains EOF.
};


#endif  // CONSOLE_H
