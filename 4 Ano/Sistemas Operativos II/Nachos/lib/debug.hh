/// Debugging routines.
///
/// The debugging routines allow the user to turn on selected debugging
/// messages, controllable from the command line arguments passed to Nachos
/// (`-d`).  You are encouraged to add your own debugging flags.  The
/// pre-defined debugging flags are:
///
/// * `+` -- turn on all debug messages.
/// * `t` -- thread system.
/// * `s` -- semaphores, locks, and conditions.
/// * `i` -- interrupt emulation.
/// * `m` -- machine emulation (requires *USER_PROGRAM*).
/// * `d` -- disk emulation (requires *FILESYS*).
/// * `f` -- file system (requires *FILESYS*).
/// * `a` -- address spaces (requires *USER_PROGRAM*).
/// * `n` -- network emulation (requires *NETWORK*).
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#ifndef NACHOS_LIB_DEBUG__HH
#define NACHOS_LIB_DEBUG__HH


/// Interface to debugging routines.
class Debug {
public:

    /// No flag is set at the beginning, so no debug message would be
    /// printed until `SetFlags` is called.
    Debug();

    /// Is this debug flag enabled?
    bool IsEnabled(char flag) const;

    /// Get the current flags.
    const char *GetFlags() const;

    /// Set debug flags to indicate which debug messages to print.
    ///
    /// Debug messages are printed only if they have a flag contained in
    /// `new_flags`.
    ///
    /// If the flag is `+`, we enable all debug messages.
    ///
    /// * `new_flags` is a string of characters for whose debug messages are
    ///   to be enabled.
    void SetFlags(const char *new_flags);

    /// Print a debug message if `flag` is enabled.
    ///
    /// Like `printf`, only with an extra argument on the front.
    ///
    /// Put a flag prefix along with the message.
    void Print(char flag, const char *format, ...) const;

    /// Same as `Print` but avoid printing the flag prefix.
    ///
    /// Useful for splitting a call for a `Print` line into multiple calls.
    void PrintCont(char flag, const char *format, ...) const;

private:
    /// String that controls which debug messages are printed.
    const char *flags;
};


#endif
