/// Copyright (c) 2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_USERPROG_DEBUGGER_COMMAND_MANAGER__HH
#define NACHOS_USERPROG_DEBUGGER_COMMAND_MANAGER__HH


class DebuggerCommandManager {
public:
    enum RunResult {
        RUN_RESULT_STAY,
          ///< Stay in the debugger, do not advance execution of the user
          ///< process.
        RUN_RESULT_STEP,
          ///< Advance execution while keeping the debugger working.
        RUN_RESULT_NORMALIZE,
          ///< Proceed with normal execution, end the debugger.
    };

    typedef RunResult (*CommandFunc)(char **args, void *extra);
    typedef RunResult (*EmptyFunc)();
    typedef RunResult (*UnknownFunc)(const char *name);

    /// Fetch the next argument for a command invocation.
    static const char *FetchArg(char **args);

    bool AddCommand(const char *name, CommandFunc f, void *extra);
    void SetEmpty(EmptyFunc f);
    void SetUnknown(UnknownFunc f);
    RunResult Run(char *line);

private:
    static const unsigned CAPACITY = 20;

    struct Command {
        const char *name;
        CommandFunc func;
        void *extra;
    };

    Command commands[CAPACITY];
    unsigned count;  ///< How many commands are added?

    EmptyFunc empty;
    UnknownFunc unknown;
};


#endif
