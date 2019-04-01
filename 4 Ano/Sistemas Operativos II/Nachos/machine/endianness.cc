/// Routines for converting Words and Short Words to and from the simulated
/// machine's format of little endian.  These end up being NOPs when the host
/// machine is also little endian (DEC and Intel).


#include "endianness.hh"


unsigned
WordToHost(unsigned word)
{
#ifdef HOST_IS_BIG_ENDIAN
     unsigned long result;
     result  = word >> 24 & 0x000000FF;
     result |= word >>  8 & 0x0000FF00;
     result |= word <<  8 & 0x00FF0000;
     result |= word << 24 & 0xFF000000;
     return result;
#else
     return word;
#endif
}

unsigned short
ShortToHost(unsigned short shortword)
{
#ifdef HOST_IS_BIG_ENDIAN
     unsigned short result;
     result  = shortword << 8 & 0xFF00;
     result |= shortword >> 8 & 0x00FF;
     return result;
#else
     return shortword;
#endif
}

unsigned
WordToMachine(unsigned word)
{
    return WordToHost(word);
}

unsigned short
ShortToMachine(unsigned short shortword)
{
    return ShortToHost(shortword);
}
