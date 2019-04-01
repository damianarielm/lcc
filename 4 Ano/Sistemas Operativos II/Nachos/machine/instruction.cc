/// DO NOT CHANGE -- part of the machine emulation
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "instruction.hh"
#include "encoding.hh"
#include "../lib/utility.hh"


/// Decode a MIPS instruction.
void
Instruction::Decode()
{
    const OpInfo *opPtr;

    rs = value >> 21 & 0x1F;
    rt = value >> 16 & 0x1F;
    rd = value >> 11 & 0x1F;
    opPtr  = &OP_TABLE[value >> 26 & 0x3F];
    opCode = opPtr->opCode;
    if (opPtr->format == IFMT) {
        extra = value & 0xFFFF;
        if (extra & 0x8000)
            extra |= 0xFFFF0000;
    } else if (opPtr->format == RFMT)
        extra = value >> 6 & 0x1F;
    else
        extra = value & 0x3FFFFFF;

    if (opCode == SPECIAL)
        opCode = SPECIAL_TABLE[value & 0x3F];
    else if (opCode == BCOND) {
        int i = value & 0x1F0000;

        if (i == 0)
            opCode = OP_BLTZ;
        else if (i == 0x10000)
            opCode = OP_BGEZ;
        else if (i == 0x100000)
            opCode = OP_BLTZAL;
        else if (i == 0x110000)
            opCode = OP_BGEZAL;
        else
            opCode = OP_UNIMP;
    }
}

int
Instruction::RegFromType(RegType t) const
{
    switch (t) {
        case RS:
            return rs;
        case RT:
            return rt;
        case RD:
            return rd;
        case EXTRA:
            return extra;
        case NONE:
            return 0;
        default:
            ASSERT(false);
            return -1;
    }
}
