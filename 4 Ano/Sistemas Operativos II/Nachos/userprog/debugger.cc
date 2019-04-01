/// Copyright (c) 2016-2017 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "debugger.hh"
#include "lib/utility.hh"
#include "machine/interrupt.hh"
#include "machine/statistics.hh"
#include "threads/system.hh"

#include <ctype.h>
#include <string.h>


typedef DebuggerCommandManager DCM;

static inline void
PrintPrompt()
{
    const char PROMPT[] = "%u> ";

    printf(PROMPT, stats->totalTicks);
    fflush(stdout);
}

static inline char *
GetLine(char *buffer, unsigned size)
{
    ASSERT(buffer != nullptr);

    if (fgets(buffer, size, stdin) == nullptr)
        return nullptr;

    // Remove trailing spaces.
    char *p;
    for (p = buffer + strlen(buffer) - 1; isspace(*p); p--);
    *(p + 1) = '\0';

    // Remove leading spaces.
    for (p = buffer; isspace(*p); p++);
    return p;
}

static inline const char *
GetGPRegisterName(unsigned i)
{
    static const char *NAMES[] = {
        "ZE", "AT", "V0", "V1", "A0", "A1", "A2", "A3",
        "T0", "T1", "T2", "T3", "T4", "T5", "T6", "T7",
        "S0", "S1", "S2", "S3", "S4", "S5", "S6", "S7",
        "T8", "T9", "K0", "K1", "GP", "SP", "FP", "RA"
    };

    if (i < sizeof NAMES / sizeof *NAMES)
        return NAMES[i];
    else
        return nullptr;
}

static inline void
PrintGPRegister(const int *registers, unsigned i)
{
    ASSERT(registers != nullptr);

    const char *name = GetGPRegisterName(i);
    if (name != nullptr)
        printf("%s(%u):\t0x%X", name, i, registers[i]);
    else
        printf("%u:\t0x%X", i, registers[i]);
}

/// Print the user program's CPU state.  We might print the contents of
/// memory, but that seemed like overkill.
static inline void
DumpMachineState(int *previousRegisters)
{
    ASSERT(previousRegisters != nullptr);

    const char COLOR_CHANGED_BEGINNING[] = "\033[34m";
    const char COLOR_CHANGED_END[]       = "\033[0m";

    const int *registers = machine->GetRegisters();

    printf("Machine registers:\n");
    for (unsigned i = 0; i < NUM_GP_REGS; i++) {
        if (registers[i] != previousRegisters[i])
            printf(COLOR_CHANGED_BEGINNING);

        printf("\t");
        PrintGPRegister(registers, i);
        if (i % 4 == 3)
            printf("\n");

        if (registers[i] != previousRegisters[i])
            printf(COLOR_CHANGED_END);
    }

    printf("\tHi:\t0x%X",       registers[HI_REG]);
    printf("\tLo:\t0x%X\n",     registers[LO_REG]);
    printf("\tPC:\t0x%X",       registers[PC_REG]);
    printf("\tNextPC:\t0x%X",   registers[NEXT_PC_REG]);
    printf("\tPrevPC:\t0x%X\n", registers[PREV_PC_REG]);
    printf("\tLoad:\t0x%X",     registers[LOAD_REG]);
    printf("\tLoadV:\t0x%X\n",  registers[LOAD_VALUE_REG]);
    printf("\n");

    memcpy(previousRegisters, registers, NUM_TOTAL_REGS * sizeof (int));
}

static DCM::RunResult
CommandContinue(char **args, void *extra)
{
    return DCM::RUN_RESULT_NORMALIZE;
}

