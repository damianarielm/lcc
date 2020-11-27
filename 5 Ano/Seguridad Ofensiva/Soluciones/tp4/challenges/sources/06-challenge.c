#include<stdlib.h>
void
win(){
    printf("YOU WIN!\n");
}

int
main(int argc, char*argv[]){
    void * buf01 = malloc(1024);
    char buf02[384];

    gets(buf02);
    strcpy(buf01,buf02);

    exit(-1);
}

