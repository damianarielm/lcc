/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_MACHINE_INSTRUCTION__HH
#define NACHOS_MACHINE_INSTRUCTION__HH


#include "encoding.hh"


/// The following class defines an instruction, represented in both:
/// * undecoded binary form;
/// * decoded to identify:
///   * operation to do;
///   * registers to act on;
///   * any immediate operand value.
class Instruction {
public:

    /// Decode the binary representation of the instruction.
    void Decode();

    /// Retrieve the register number referred to in an instruction.
    int RegFromType(RegType reg) const;

    unsigned value;  //< Binary representation of the instruction.

    unsigned char opCode;  ///< Type of instruction.  This is NOT the same as
                           ///< the opcode field from the instruction: see
                           ///< defs in `encoding.hh`.
    unsigned char rs, rt, rd;  ///< Three registers from instruction.
    int extra;  ///< Immediate or target or shamt field or offset.
                ///< Immediates are sign-extended.
};


#endif