static DCM::RunResult
CommandDump(char **args, void *extra)
{
    const char *path = DCM::FetchArg(args);
    if (path == nullptr) {
        fprintf(stderr, "ERROR: missing argument.\n");
        return DCM::RUN_RESULT_STAY;
    }

    FILE *f = fopen(path, "w");
    if (f == nullptr) {
        fprintf(stderr, "ERROR: file `%s` could not be opened.\n", path);
        return DCM::RUN_RESULT_STAY;
    }

    int rv = fwrite(machine->GetMMU()->mainMemory, 1, MEMORY_SIZE, f);
    if (rv != MEMORY_SIZE) {
        fprintf(stderr, "ERROR: write to file `%s` did not succeed.\n",
                path);
        return DCM::RUN_RESULT_STAY;
    }

    fclose(f);
    printf("Main memory dumped into file `%s`.\n", path);
    return DCM::RUN_RESULT_STAY;
}

static DCM::RunResult
CommandFlags(char **args, void *extra)
{
    const char *flags = debug.GetFlags();
    if (flags[0] == '\0')
        printf("Debug flags empty.\n");
    else
        printf("Debug flags: %s\n", flags);
    return DCM::RUN_RESULT_STAY;
}

static DCM::RunResult
CommandHelp(char **args, void *extra)
{
    printf("\
Debugger commands:\n\
    continue, c             Run until completion.\n\
    dump <path>             Dump the simulated machine's main memory into\n\
                            a file.\n\
    flags, f                Show current flags for debug output.\n\
    help, h, ?              Show this help message.\n\
    print, p <address>...   Print bytes from memory.  The addresses are\n\
                            taken as virtual by default; one can specify\n\
                            whether each of them is physical or virtual\n\
                            with the suffixes `@p` and `@v` respectively.\n\
                            Addresses can be represented in decimal,\n\
                            hexadecimal (using the prefix `0x`) and octal\n\
                            (with the prefix `0`).\n\
    step, s, <return>       Execute one instruction.\n\
    setflags, setf <flags>  Set flags for debug output.\n\
    tick, t <number>        Run for a number of timer ticks.\n\
    quit, q                 Exit.\n\n");
    return DCM::RUN_RESULT_STAY;
}

static void
PrintChar(char c)
{
    if (isprint(c))
        printf("%hhu ('%c')\n", c, c);
    else
        printf("%hhu\n", c);
}

/// Exceptions on memory reads performed by this function are not handled by
/// Nachos (as in normal execution).  However, the use bit in the
/// corresponding translation entry does get enabled when reading a virtual
/// address.
static DCM::RunResult
CommandPrint(char **args, void *extra)
{
    const char *arg;
    while ((arg = DCM::FetchArg(args)) != nullptr) {
        char *end;
        unsigned address = strtoul(arg, &end, 0);

        if (strcmp(end, "@v") == 0 || *end == '\0') {
            int c;
            ExceptionType e = machine->GetMMU()->ReadMem(address, 1, &c);
            if (e == NO_EXCEPTION)
                PrintChar(c);
            else
                printf("Exception on memory read: %u\n", e);

        } else if (strcmp(end, "@p") == 0) {
            if (address >= MEMORY_SIZE) {
                fprintf(stderr, "ERROR: address %u is too big.\n", address);
                return DCM::RUN_RESULT_STAY;
            }

            PrintChar(machine->GetMMU()->mainMemory[address]);

        } else {
            fprintf(stderr,
                    "ERROR: argument `%s` is not an address.\n", arg);
            return DCM::RUN_RESULT_STAY;
        }
    }

    return DCM::RUN_RESULT_STAY;
}

static DCM::RunResult
CommandQuit(char **args, void *extra)
{
    interrupt->Halt();
    return DCM::RUN_RESULT_NORMALIZE;
}

static DCM::RunResult
CommandSetFlags(char **args, void *extra)
{
    const char *flags = DCM::FetchArg(args);
    if (flags == nullptr) {
        fprintf(stderr, "ERROR: missing argument.\n");
        return DCM::RUN_RESULT_STAY;
    }

    debug.SetFlags(flags);
    if (flags[0] == '\0')
        printf("Debug flags set to empty.\n");
    else
        printf("Debug flags set to: %s\n", flags);
    return DCM::RUN_RESULT_STAY;
}

static DCM::RunResult
CommandStep(char **args, void *extra)
{
    return DCM::RUN_RESULT_STEP;
}

