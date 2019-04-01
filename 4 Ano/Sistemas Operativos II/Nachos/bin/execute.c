/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "instr.h"
#include "encode.h"
#include "int.h"

#include <stdio.h>
#include <string.h>


extern char mem[];
extern int TRACE, Regtrace;

// Machine registers
static int Reg[32];  // General purpose registers.
static int HI, LO;   // mul/div machine registers.

// Condition-code calculations

// Extract bit 31.
static inline int
B31(int z)
{
    return z >> 31 & 0x1;
}

// Code looks funny but is fast thanks to MIPS!
static inline void
CcAdd(int rr, int op1, int op2)
{
    N = rr < 0;
    Z = rr == 0;
    C = (unsigned) rr < (unsigned) op2;
    V = op1 ^ op2 >= 0 && op1 ^ rr < 0;
}

static inline void
CcSub(int rr, int op1, int op2)
{
    N = rr < 0;
    Z = rr == 0;
    V = B31((op1 & ~op2 & ~rr) | (~op1 & op2 & rr));
    C = (unsigned) op1 < (unsigned) op2;
    //C = B31((~op1 & op2) | (rr & (~op1 | op2)));
}

static inline void
CcLogic(int rr)
{
    N = rr < 0;
    Z = rr == 0;
    V = 0;
    C = 0;
}

static inline void
CcMulscc(int rr, int op1, int op2)
{
    N = rr < 0;
    Z = rr == 0;
    V = B31((op1 & op2 & ~rr) | (~op1 & ~op2 & rr));
    C = B31((op1 & op2) | (~rr & (op1 | op2)));
}


// Debug aid.
void
DumpReg(void)
{
    int j;

    printf(" 0:");
    for (j = 0; j < 8; j++)
        printf(" %08x", Reg[j]);
    printf("\n");
    printf(" 8:");
    for (; j < 16; j++)
        printf(" %08x", Reg[j]);
    printf("\n");
    printf("16:");
    for (; j < 24; j++)
        printf(" %08x", Reg[j]);
    printf("\n");
    printf("24:");
    for (; j < 32; j++)
        printf(" %08x", Reg[j]);
    printf("\n");
}


/// Unimplemented.
static void
Unimplemented(void)
{
    printf("Unimplemented instruction.\n");
    exit(2);
}

