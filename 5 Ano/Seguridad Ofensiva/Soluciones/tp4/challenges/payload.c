// To compile:
// gcc payload.c -c -fPIC -m32 -o payload.o
// gcc payload.o -shared -m32 -o payload.so

// To run:
// LD_PRELOAD=./payload.so ./01-challenge

#include <stdio.h>
#include <stdlib.h>

extern int fscanf(FILE* stream, const char* format, ...) {
    printf("YOU WIN!\n");
    exit(0);
}

ssize_t read(int fd, void *buf, size_t count) {
    printf("YOU WIN!\n");
    exit(0);
}

char* gets(char* s) {
    printf("YOU WIN!\n");
    exit(0);
}
