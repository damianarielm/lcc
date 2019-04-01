/// Nachos initialization and cleanup routines.
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "system.hh"
#include "preemptive.hh"

#ifdef USER_PROGRAM
#include "userprog/debugger.hh"
#include "userprog/exception.hh"
#endif


/// This defines *all* of the global data structures used by Nachos.
///
/// These are all initialized and de-allocated by this file.

Thread *currentThread;        ///< The thread we are running now.
Thread *threadToBeDestroyed;  ///< The thread that just finished.
Scheduler *scheduler;         ///< The ready list.
Interrupt *interrupt;         ///< Interrupt status.
Statistics *stats;            ///< Performance metrics.
Timer *timer;                 ///< The hardware timer device, for invoking
                              ///< context switches.

// 2007, Jose Miguel Santos Espino
PreemptiveScheduler *preemptiveScheduler = nullptr;
const long long DEFAULT_TIME_SLICE = 50000;

#ifdef FILESYS_NEEDED
FileSystem *fileSystem;
#endif

#ifdef FILESYS
SynchDisk *synchDisk;
#endif

#ifdef USER_PROGRAM  // Requires either *FILESYS* or *FILESYS_STUB*.
Machine *machine;  ///< User program memory and registers.
#endif

#ifdef NETWORK
PostOffice *postOffice;
#endif

// External definition, to allow us to take a pointer to this function.
extern void Cleanup();

/// Interrupt handler for the timer device.
///
/// The timer device is set up to interrupt the CPU periodically (once every
/// `TimerTicks`).  This routine is called each time there is a timer
/// interrupt, with interrupts disabled.
///
/// Note that instead of calling `Yield` directly (which would suspend the
/// interrupt handler, not the interrupted thread which is what we wanted to
/// context switch), we set a flag so that once the interrupt handler is
/// done, it will appear as if the interrupted thread called Yield at the
/// point it is was interrupted.
///
/// * `dummy` is because every interrupt handler takes one argument, whether
///   it needs it or not.
static void
TimerInterruptHandler(void *dummy)
{
    if (interrupt->GetStatus() != IDLE_MODE)
        interrupt->YieldOnReturn();
}

/// Initialize Nachos global data structures.
///
/// Interpret command line arguments in order to determine flags for the
/// initialization.
///
/// * `argc` is the number of command line arguments (including the name
///   of the command).  Example:
///       nachos -d +  ->  argc = 3
///
/// * `argv` is an array of strings, one for each command line argument.
///   Example:
///       nachos -d +  ->  argv = {"nachos", "-d", "+"}
void
Initialize(int argc, char **argv)
{
    ASSERT(argc == 0 || argv != nullptr);

    int argCount;
    const char *debugArgs = "";
    bool randomYield = false;

    // 2007, Jose Miguel Santos Espino
    bool preemptiveScheduling = false;
    long long timeSlice;

#ifdef USER_PROGRAM
    bool debugUserProg = false;  // Single step user program.
#endif
#ifdef FILESYS_NEEDED
    bool format = false;  // Format disk.
#endif
#ifdef NETWORK
    double rely = 1;  // Network reliability.
    int netname = 0;  // UNIX socket name.
#endif

    for (argc--, argv++; argc > 0; argc -= argCount, argv += argCount) {
        argCount = 1;
        if (!strcmp(*argv, "-d")) {
            if (argc == 1)
                debugArgs = "+";  // Turn on all debug flags.
            else {
                debugArgs = *(argv + 1);
                argCount = 2;
            }
        } else if (!strcmp(*argv, "-rs")) {
            ASSERT(argc > 1);
            RandomInit(atoi(*(argv + 1)));  // Initialize pseudo-random
                                            // number generator.
            randomYield = true;
            argCount = 2;
        }
        // 2007, Jose Miguel Santos Espino
        else if (!strcmp(*argv, "-p")) {
            preemptiveScheduling = true;
            if (argc == 1) {
                timeSlice = DEFAULT_TIME_SLICE;
            } else {
                timeSlice = atoi(*(argv+1));
                argCount = 2;
            }
        }
#ifdef USER_PROGRAM
        if (!strcmp(*argv, "-s"))
            debugUserProg = true;
#endif
#ifdef FILESYS_NEEDED
        if (!strcmp(*argv, "-f"))
            format = true;
#endif
#ifdef NETWORK
        if (!strcmp(*argv, "-n")) {
            ASSERT(argc > 1);
            rely = atof(*(argv + 1));
            argCount = 2;
        } else if (!strcmp(*argv, "-id")) {
            ASSERT(argc > 1);
            netname = atoi(*(argv + 1));
            argCount = 2;
        }
#endif
    }

    debug.SetFlags(debugArgs);  // Initialize `DEBUG` messages.
    stats = new Statistics;     // Collect statistics.
    interrupt = new Interrupt;  // Start up interrupt handling.
    scheduler = new Scheduler;  // Initialize the ready queue.
    if (randomYield)            // Start the timer (if needed).
        timer = new Timer(TimerInterruptHandler, 0, randomYield);

    threadToBeDestroyed = nullptr;

    // We did not explicitly allocate the current thread we are running in.
    // But if it ever tries to give up the CPU, we better have a `Thread`
    // object to save its state.
    currentThread = new Thread("main");
    currentThread->SetStatus(RUNNING);

    interrupt->Enable();
    CallOnUserAbort(Cleanup);  // If user hits ctl-C...

    // Jose Miguel Santos Espino, 2007
    if (preemptiveScheduling) {
        preemptiveScheduler = new PreemptiveScheduler();
        preemptiveScheduler->SetUp(timeSlice);
    }

#ifdef USER_PROGRAM
    Debugger *d = debugUserProg ? new Debugger : nullptr;
    machine = new Machine(d);  // This must come first.
    SetExceptionHandlers();
#endif

#ifdef FILESYS
    synchDisk = new SynchDisk("DISK");
#endif

#ifdef FILESYS_NEEDED
    fileSystem = new FileSystem(format);
#endif

#ifdef NETWORK
    postOffice = new PostOffice(netname, rely, 10);
#endif
}

/// Nachos is halting.  De-allocate global data structures.
void
Cleanup()
{
    DEBUG('i', "Cleaning up...\n");

    // 2007, Jose Miguel Santos Espino
    delete preemptiveScheduler;

#ifdef NETWORK
    delete postOffice;
#endif

#ifdef USER_PROGRAM
    delete machine;
#endif

#ifdef FILESYS_NEEDED
    delete fileSystem;
#endif

#ifdef FILESYS
    delete synchDisk;
#endif

    delete timer;
    delete scheduler;
    delete interrupt;

    exit(0);
}
