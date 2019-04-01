/// Copyright (c) 2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "debugger_command_manager.hh"
#include "lib/utility.hh"

#include <string.h>


typedef DebuggerCommandManager DCM;

static const char SEPARATOR[] = " ";

const char *
DCM::FetchArg(char **args)
{
    return strtok_r(nullptr, SEPARATOR, args);
}

bool
DCM::AddCommand(const char *name, CommandFunc f, void *extra)
{
    ASSERT(name != nullptr);
    ASSERT(f != nullptr);

    if (count >= CAPACITY)
        return false;

    Command c = { name, f, extra };
    commands[count++] = c;
    return true;
}

void
DCM::SetEmpty(EmptyFunc f)
{
    empty = f;
}

void
DCM::SetUnknown(UnknownFunc f)
{
    unknown = f;
}

DCM::RunResult
DCM::Run(char *line)
{
    // Extract the command name from the line.
    char *saved;
    const char *name = strtok_r(line, SEPARATOR, &saved);

    // If the line is empty...
    if (name == nullptr) {
        ASSERT(empty != nullptr);
        return (*empty)();
    }

    for (unsigned i = 0; i < count; i++) {
        Command c = commands[i];
        if (strcmp(c.name, name) == 0)
            return (*c.func)(&saved, c.extra);
    }

    // If this is reached, then the command is unknown...
    ASSERT(unknown != nullptr);
    return (*unknown)(name);
}
