#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>


void win(){
    printf("YOU WIN!\n");
}

void func(){
    char buf[0xff];
    read(0,buf,256);
}

int
main(int argc, char*argv[]){
    func();
return 0;
}



