/// Data structures for synchronized access to a list.
///
/// Implemented by surrounding the `List` abstraction with synchronization
/// routines.
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_THREADS_SYNCHLIST__HH
#define NACHOS_THREADS_SYNCHLIST__HH


#include "synch.hh"
#include "lib/list.hh"


/// The following class defines a "synchronized list" -- a list for which
/// these constraints hold:
///
/// 1. Threads trying to remove an item from a list will wait until the list
///    has an element on it.
/// 2. One thread at a time can access list data structures.
template <class Item>
class SynchList {
public:

    /// Initialize a synchronized list.
    SynchList();

    // De-allocate a synchronized list.
    ~SynchList();

    /// Append item to the end of the list, and wake up any thread waiting in
    /// remove.
    void Append(Item item);

    /// Remove the first item from the front of the list, waiting if the list
    /// is empty.
    Item Pop();

    /// Apply function to every item in the list.
    void Apply(void (*func)(Item));

private:

    // The unsynchronized list.
    List<Item> *list;

    // Enforce mutual exclusive access to the list.
    Lock *lock;

    // Wait in `Pop` if the list is empty.
    Condition *listEmpty;

};

/// Allocate and initialize the data structures needed for a synchronized
/// list, empty to start with.
///
/// Elements can now be added to the list.
template <class Item>
SynchList<Item>::SynchList()
{
    list      = new List<Item>;
    lock      = new Lock("list lock");
    listEmpty = new Condition("list empty cond", lock);
    // original // listEmpty = new Condition("list empty cond");
}

/// De-allocate the data structures created for synchronizing a list.
template <class Item>
SynchList<Item>::~SynchList()
{
    delete list;
    delete lock;
    delete listEmpty;
}

/// Append an “item” to the end of the list.  Wake up anyone waiting for an
/// element to be appended.
///
/// * `item` is the thing to put on the list
template <class Item>
void
SynchList<Item>::Append(Item item)
{
    lock->Acquire();      // Enforce mutual exclusive access to the list.
    list->Append(item);
    listEmpty->Signal();  // Wake up a waiter, if any.
    // original // listEmpty->Signal(lock);    // wake up a waiter, if any
    lock->Release();
}

/// Remove an “item” from the beginning of the list.  Wait if the list is
/// empty.
///
/// Returns the removed item.
template <class Item>
Item
SynchList<Item>::Pop()
{
    Item item;

    lock->Acquire();    // Enforce mutual exclusion.
    while (list->IsEmpty())
    listEmpty->Wait();  // Wait until list is not empty.
    // Original: //listEmpty->Wait(lock);  // Wait until list is not empty.
    item = list->Pop();
    //ASSERT(item != nullptr);
    lock->Release();
    return item;
}

/// Apply function to every item on the list.
///
/// Obey mutual exclusion constraints.
///
/// * `func` is the procedure to be applied.
template <class Item>
void
SynchList<Item>::Apply(void (*func)(Item))
{
    ASSERT(func != nullptr);
    lock->Acquire();
    list->Apply(func);
    lock->Release();
}


#endif
