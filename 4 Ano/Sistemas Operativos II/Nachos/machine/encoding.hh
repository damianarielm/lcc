/// Internal data structures for simulating the MIPS instruction set.
///
/// DO NOT CHANGE -- part of the machine emulation
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_MACHINE_ENCODING__HH
#define NACHOS_MACHINE_ENCODING__HH


/// OpCode values.
///
/// The names are straight from the MIPS manual except for the following
/// special ones:
///
/// `OP_UNIMP`
///     Means that this instruction is legal, but has not been implemented
///     in the simulator yet.
/// `OP_RES`
///     Means that this is a reserved opcode (it is not supported by the
///     architecture).
enum {
    OP_ADD      =  1,
    OP_ADDI     =  2,
    OP_ADDIU    =  3,
    OP_ADDU     =  4,
    OP_AND      =  5,
    OP_ANDI     =  6,
    OP_BEQ      =  7,
    OP_BGEZ     =  8,
    OP_BGEZAL   =  9,
    OP_BGTZ     = 10,
    OP_BLEZ     = 11,
    OP_BLTZ     = 12,
    OP_BLTZAL   = 13,
    OP_BNE      = 14,

    OP_DIV      = 16,
    OP_DIVU     = 17,
    OP_J        = 18,
    OP_JAL      = 19,
    OP_JALR     = 20,
    OP_JR       = 21,
    OP_LB       = 22,
    OP_LBU      = 23,
    OP_LH       = 24,
    OP_LHU      = 25,
    OP_LUI      = 26,
    OP_LW       = 27,
    OP_LWL      = 28,
    OP_LWR      = 29,

    OP_MFHI     = 31,
    OP_MFLO     = 32,

    OP_MTHI     = 34,
    OP_MTLO     = 35,
    OP_MULT     = 36,
    OP_MULTU    = 37,
    OP_NOR      = 38,
    OP_OR       = 39,
    OP_ORI      = 40,
    OP_RFE      = 41,
    OP_SB       = 42,
    OP_SH       = 43,
    OP_SLL      = 44,
    OP_SLLV     = 45,
    OP_SLT      = 46,
    OP_SLTI     = 47,
    OP_SLTIU    = 48,
    OP_SLTU     = 49,
    OP_SRA      = 50,
    OP_SRAV     = 51,
    OP_SRL      = 52,
    OP_SRLV     = 53,
    OP_SUB      = 54,
    OP_SUBU     = 55,
    OP_SW       = 56,
    OP_SWL      = 57,
    OP_SWR      = 58,
    OP_XOR      = 59,
    OP_XORI     = 60,
    OP_SYSCALL  = 61,

    OP_UNIMP    = 62,
    OP_RES      = 63,

    MAX_OPCODE  = 63
};

/// Miscellaneous definitions.

template<typename T>
inline T
IndexToAddr(T x)
{
    return x << 2;
}

static const unsigned SIGN_BIT = 0x80000000;

/// The table below is used to translate bits 31:26 of the instruction into a
/// value suitable for the `opCode` field of a `MemWord` structure, or into a
/// special value for further decoding.

enum {
    SPECIAL = 100,
    BCOND   = 101
};

enum {
    IFMT = 1,
    JFMT = 2,
    RFMT = 3
};

struct OpInfo {
    int opCode;  ///< Translated op code.
    int format;  ///< Format type (IFMT or JFMT or RFMT).
};

extern const OpInfo OP_TABLE[];

/// This table is used to convert the `funct` field of SPECIAL instructions
/// into the `opCode` field of a `MemWord`.
extern const int SPECIAL_TABLE[];


/// Stuff to help print out each instruction, for debugging.

enum RegType {
    NONE,
    RS,
    RT,
    RD,
    EXTRA
};

struct OpString {
    const char *string;  ///< Printed version of instruction.
    RegType     args[3];
};

extern const struct OpString OP_STRINGS[];


#endif
