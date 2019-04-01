/// Synchronization primitives
///
/// Data structures for synchronizing threads.
///
/// Three synchronization mechanisms are defined here: semaphores, locks and
/// condition variables. Only semaphores are implemented; for locks and
/// condition variables, only the interface is provided. Precisely, the first
/// task involves developing this implementation.
///
/// All synchronization objects have a `name` parameter in the constructor;
/// its only aim is to ease debugging the program.
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2000      José Miguel Santos Espino - ULPGC.
///               2016-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_THREADS_SYNCH__HH
#define NACHOS_THREADS_SYNCH__HH


#include "thread.hh"
#include "lib/list.hh"


/// This class defines a “semaphore”, which has a positive integer as its
/// value.
///
/// Semaphores offer only two operations:
///
/// * `P` -- wait until `value > 0`, then decrement `value`.
/// * `V` -- increment `value`, awaken a waiting thread if any.
///
/// Observe that this interface does *not* allow to read the semaphore value
/// directly -- even if you were able to read it, it would serve for nothing,
/// because meanwhile another thread could have modified the semaphore, in
/// case you have lost the CPU for some time.
class Semaphore {
public:

    /// Constructor: give an initial value to the semaphore.
    ///
    /// Set initial value.
    Semaphore(const char *debugName, int initialValue);

    ~Semaphore();

    /// For debugging.
    const char *GetName() const;

    /// The only public operations on the semaphore.
    ///
    /// Both of them must be *atomic*.
    void P();
    void V();

private:

    /// For debugging.
    const char *name;

    /// Semaphore value, it is always `>= 0`.
    int value;

    /// Queue of threads waiting on `P` because the value is zero.
    List<Thread *> *queue;

};

/// This class defines a “lock”.
///
/// A lock can have two states: free and busy. Only two operations are
/// allowed on locks:
///
/// * `Acquire` -- wait until the lock is free and mark is as busy.
/// * `Release` -- mark the lock as free, thereby awakening some other thread
///   that were blocked on an `Acquired`.
///
/// For convenience, nobody but the thread that holds the lock can free it.
/// There is no operation for reading the state of the lock.
class Lock {
public:

    /// Constructor: set up the lock as free.
    Lock(const char *debugName);

    ~Lock();

    /// For debugging.
    const char *GetName() const;

    /// Operations on the lock.
    ///
    /// Both must be *atomic*.
    void Acquire();
    void Release();

    /// Returns `true` if the current thread is the one that possesses the
    /// lock.
    ///
    /// Useful for checks in `Release` and in condition variables.
    bool IsHeldByCurrentThread() const;

private:

    /// For debugging.
    const char *name;

    // Add other needed fields here.
};

// This class defined a “condition variable”.
//
// A condition variable does not have any value.  It is used for enqueuing
// threads that are waiting (`Wait`) that another thread informs them of
// something (`Signal`).  Condition variables are bound to a lock (`Lock`).
//
// These are the three operations on condition variables:
//
// * `Wait` -- free the lock and displace the thread from the CPU.  The
//   thread will wait until someone sends it a `Signal`.
// * `Signal` -- if there is someone waiting on the variable, awaken one of
//   the threads. If there is none waiting, nothing occurs.
// * `Broadcast` -- awaken all waiting threads.
//
// All operations on a condition variable must be performed after having
// acquired the lock.  This means that operations on condition variables must
// be executed in mutual exclusion.
//
// Nachos' condition variables should work according to the “Mesa” style.
// When a `Signal` or `Broadcast` awakens another thread, this is put in the
// ready queue.  The woken thread is responsible for acquiring the lock
// again.  This has to be implemented in the body of the `Wait` function.
//
// In contrast, there exists another style of condition variables, the
// “Hoare” style: according to it, `Signal` loses control of the lock and
// delivers the CPU to the woken thread; this is run immediately and when the
// lock is freed, the thread returns control to the thread that performed the
// `Signal`.
//
// The “Mesa” style is somewhat simpler to implement, but it does not
// guarantee that the woken thread recover the control of the lock
// immediately.
class Condition {
public:

    // Constructor: indicate which lock the condition variable belongs to.
    Condition(const char *debugName, Lock *conditionLock);

    ~Condition();

    const char *GetName() const;

    /// The three operations on condition variables.
    ///
    /// The thread that invokes any of these operations must hold the
    /// corresponding lock; otherwise an error must occur.

    void Wait();
    void Signal();
    void Broadcast();

private:

    const char *name;

    // Other needed fields are to be added here.
};


#endif
