/// Move command-line arguments between user memory and kernel memory
///
/// These functions follow the standard style of passing arguments in
/// Unix-like operating systems and the C programming language.
///
/// Copyright (c) 2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.

#ifndef NACHOS_USERPROG_ARGS__HH
#define NACHOS_USERPROG_ARGS__HH


/// Save command-line arguments from the memory of a user process.
///
/// It moves an `argv`-like array from user memory to kernel memory, and
/// returns a pointer to the latter.
///
/// * `address` is a user-space address pointing to the start of an
///   `argv`-like array.
char **SaveArgs(int address);

/// Write command-line arguments into the stack memory of a user process.
///
/// Considering two example arguments `hello` and `Nachos`, the resulting
/// stack layout is as follows:
///
///            +┌───────────────────────┐
///     7 bytes │         hello\0       │<───────────────┐ 1st arg.
///             ├───────────────────────┤                │
///     6 bytes │        Nachos\0       │<───┐ 2nd arg.  │
///             ├───────────────────────┤    │           │
///     4 bytes │     (null pointer)    │    │           │
///             ├───────────────────────┤    │           │
///     4 bytes │ (pointer to 2nd arg.) │────┘           │
///             ├───────────────────────┤                │
///     4 bytes │ (pointer to 1st arg.) │────────────────┘
///            -└───────────────────────┘
///
/// * `args` is a kernel-space pointer to the start of an `argv`-like array.
void WriteArgs(char **args);


#endif
