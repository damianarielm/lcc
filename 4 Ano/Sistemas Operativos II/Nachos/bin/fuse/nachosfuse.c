/// A FUSE client the Nachos file system.
///
/// FUSE (Filesystem in Userspace) is a mechanism for integrating custom
/// file systems from userspace in POSIX operating systems.  This program
/// allows the user to mount Nachos' file system in a directory and then
/// access it using all the standard tools (e.g. commands like `ls` and
/// `cat`, or graphical file managers).
///
/// For now, only read capabilities are implemented in the FUSE client.
/// This means that it is yet not possible to create a new file or modify
/// an existing one through the standard tools.
///
/// Another limitation is that the `DISK` file, which contains the whole
/// simulated disk content, must be available in the same directory where
/// the FUSE client is executed.  It is recommended to set up a symbolic
/// link to the original in the `filesys` directory.  If you launch the
/// client with `make mount`, the link gets created automatically.
///
/// Copyright (c) 2018 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#define FUSE_USE_VERSION 26
#include <fuse.h>
#include <unistd.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef NACHOS
#error "The `NACHOS` macro is not defined.  Compile with `make`."
#endif
#define NACHOS_LS             NACHOS " -ls"
#define NACHOS_PR             NACHOS " -pr"
#define MAX_PATH_LENGTH       1024
#define MAX_NACHOS_PR_LENGTH  (sizeof NACHOS_PR + MAX_PATH_LENGTH + 2)

static int
do_getattr(const char *path, struct stat *st)
{
    fprintf(stderr, "[getattr] %s\n", path);

    time_t t = time(NULL);

    st->st_uid = getuid();
    st->st_gid = getgid();
    st->st_atime = t;
    st->st_mtime = t;
    if (strcmp(path, "/") == 0) {
        st->st_mode = S_IFDIR | 0755;
        st->st_nlink = 2;
    } else {
        st->st_mode = S_IFREG | 0644;
        st->st_nlink = 1;
        st->st_size = 1024;
    }

    return 0;
}

static int
do_readdir(const char *path, void *buffer, fuse_fill_dir_t fill,
           off_t offset, struct fuse_file_info *fi)
{
    fprintf(stderr, "[readdir] %s\n", path);

    (*fill)(buffer, ".", NULL, 0);
    (*fill)(buffer, "..", NULL, 0);

    if (strcmp(path, "/") != 0)
        return 0;

    // Invoke Nachos.
    FILE *f = popen(NACHOS_LS, "r");
    if (f == NULL) {
        perror(NACHOS);
        exit(1);
    }

    // Read lines.  Each line represents an entry in the directory, until an
    // empty line is found.
    char *line = NULL;
    size_t n, capacity = 0;
    while (n = getline(&line, &capacity, f)) {
        if (n == 1 && line[0] == '\n')
            // Stop when the first empty line is found.  The directory
            // listing ends here.  Only messages from the simulated machine
            // follow.
            break;
        line[n - 1] = '\0';  // Replace the delimiter (newline) by a null
                             // character.
        fprintf(stderr, "    %s\n", line);
        (*fill)(buffer, line, NULL, 0);
    }

    fclose(f);
    if (line != NULL)
        free(line);
    return 0;
}

static int
do_read(const char *path, char *buffer, size_t size, off_t offset,
        struct fuse_file_info *fi)
{
    fprintf(stderr, "[read] %s\n"
                    "    size: %zu, start: %zu\n",
            path, size, offset);

    // Prepare command string for invoking Nachos.
    char command[MAX_NACHOS_PR_LENGTH];
    int rv = snprintf(command, MAX_NACHOS_PR_LENGTH,
                      "%s %s", NACHOS_PR, path + 1);
      // Discard leading slash in path, because Nachos does not like it.
    if (rv < 0 || rv >= MAX_NACHOS_PR_LENGTH) {
        perror(path);
        return -1;
    }

    // Invoke Nachos.
    FILE *f = popen(command, "r");
    if (f == NULL) {
        perror(NACHOS);
        exit(1);
    }

    // Read lines.
    char *line = NULL;
    size_t i, n, capacity = 0;
    for (i = 0; n = getline(&line, &capacity, f); i += n) {
        if (n == 1 && line[0] == '\n')
            // Stop when the first empty line is found.  The directory
            // listing ends here.  Only messages from the simulated machine
            // follow.
            break;
        memcpy(buffer + i, line, n);
        if (n > size)
            break;
    }

    fclose(f);
    if (line != NULL)
        free(line);
    return i;
}

static const struct fuse_operations OPERATIONS = {
    .getattr = do_getattr,
    .readdir = do_readdir,
    .read    = do_read,
};

int
main(int argc, char *argv[])
{
    return fuse_main(argc, argv, &OPERATIONS, NULL);
}
