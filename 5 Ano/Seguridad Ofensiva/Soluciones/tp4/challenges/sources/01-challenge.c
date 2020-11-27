#include <stdio.h>

int main(int argc, char*argv[]) {
    int cookie = 0;
    char buf[80];

    gets(buf);

    if (cookie == 0x41424344)
        printf("YOU WIN!\n");

    return 0;
}