static DCM::RunResult
CommandTick(char **args, void *runUntilTime_)
{
    ASSERT(runUntilTime_ != nullptr);

    const char *num_s = DCM::FetchArg(args);
    if (num_s == nullptr) {
        fprintf(stderr, "ERROR: missing argument.\n");
        return DCM::RUN_RESULT_STAY;
    }

    char *end;
    unsigned num = strtoul(num_s, &end, 10);
    if (*end != '\0') {
        fprintf(stderr,
                "ERROR: argument `%s` is not an integer number.\n", num_s);
        return DCM::RUN_RESULT_STAY;
    }

    unsigned *runUntilTime = (unsigned *) runUntilTime_;
    *runUntilTime = stats->totalTicks + num;
    return DCM::RUN_RESULT_STEP;
}

static DCM::RunResult
HandleEmpty()
{
    return DCM::RUN_RESULT_STEP;
}

static DCM::RunResult
HandleUnknown(const char *name)
{
    fprintf(stderr, "ERROR: `%s` is not a valid command.\n", name);
    return CommandHelp(nullptr, nullptr);
}

Debugger::Debugger()
{
    runUntilTime = 0;
    memset(previousRegisters, 0, sizeof previousRegisters);
    manager.AddCommand("continue", &CommandContinue, nullptr);
    manager.AddCommand("c",        &CommandContinue, nullptr);
    manager.AddCommand("dump",     &CommandDump,     nullptr);
    manager.AddCommand("flags",    &CommandFlags,    nullptr);
    manager.AddCommand("f",        &CommandFlags,    nullptr);
    manager.AddCommand("help",     &CommandHelp,     nullptr);
    manager.AddCommand("h",        &CommandHelp,     nullptr);
    manager.AddCommand("?",        &CommandHelp,     nullptr);
    manager.AddCommand("print",    &CommandPrint,    nullptr);
    manager.AddCommand("p",        &CommandPrint,    nullptr);
    manager.AddCommand("quit",     &CommandQuit,     nullptr);
    manager.AddCommand("q",        &CommandQuit,     nullptr);
    manager.AddCommand("setflags", &CommandSetFlags, nullptr);
    manager.AddCommand("setf",     &CommandSetFlags, nullptr);
    manager.AddCommand("step",     &CommandStep,     nullptr);
    manager.AddCommand("s",        &CommandStep,     nullptr);
    manager.AddCommand("tick",     &CommandTick,     &runUntilTime);
    manager.AddCommand("t",        &CommandTick,     &runUntilTime);
    manager.SetEmpty(&HandleEmpty);
    manager.SetUnknown(&HandleUnknown);

    printf("Welcome to Nachos' debugger.  If you need help, type `help`.\n\n");
}

/// This destructor is not really needed.  However, since this class is a
/// derived one, there would be a possibility of undefined behavior if only
/// the superclass destructor were called.  This empty definition of a
/// virtual destructor avoids a compiler warning.
Debugger::~Debugger()
{}

/// Primitive debugger for user programs.  Note that we cannot use GDB to
/// debug user programs, since GDB does not run on top of Nachos.  It could,
/// but you would have to implement *a lot* more system calls to get it to
/// work!
///
/// So just allow single-stepping, and printing the contents of memory.
bool
Debugger::Step()
{
    // Wait until the indicated number of ticks has been reached.
    if (runUntilTime > stats->totalTicks)
        return true;

    runUntilTime = 0;

    interrupt->DumpState();
    DumpMachineState(previousRegisters);

    for (;;) {
        PrintPrompt();

        // Get an input line, and exit if EOF.
        char *l = GetLine(buffer, BUFFER_SIZE);
        if (l == nullptr)
            return CommandQuit(nullptr, nullptr);

        switch (manager.Run(l)) {
            case DCM::RUN_RESULT_STAY:
                continue;
            case DCM::RUN_RESULT_STEP:
                return true;
            case DCM::RUN_RESULT_NORMALIZE:
                return false;
            default:
                ASSERT(false);
        }
    }
}