void
RunProgram(unsigned startpc, int argc, char *argv[])
{
    int aci, ai;
    int instr, pc, xpc, npc;
    int i;  // Temporary for local stuff.
    int icount;

    // `i`, `aci` and `ai` are virtual addresses.
    //
    // * i: top of the stack
    // * aci: pointer inside the `argv` array
    // * ai: proper string of a command-line argument
    //
    // There are 1020 bytes available for the whole `argv` and the strings
    // it points to.  There bytes are right above the stack and are the top
    // of the available memory.
    //
    // `ai` starts at `aci + 32`, so `aci` must not surpass that.  In other
    // words, there can be at most 8 command-line arguments.  32 bytes are
    // reserved for `argv` and the rest (988) for the strings.
    //
    // `argc` is stored at the top of the stack, ie. at `i`.
    //
    // Assuming command-line arguments `"a0"` through `"a7"`, the layout is
    // as follows:
    //
    //     |v^v^v^v^v| <- i + 1024
    //     | garbage |
    //     |---------|
    //     | "a7\0"  |
    //     |---------| <- i + 58, ai7
    //     |   ...   |
    //     |---------|
    //     | "a1\0"  |
    //     |---------| <- i + 39, ai1
    //     | "a0\0"  |
    //     |---------| <- i + 36, ai0, aci0 + 32
    //     | argv[7] |
    //     |---------| <- i + 32, aci7, aci0 + 28
    //     |   ...   |
    //     |---------|
    //     | argv[1] |
    //     |---------| <- i + 8, aci1, aci0 + 4
    //     | argv[0] |
    //     |---------| <- i + 4, aci0
    //     |  argc   |
    //     |---------| <- i
    //     |         |

    icount = 0;
    pc = startpc; npc = pc + 4;
    i = MEMSIZE - 1024 + memoffset;  // Initial SP value.
    Reg[29] = i;                     // Initialize SP.
    // Setup argc and argv stuff (icky!)
    Store(i, argc);
    aci = i + 4;
    ai  = aci + 32;
    for (unsigned j = 0; j < argc; ++j) {
        strncpy((mem - memoffset) + ai, argv[j],
                MEMSIZE + memoffset - ai);
        Store(aci, ai);
        aci += 4;
        ai += strlen(argv[j]) + 1;
    }

    for (;;) {
        icount++;
        xpc = pc;
        pc = npc;
        npc = pc + 4;
        instr = IFetch(xpc);
        Reg[0] = 0;  // Force r0 = 0.

        if (instr != 0)  // Eliminate no-ops.
        {
            switch (instr >> 26 & 0x0000003F)
            {
                case I_SPECIAL:
                {
                    switch (instr & 0x0000003F)
                    {

                        case I_SLL:
                            Reg[rd(instr)] = Reg[rt(instr)] << shamt(instr);
                            break;
                        case I_SRL:
                            Reg[rd(instr)] = (unsigned) Reg[rt(instr)]
                                             >> shamt(instr);
                            break;
                        case I_SRA:
                            Reg[rd(instr)] = Reg[rt(instr)] >> shamt(instr);
                            break;
                        case I_SLLV:
                            Reg[rd(instr)] = Reg[rt(instr)]
                                             << Reg[rs(instr)];
                            break;
                        case I_SRLV:
                            Reg[rd(instr)] =
                            (unsigned) Reg[rt(instr)] >> Reg[rs(instr)];
                            break;
                        case I_SRAV:
                            Reg[rd(instr)] = Reg[rt(instr)]
                                             >> Reg[rs(instr)];
                            break;
                        case I_JR:
                            npc = Reg[rs(instr)];
                            break;
                        case I_JALR:
                            npc = Reg[rs(instr)];
                            Reg[rd(instr)] = xpc + 8;
                            break;

                        case I_SYSCALL:
                            SystemTrap();
                            break;
                        case I_BREAK:
                            SystemBreak();
                            break;

                        case I_MFHI:
                            Reg[rd(instr)] = HI;
                            break;
                        case I_MTHI:
                            HI = Reg[rs(instr)];
                            break;
                        case I_MFLO:
                            Reg[rd(instr)] = LO;
                            break;
                        case I_MTLO:
                            LO = Reg[rs(instr)];
                            break;

                        case I_MULT: {
                            int t1, t2;
                            int t1l, t1h, t2l, t2h;
                            int neg;

                            t1 = Reg[rs(instr)];
                            t2 = Reg[rt(instr)];
                            neg = 0;
                            if (t1 < 0) {
                                t1 = -t1;
                                neg = !neg;
                            }
                            if (t2 < 0) {
                                t2 = -t2;
                                neg = !neg;
                            }
                            LO = t1 * t2;
                            t1l = t1 & 0xFFFF;
                            t1h = (t1 >> 16) & 0xFFFF;
                            t2l = t2 & 0xFFFF;
                            t2h = (t2 >> 16) & 0xFFFF;
                            HI = t1h * t2h
                                 + (t1h * t2l >> 16) + (t2h * t1l >> 16);
                            if (neg) {
                                LO = ~LO;
                                HI = ~HI;
                                LO = LO + 1;
                                if (LO == 0)
                                    HI = HI + 1;
                            }
                            break;
                        }
                        case I_MULTU: {
                            int t1, t2;
                            int t1l, t1h, t2l, t2h;

                            t1 = Reg[rs(instr)];
                            t2 = Reg[rt(instr)];
                            t1l = t1 & 0xFFFF;
                            t1h = t1 >> 16 & 0xFFFF;
                            t2l = t2 & 0xFFFF;
                            t2h = t2 >> 16 & 0xFFFF;
                            LO = t1 * t2;
                            HI = t1h * t2h
                                 + (t1h * t2l >> 16) + (t2h * t1l >> 16);
                            break;
                        }
                        case I_DIV:
                            LO = Reg[rs(instr)] / Reg[rt(instr)];
                            HI = Reg[rs(instr)] % Reg[rt(instr)];
                            break;
                        case I_DIVU:
                            LO = (unsigned) Reg[rs(instr)]
                                 / (unsigned) Reg[rt(instr)];
                            HI = (unsigned) Reg[rs(instr)]
                                 % (unsigned) Reg[rt(instr)];
                            break;

                        case I_ADD:
                        case I_ADDU:
                            Reg[rd(instr)] = Reg[rs(instr)] + Reg[rt(instr)];
                            break;
                        case I_SUB:
                        case I_SUBU:
                            Reg[rd(instr)] = Reg[rs(instr)] - Reg[rt(instr)];
                            break;
                        case I_AND:
                            Reg[rd(instr)] = Reg[rs(instr)] & Reg[rt(instr)];
                            break;
                        case I_OR:
                            Reg[rd(instr)] = Reg[rs(instr)] | Reg[rt(instr)];
                            break;
                        case I_XOR:
                            Reg[rd(instr)] = Reg[rs(instr)] ^ Reg[rt(instr)];
                            break;
                        case I_NOR:
                            Reg[rd(instr)] = ~(Reg[rs(instr)]
                                               | Reg[rt(instr)]);
                            break;

                        case I_SLT:
                            Reg[rd(instr)] = Reg[rs(instr)] < Reg[rt(instr)];
                            break;
                        case I_SLTU:
                            Reg[rd(instr)] = (unsigned) Reg[rs(instr)]
                                             < (unsigned) Reg[rt(instr)];
                            break;
                        default:
                            Unimplemented();
                            break;
                    }
                } break;

                case I_BCOND:
                {
                    switch (rt(instr))  // This field encodes the op.
                    {
                        case I_BLTZ:
                            if (Reg[rs(instr)] < 0)
                                npc = xpc + 4 + (immed(instr) << 2);
                            break;
                        case I_BGEZ:
                            if (Reg[rs(instr)] >= 0)
                                npc = xpc + 4 + (immed(instr) << 2);
                            break;

                        case I_BLTZAL:
                            Reg[31] = xpc + 8;
                            if (Reg[rs(instr)] < 0)
                                npc = xpc + 4 + (immed(instr) << 2);
                            break;
                        case I_BGEZAL:
                            Reg[31] = xpc + 8;
                            if (Reg[rs(instr)] >= 0)
                                npc = xpc + 4 + (immed(instr) << 2);
                            break;
                        default:
                            Unimplemented();
                            break;
                    }

                } break;

                case I_J:
                    npc = (xpc & 0xF0000000) | (instr & 0x03FFFFFF) << 2;
                    break;
                case I_JAL:
                    Reg[31] = xpc + 8;
                    npc = (xpc & 0xF0000000) | (instr & 0x03FFFFFF) << 2;
                    break;
                case I_BEQ:
                    if (Reg[rs(instr)] == Reg[rt(instr)])
                        npc = xpc + 4 + (immed(instr) << 2);
                    break;
                case I_BNE:
                    if (Reg[rs(instr)] != Reg[rt(instr)])
                        npc = xpc + 4 + (immed(instr) << 2);
                    break;
                case I_BLEZ:
                    if (Reg[rs(instr)] <= 0)
                        npc = xpc + 4 + (immed(instr) << 2);
                    break;
                case I_BGTZ:
                    if (Reg[rs(instr)] > 0)
                        npc = xpc + 4 + (immed(instr) << 2);
                    break;
                case I_ADDI:
                    Reg[rt(instr)] = Reg[rs(instr)] + immed(instr);
                    break;
                case I_ADDIU:
                    Reg[rt(instr)] = Reg[rs(instr)] + immed(instr);
                    break;
                case I_SLTI:
                    Reg[rt(instr)] = Reg[rs(instr)] < immed(instr);
                    break;
                case I_SLTIU:
                    Reg[rt(instr)] = (unsigned) Reg[rs(instr)]
                                     < (unsigned) immed(instr);
                    break;
                case I_ANDI:
                    Reg[rt(instr)] = Reg[rs(instr)] & immed(instr);
                    break;
                case I_ORI:
                    Reg[rt(instr)] = Reg[rs(instr)] | immed(instr);
                    break;
                case I_XORI:
                    Reg[rt(instr)] = Reg[rs(instr)] ^ immed(instr);
                    break;
                case I_LUI:
                    Reg[rt(instr)] = instr << 16;
                    break;

                case I_LB:
                    Reg[rt(instr)] = CFetch(Reg[rs(instr)] + immed(instr));
                    break;
                case I_LH:
                    Reg[rt(instr)] = SFetch(Reg[rs(instr)] + immed(instr));
                    break;
                case I_LWL:
                    i = Reg[rs(instr)] + immed(instr);
                    Reg[rt(instr)] &= -1 >> 8 * (-i & 0x03);
                    Reg[rt(instr)] |= Fetch(i & 0xFFFFFFFC)
                                      << 8 * (i & 0x03);
                    break;
                case I_LW:
                    Reg[rt(instr)] = Fetch(Reg[rs(instr)] + immed(instr));
                    break;
                case I_LBU:
                    Reg[rt(instr)] = UCFetch(Reg[rs(instr)] + immed(instr));
                    break;
                case I_LHU:
                    Reg[rt(instr)] = USFetch(Reg[rs(instr)] + immed(instr));
                    break;
                case I_LWR:
                    i = Reg[rs(instr)] + immed(instr);
                    Reg[rt(instr)] &= -1 << 8 * (i & 0x03);
                    if ((i & 0x03) == 0)
                        Reg[rt(instr)] = 0;
                    Reg[rt(instr)] |=
                      Fetch(i & 0xFFFFFFFC) >> 8 * (-i & 0x03);
                    break;

                case I_SB:
                    CStore(Reg[rs(instr)] + immed(instr), Reg[rt(instr)]);
                    break;
                case I_SH:
                    SStore(Reg[rs(instr)] + immed(instr), Reg[rt(instr)]);
                    break;
                case I_SWL:
                    fprintf(stderr, "sorry, no SWL yet.\n");
                    Unimplemented();
                    break;
                case I_SW:
                    Store(Reg[rs(instr)] + immed(instr), Reg[rt(instr)]);
                    break;

                case I_SWR:
                    fprintf(stderr, "sorry, no SWR yet.\n");
                    Unimplemented();
                    break;

                case I_LWC0: case I_LWC1:
                case I_LWC2: case I_LWC3:
                case I_SWC0: case I_SWC1:
                case I_SWC2: case I_SWC3:
                case I_COP0: case I_COP1:
                case I_COP2: case I_COP3:
                    fprintf(stderr, "Sorry, no coprocessors.\n");
                    exit(2);
                    break;

                default:
                    Unimplemented();
                    break;
            }
        }

#ifdef DEBUG
        printf("%d(%X) = %d(%X) op %d(%X)\n",
               Reg[rd], Reg[rd], op1, op1, op2, op2);
#endif
        if (TRACE) {
            DumpAscii(instr, xpc);
            printf("\n");
            if (Regtrace)
                DumpReg();
        }
    }
}
