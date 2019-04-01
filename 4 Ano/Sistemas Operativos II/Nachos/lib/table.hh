/// A very simple map from non-negative integers to some type.
///
/// Copyright (c) 2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_LIB_TABLE__HH
#define NACHOS_LIB_TABLE__HH


#include "list.hh"


template <class T>
class Table {
public:
    static const unsigned SIZE = 20;

    Table();

    int Add(T item);

    T Get(int i) const;

    bool HasKey(int i) const;

    bool IsEmpty() const;

    T Remove(int i);

private:
    /// Data items.
    T data[SIZE];

    /// Current greatest index for a new item.
    int current;

    /// A list to store indexes of items that have been freed and are not
    /// among those with greatest numbers, so it is not possible to modify
    /// `current`.  In other words, this keeps track of external
    /// fragmentation.
    List<int> freed;
};


template <class T>
Table<T>::Table()
{
    current = 0;
}


template <class T>
int
Table<T>::Add(T item)
{
    int i;

    if (!freed.IsEmpty()) {
        i = freed.Pop();
        data[i] = item;
        return i;
    } else if (current < static_cast<int>(SIZE)) {
        i = current++;
        data[i] = item;
        return i;
    } else {
        return -1;
    }
}

template <class T>
T
Table<T>::Get(int i) const
{
    ASSERT(i >= 0);

    if (freed.Has(i) || i >= current) {
        return T();
    }

    return data[i];
}

template <class T>
bool
Table<T>::HasKey(int i) const
{
    ASSERT(i >= 0);

    return !(freed.Has(i) || i >= current);
}

template <class T>
bool
Table<T>::IsEmpty() const
{
    return current == 0;
}

template <class T>
T
Table<T>::Remove(int i)
{
    ASSERT(i >= 0);

    if (!HasKey(i)) {
        return T();
    }

    if (i == current - 1) {
        current--;
        for (int j = current - 1; j >= 0 && !HasKey(j); j--) {
            ASSERT(freed.Has(j));
            freed.SortedPop(&j);
            current--;
        }
    } else {
        freed.SortedInsert(i, i);
    }
    return data[i];
}


#endif
