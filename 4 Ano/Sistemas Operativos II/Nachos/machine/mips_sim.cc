/// Simulate a MIPS R2/3000 processor.
///
/// This code has been adapted from Ousterhout's MIPSSIM package.  Byte
/// ordering is little-endian, so we can be compatible with DEC RISC systems.
///
/// DO NOT CHANGE -- part of the machine emulation
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "instruction.hh"
#include "machine.hh"
#include "threads/system.hh"


/// Simulate the execution of a user-level program on Nachos.
///
/// Called by the kernel when the program starts up; never returns.
///
/// This routine is re-entrant, in that it can be called multiple times
/// concurrently -- one for each thread executing user code.
void
Machine::Run()
{
    Instruction *instr = new Instruction;
      // Storage for decoded instruction.

    if (debug.IsEnabled('m'))
        printf("Starting to run at time %u\n", stats->totalTicks);
    interrupt->SetStatus(USER_MODE);

    for (;;) {
        if (FetchInstruction(instr))
            ExecInstruction(instr);
        interrupt->OneTick();
        if (singleStepper != nullptr && !singleStepper->Step())
            singleStepper = nullptr;
    }
}

/// Simulate effects of a delayed load.
///
/// NOTE -- `RaiseException`/`CheckInterrupts` must also call `DelayedLoad`,
/// since any delayed load must get applied before we trap to the kernel.
void
Machine::DelayedLoad(unsigned nextReg, int nextValue)
{
    registers[registers[LOAD_REG]] = registers[LOAD_VALUE_REG];
    registers[LOAD_REG] = nextReg;
    registers[LOAD_VALUE_REG] = nextValue;
    registers[0] = 0;  // And always make sure R0 stays zero.
}

bool
Machine::FetchInstruction(Instruction *instr)
{
    ASSERT(instr != nullptr);

    int raw;
    if (!ReadMem(registers[PC_REG], 4, &raw))
        return false;  // Exception occurred.
    instr->value = raw;
    instr->Decode();

    if (debug.IsEnabled('m')) {
        const struct OpString *str = &OP_STRINGS[instr->opCode];

        ASSERT(instr->opCode <= MAX_OPCODE);
        DEBUG('m', "At PC = 0x%X: ", registers[PC_REG]);
        DEBUG_CONT('m', str->string, instr->RegFromType(str->args[0]),
                        instr->RegFromType(str->args[1]),
                        instr->RegFromType(str->args[2]));
        DEBUG_CONT('m', "\n");
    }
    return true;
}

/// Simulate R2000 multiplication.
///
/// The words at `*hiPtr` and `*loPtr` are overwritten with the double-length
/// result of the multiplication.
static void
Mult(int a, int b, bool signedArith, int *hiPtr, int *loPtr)
{
    ASSERT(hiPtr != nullptr);
    ASSERT(loPtr != nullptr);

    if (a == 0 || b == 0) {
        *hiPtr = *loPtr = 0;
        return;
    }

    // Compute the sign of the result, then make everything positive so
    // unsigned computation can be done in the main loop.
    bool negative = false;
    if (signedArith) {
        if (a < 0) {
            negative = !negative;
            a = -a;
        }
        if (b < 0) {
            negative = !negative;
            b = -b;
        }
    }

    // Compute the result in unsigned arithmetic (check `a`'s bits one at a
    // time, and add in a shifted value of `b`).
    unsigned bLo = b;
    unsigned bHi = 0;
    unsigned lo = 0;
    unsigned hi = 0;
    for (unsigned i = 0; i < 32; i++) {
        if (a & 1) {
            lo += bLo;
            if (lo < bLo)  // Carry out of the low bits?
                hi += 1;
            hi += bHi;
            if ((a & 0xFFFFFFFE) == 0)
                break;
        }
        bHi <<= 1;
        if (bLo & 0x80000000)
            bHi |= 1;

        bLo <<= 1;
        a >>= 1;
    }

    // If the result is supposed to be negative, compute the two's complement
    // of the double-word result.
    if (negative) {
        hi = ~hi;
        lo = ~lo;
        lo++;
        if (lo == 0)
            hi++;
    }

    *hiPtr = (int) hi;
    *loPtr = (int) lo;
}

