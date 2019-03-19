/// Simple test case for the threads assignment.
///
/// Create several threads, and have them context switch back and forth
/// between themselves by calling `Thread::Yield`, to illustrate the inner
/// workings of the thread system.
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2007-2009 Universidad de Las Palmas de Gran Canaria.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "system.hh"


/// Loop 10 times, yielding the CPU to another ready thread each iteration.
///
/// * `name` points to a string with a thread name, just for debugging
///   purposes.
void
SimpleThread(void *name_)
{
    // Reinterpret arg `name` as a string.
    char *name = (char *) name_;

    // If the lines dealing with interrupts are commented, the code will
    // behave incorrectly, because printf execution may cause race
    // conditions.
    for (unsigned num = 0; num < 10; num++) {
        printf("*** Thread `%s` is running: iteration %u\n", name, num);
        currentThread->Yield();
    }
    printf("!!! Thread `%s` has finished\n", name);
}

/// Set up a ping-pong between several threads.
///
/// Do it by launching ten threads which call `SimpleThread`, and finally
/// calling `SimpleThread` ourselves.
void
ThreadTest()
{
    DEBUG('t', "Entering thread test\n");

    char *name2 = new char [64];
    strncpy(name2, "2nd", 64);
    Thread *newThread2 = new Thread(name2);
    
    char *name3 = new char [64];
    strncpy(name3, "3rd", 64);
    Thread *newThread3 = new Thread(name3);

    char *name4 = new char [64];
    strncpy(name4, "4th", 64);
    Thread *newThread4 = new Thread(name4);

    char *name5 = new char [64];
    strncpy(name5, "5th", 64);
    Thread *newThread5 = new Thread(name5);

    newThread2->Fork(SimpleThread, (void *) name2);
    newThread3->Fork(SimpleThread, (void *) name3);
    newThread4->Fork(SimpleThread, (void *) name4);
    newThread5->Fork(SimpleThread, (void *) name5);

    SimpleThread((void *) "1st");
}
