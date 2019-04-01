/// A data structure defining a bitmap -- an array of bits each of which can
/// be either on or off.  It is also known as a bit array, bit set or bit
/// vector.
///
/// The bitmap is represented as an array of unsigned integers, on which we
/// do modulo arithmetic to find the bit we are interested in.
///
/// The data structure is parameterized with with the number of bits being
/// managed.
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#ifndef NACHOS_LIB_BITMAP__HH
#define NACHOS_LIB_BITMAP__HH


#include "utility.hh"
#include "filesys/open_file.hh"


/// Definitions helpful for representing a bitmap as an array of integers.

const unsigned BITS_IN_BYTE = 8;
const unsigned BITS_IN_WORD = 32;


/// A “bitmap” -- an array of bits, each of which can be independently set,
/// cleared, and tested.
///
/// Most useful for managing the allocation of the elements of an array --
/// for instance, disk sectors, or main memory pages.
///
/// Each bit represents whether the corresponding sector or page is in use
/// or free.
class Bitmap {
public:

    /// Initialize a bitmap with `nitems` bits; all bits are cleared.
    ///
    /// * `nitems` is the number of items in the bitmap.
    Bitmap(unsigned nitems);

    /// Uninitialize a bitmap.
    ~Bitmap();

    /// Set the “nth” bit.
    void Mark(unsigned which);

    /// Clear the “nth” bit.
    void Clear(unsigned which);

    /// Is the “nth” bit set?
    bool Test(unsigned which) const;

    /// Return the index of a clear bit, and as a side effect, set the bit.
    ///
    /// If no bits are clear, return -1.
    int Find();

    /// Return the number of clear bits.
    unsigned CountClear() const;

    /// Print contents of bitmap.
    void Print() const;

    /// Fetch contents from disk.
    ///
    /// Note: this is not needed until the *FILESYS* assignment, when we will
    /// need to read and write the bitmap to a file.
    void FetchFrom(OpenFile *file);

    /// Write contents to disk.
    ///
    /// Note: this is not needed until the *FILESYS* assignment, when we will
    /// need to read and write the bitmap to a file.
    void WriteBack(OpenFile *file) const;

private:

    /// Number of bits in the bitmap.
    unsigned numBits;

    /// Number of words of bitmap storage (rounded up if `numBits` is not a
    /// multiple of the number of bits in a word).
    unsigned numWords;

    /// Bit storage.
    unsigned *map;

};


#endif