/// Execute one instruction from a user-level program.
///
/// If there is any kind of exception or interrupt, we invoke the exception
/// handler, and when it returns, we return to `Run`, which will re-invoke us
/// in a loop.  This allows us to re-start the instruction execution from the
/// beginning, in case any of our state has changed.  On a syscall, the OS
/// software must increment the PC so execution begins at the instruction
/// immediately after the syscall.
///
/// This routine is re-entrant, in that it can be called multiple times
/// concurrently -- one for each thread executing user code.  We get
/// re-entrancy by never caching any data -- we always re-start the
/// simulation from scratch each time we are called (or after trapping back
/// to the Nachos kernel on an exception or interrupt), and we always store
/// all data back to the machine registers and memory before leaving.  This
/// allows the Nachos kernel to control our behavior by controlling the
/// contents of memory, the translation table, and the register set.
void
Machine::ExecInstruction(const Instruction *instr)
{
    int nextLoadReg = 0;
    int nextLoadValue = 0;  // Record delayed load operation, to apply in the
                            // future.

    // Compute next pc, but do not install in case there is an error or
    // branch.
    int      pcAfter = registers[NEXT_PC_REG] + 4;
    int      sum, diff, tmp, value;
    unsigned rs, rt, imm;

    // Execute the instruction (cf. Kane's book).
    switch (instr->opCode) {

        case OP_ADD:
            sum = registers[instr->rs] + registers[instr->rt];
            if (!((registers[instr->rs] ^ registers[instr->rt]) & SIGN_BIT)
                  && (registers[instr->rs] ^ sum) & SIGN_BIT) {
                RaiseException(OVERFLOW_EXCEPTION, 0);
                return;
            }
            registers[instr->rd] = sum;
            break;

        case OP_ADDI:
            sum = registers[instr->rs] + instr->extra;
            if (!((registers[instr->rs] ^ instr->extra) & SIGN_BIT)
                  && (instr->extra ^ sum) & SIGN_BIT) {
                RaiseException(OVERFLOW_EXCEPTION, 0);
                return;
            }
            registers[instr->rt] = sum;
            break;

        case OP_ADDIU:
            registers[instr->rt] = registers[instr->rs] + instr->extra;
            break;

        case OP_ADDU:
            registers[instr->rd] = registers[instr->rs]
                                   + registers[instr->rt];
            break;

        case OP_AND:
            registers[instr->rd] = registers[instr->rs]
                                   & registers[instr->rt];
            break;

        case OP_ANDI:
            registers[instr->rt] = registers[instr->rs]
                                   & (instr->extra & 0xFFFF);
            break;

        case OP_BEQ:
            if (registers[instr->rs] == registers[instr->rt])
                pcAfter = registers[NEXT_PC_REG] + IndexToAddr(instr->extra);
            break;

        case OP_BGEZAL:
            registers[RET_ADDR_REG] = registers[NEXT_PC_REG] + 4;
        case OP_BGEZ:
            if (!(registers[instr->rs] & SIGN_BIT))
                pcAfter = registers[NEXT_PC_REG] + IndexToAddr(instr->extra);
            break;

        case OP_BGTZ:
            if (registers[instr->rs] > 0)
                pcAfter = registers[NEXT_PC_REG] + IndexToAddr(instr->extra);
            break;

        case OP_BLEZ:
            if (registers[instr->rs] <= 0)
                pcAfter = registers[NEXT_PC_REG] + IndexToAddr(instr->extra);
            break;

        case OP_BLTZAL:
            registers[RET_ADDR_REG] = registers[NEXT_PC_REG] + 4;
        case OP_BLTZ:
            if (registers[instr->rs] & SIGN_BIT)
                pcAfter = registers[NEXT_PC_REG] + IndexToAddr(instr->extra);
            break;

        case OP_BNE:
            if (registers[instr->rs] != registers[instr->rt])
                pcAfter = registers[NEXT_PC_REG] + IndexToAddr(instr->extra);
            break;

        case OP_DIV:
            if (registers[instr->rt] == 0) {
                registers[LO_REG] = 0;
                registers[HI_REG] = 0;
            } else {
                registers[LO_REG] = registers[instr->rs]
                                    / registers[instr->rt];
                registers[HI_REG] = registers[instr->rs]
                                    % registers[instr->rt];
            }
            break;

        case OP_DIVU:
            rs = (unsigned) registers[instr->rs];
            rt = (unsigned) registers[instr->rt];
            if (rt == 0) {
                registers[LO_REG] = 0;
                registers[HI_REG] = 0;
            } else {
                tmp = rs / rt;
                registers[LO_REG] = (int) tmp;
                tmp = rs % rt;
                registers[HI_REG] = (int) tmp;
            }
            break;

        case OP_JAL:
            registers[RET_ADDR_REG] = registers[NEXT_PC_REG] + 4;
        case OP_J:
            pcAfter = (pcAfter & 0xF0000000) | IndexToAddr(instr->extra);
            break;

        case OP_JALR:
            registers[instr->rd] = registers[NEXT_PC_REG] + 4;
        case OP_JR:
            pcAfter = registers[instr->rs];
            break;

        case OP_LB:
        case OP_LBU:
            tmp = registers[instr->rs] + instr->extra;
            if (!ReadMem(tmp, 1, &value))
                return;

            if (value & 0x80 && instr->opCode == OP_LB)
                value |= 0xFFFFFF00;
            else
                value &= 0xFF;
            nextLoadReg = instr->rt;
            nextLoadValue = value;
            break;

        case OP_LH:
        case OP_LHU:
            tmp = registers[instr->rs] + instr->extra;
            if (tmp & 0x1) {
                RaiseException(ADDRESS_ERROR_EXCEPTION, tmp);
                return;
            }
            if (!ReadMem(tmp, 2, &value))
                return;

            if (value & 0x8000 && instr->opCode == OP_LH)
                value |= 0xFFFF0000;
            else
                value &= 0xFFFF;
            nextLoadReg = instr->rt;
            nextLoadValue = value;
            break;

        case OP_LUI:
            DEBUG('m', "Executing: LUI r%d,%d\n", instr->rt, instr->extra);
            registers[instr->rt] = instr->extra << 16;
            break;

        case OP_LW:
            tmp = registers[instr->rs] + instr->extra;
            if (tmp & 0x3) {
                RaiseException(ADDRESS_ERROR_EXCEPTION, tmp);
                return;
            }
            if (!ReadMem(tmp, 4, &value))
                return;
            nextLoadReg = instr->rt;
            nextLoadValue = value;
            break;

        case OP_LWL:
            tmp = registers[instr->rs] + instr->extra;

            // `ReadMem` assumes all 4 byte requests are aligned on an even
            // word boundary.  Also, the little endian/big endian swap code
            // would fail (I think) if the other cases are ever exercised.
            ASSERT((tmp & 0x3) == 0);

            if (!ReadMem(tmp, 4, &value))
                return;
            if (registers[LOAD_REG] == instr->rt)
                nextLoadValue = registers[LOAD_VALUE_REG];
            else
                nextLoadValue = registers[instr->rt];
            switch (tmp & 0x3) {
                case 0:
                    nextLoadValue = value;
                    break;
                case 1:
                    nextLoadValue = (nextLoadValue & 0xFF) | value << 8;
                    break;
                case 2:
                    nextLoadValue = (nextLoadValue & 0xFFFF) | value << 16;
                    break;
                case 3:
                    nextLoadValue = (nextLoadValue & 0xFFFFFF) | value << 24;
                    break;
            }
            nextLoadReg = instr->rt;
            break;

        case OP_LWR:
            tmp = registers[instr->rs] + instr->extra;

            // `ReadMem` assumes all 4 byte requests are aligned on an even
            // word boundary.  Also, the little endian/big endian swap code
            // would fail (I think) if the other cases are ever exercised.
            ASSERT((tmp & 0x3) == 0);

            if (!ReadMem(tmp, 4, &value))
                return;
            if (registers[LOAD_REG] == instr->rt)
                nextLoadValue = registers[LOAD_VALUE_REG];
            else
                nextLoadValue = registers[instr->rt];
            switch (tmp & 0x3) {
                case 0:
                    nextLoadValue = (nextLoadValue & 0xFFFFFF00)
                                    | (value >> 24 & 0xFF);
                    break;
                case 1:
                    nextLoadValue = (nextLoadValue & 0xFFFF0000)
                                    | (value >> 16 & 0xFFFF);
                    break;
                case 2:
                    nextLoadValue = (nextLoadValue & 0xFF000000)
                                    | (value >> 8 & 0xFFFFFF);
                    break;
                case 3:
                    nextLoadValue = value;
                    break;
            }
            nextLoadReg = instr->rt;
            break;

        case OP_MFHI:
            registers[instr->rd] = registers[HI_REG];
            break;

        case OP_MFLO:
            registers[instr->rd] = registers[LO_REG];
            break;

        case OP_MTHI:
            registers[HI_REG] = registers[instr->rs];
            break;

        case OP_MTLO:
            registers[LO_REG] = registers[instr->rs];
            break;

        case OP_MULT:
            Mult(registers[instr->rs], registers[instr->rt],
                 true, &registers[HI_REG], &registers[LO_REG]);
            break;

        case OP_MULTU:
            Mult(registers[instr->rs], registers[instr->rt],
                 false, &registers[HI_REG], &registers[LO_REG]);
            break;

        case OP_NOR:
            registers[instr->rd] = ~(registers[instr->rs]
                                     | registers[instr->rt]);
            break;

        case OP_OR:
            registers[instr->rd] = registers[instr->rs]
                                   | registers[instr->rt];
            break;

        case OP_ORI:
            registers[instr->rt] = registers[instr->rs]
                                   | (instr->extra & 0xFFFF);
            break;

        case OP_SB:
            if (!WriteMem((unsigned) (registers[instr->rs] + instr->extra),
                          1, registers[instr->rt]))
                return;
            break;

        case OP_SH:
            if (!WriteMem((unsigned) (registers[instr->rs] + instr->extra),
                          2, registers[instr->rt]))
                return;
            break;

        case OP_SLL:
            registers[instr->rd] = registers[instr->rt] << instr->extra;
            break;

        case OP_SLLV:
            registers[instr->rd] = registers[instr->rt]
                                   << (registers[instr->rs] & 0x1F);
            break;

        case OP_SLT:
            if (registers[instr->rs] < registers[instr->rt])
                registers[instr->rd] = 1;
            else
                registers[instr->rd] = 0;
            break;

        case OP_SLTI:
            if (registers[instr->rs] < instr->extra)
                registers[instr->rt] = 1;
            else
                registers[instr->rt] = 0;
            break;

        case OP_SLTIU:
            rs = registers[instr->rs];
            imm = instr->extra;
            if (rs < imm)
                registers[instr->rt] = 1;
            else
                registers[instr->rt] = 0;
            break;

        case OP_SLTU:
            rs = registers[instr->rs];
            rt = registers[instr->rt];
            if (rs < rt)
                registers[instr->rd] = 1;
            else
                registers[instr->rd] = 0;
            break;

        case OP_SRA:
            registers[instr->rd] = registers[instr->rt] >> instr->extra;
            break;

        case OP_SRAV:
            registers[instr->rd] = registers[instr->rt]
                                   >> (registers[instr->rs] & 0x1F);
            break;

        case OP_SRL:
            tmp = registers[instr->rt];
            tmp >>= instr->extra;
            registers[instr->rd] = tmp;
            break;

        case OP_SRLV:
            tmp = registers[instr->rt];
            tmp >>= registers[instr->rs] & 0x1F;
            registers[instr->rd] = tmp;
            break;

        case OP_SUB:
            diff = registers[instr->rs] - registers[instr->rt];
            if ((registers[instr->rs] ^ registers[instr->rt]) & SIGN_BIT
                  && (registers[instr->rs] ^ diff) & SIGN_BIT) {
                RaiseException(OVERFLOW_EXCEPTION, 0);
                return;
            }
            registers[instr->rd] = diff;
            break;

        case OP_SUBU:
            registers[instr->rd] = registers[instr->rs]
                                   - registers[instr->rt];
            break;

        case OP_SW:
            if (!WriteMem((unsigned) (registers[instr->rs] + instr->extra),
                          4, registers[instr->rt]))
                return;
            break;

        case OP_SWL:
            tmp = registers[instr->rs] + instr->extra;

            // The little endian/big endian swap code would fail (I think) if
            // the other cases are ever exercised.
            ASSERT((tmp & 0x3) == 0);

            if (!ReadMem(tmp & ~0x3, 4, &value))
                return;
            switch (tmp & 0x3) {
                case 0:
                    value = registers[instr->rt];
                    break;
                case 1:
                    value = (value & 0xFF000000)
                            | (registers[instr->rt] >> 8 & 0xFFFFFF);
                    break;
                case 2:
                    value = (value & 0xFFFF0000)
                            | (registers[instr->rt] >> 16 & 0xFFFF);
                    break;
                case 3:
                    value = (value & 0xFFFFFF00)
                            | (registers[instr->rt] >> 24 & 0xFF);
                    break;
            }
            if (!WriteMem(tmp & ~0x3, 4, value))
                return;
            break;

        case OP_SWR:
            tmp = registers[instr->rs] + instr->extra;

            // The little endian/big endian swap code would fail (I think) if
            // the other cases are ever exercised.
            ASSERT((tmp & 0x3) == 0);

            if (!ReadMem(tmp & ~0x3, 4, &value))
                return;
            switch (tmp & 0x3) {
                case 0:
                    value = (value & 0xFFFFFF)
                            | registers[instr->rt] << 24;
                    break;
                case 1:
                    value = (value & 0xFFFF)
                            | registers[instr->rt] << 16;
                    break;
                case 2:
                    value = (value & 0xFF) | registers[instr->rt] << 8;
                    break;
                case 3:
                    value = registers[instr->rt];
                    break;
            }
            if (!WriteMem(tmp & ~0x3, 4, value))
                return;
            break;

        case OP_SYSCALL:
            RaiseException(SYSCALL_EXCEPTION, 0);
            return;

        case OP_XOR:
            registers[instr->rd] = registers[instr->rs]
                                   ^ registers[instr->rt];
            break;

        case OP_XORI:
            registers[instr->rt] = registers[instr->rs]
                                   ^ (instr->extra & 0xFFFF);
            break;

        case OP_RES:
        case OP_UNIMP:
            RaiseException(ILLEGAL_INSTR_EXCEPTION, 0);
            return;

        default:
            ASSERT(false);
    }

    // Now we have successfully executed the instruction.

    // Do any delayed load operation.
    DelayedLoad(nextLoadReg, nextLoadValue);

    // Advance program counters.
    registers[PREV_PC_REG] = registers[PC_REG];
      // For debugging, in case we are jumping into lala-land.
    registers[PC_REG] = registers[NEXT_PC_REG];
    registers[NEXT_PC_REG] = pcAfter;
}
