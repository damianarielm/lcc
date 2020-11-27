#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*function)();

struct A{
    function f;
    char data[256];
};


int read_int(){
    int ret;
    fscanf(stdin," %d ",&ret);
    return ret;
}

void lose(){ }
void win(){ printf ("YOU WIN!\n");}

int
main(int argc, char*argv[]){
    int i;
    struct A * p[1024];

    for(i=0;i<1024;i++){
        p[i] = malloc(sizeof(struct A)); 
        p[i]->f = lose;
        memset(p[i]->data,0,256);
    }

    i = read_int();
    free(p[i]);
    p[i] = malloc(sizeof(struct A)); 
    p[i]->f = lose;
    gets(p[i]->data);

    p[800]->f();

    //leak
    return 0;
}
