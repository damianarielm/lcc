/// Copyright (c) 2016-2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "transfer.hh"
#include "machine/machine.h"


const unsigned MAX_ARG_COUNT  = 32;
const unsigned MAX_ARG_LENGTH = 128;

char **
SaveArgs(int address)
{
    ASSERT(address != 0);

    // Count the number of arguments up to a null.
    int val;
    unsigned i = 0;
    do {
        machine->ReadMem(address + i * 4, 4, &val);
        i++;
    } while (i < MAX_ARG_COUNT && val != 0);
    if (i == MAX_ARG_COUNT && val != 0)
        // The maximum number of arguments was reached but the last is not
        // null.  Return null as error.
        return nullptr;

    DEBUG('e', "Saving %u command line arguments from parent process.\n", i);

    char **ret = new char * [i];  // Allocate an array of `i` pointers. We
                                  // know that `i` will always be at least 1.
    for (unsigned j = 0; j < i - 1; j++) {
        // For each pointer, read the corresponding string.
        ret[j] = new char [MAX_ARG_LENGTH];
        machine->ReadMem(address + j * 4, 4, &val);
        ReadStringFromUser(val, ret[j], MAX_ARG_LENGTH);
    }
    ret[i - 1] = nullptr;  // Write the trailing null.

    return ret;
}

void
WriteArgs(char **args)
{
    ASSERT(args != nullptr);

    DEBUG('e', "Writing command line arguments into child process.\n");

    // Start writing the arguments where the current SP points.
    int args_address[MAX_ARG_COUNT];
    unsigned i;
    int sp = machine->ReadRegister(StackReg);
    for (i = 0; i < MAX_ARG_COUNT; i++) {
        if (args[i] == nullptr)     // If the last was reached, terminate.
            break;
        sp -= strlen(args[i]) + 1;  // Decrease SP (leave one byte for \0).
        WriteStringToUser(args[i], sp);  // Write the string there.
        args_address[i] = sp;       // Save the argument's address.
        delete args[i];             // Free the memory.
    }
    ASSERT(i < MAX_ARG_COUNT);

    sp -= sp % 4;     // Align the stack to a multiple of four.
    sp -= i * 4 + 4;  // Make room for the array and the trailing null.
    for (unsigned j = 0; j < i; j++)
        // Save the address of the j-th argument counting from the end down
        // to the beginning.
        machine->WriteMem(sp + 4 * j, 4, args_address[j]);
    machine->WriteMem(sp + 4 * i, 4, 0);  // The last is null.
    sp -= 16;  // Make room for the “register saves”.

    machine->WriteRegister(StackReg, sp);
    delete args;  // Free the array.
}
