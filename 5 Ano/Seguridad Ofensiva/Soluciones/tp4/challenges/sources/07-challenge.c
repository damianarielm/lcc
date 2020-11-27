#include<stdio.h>

int table[1024];

int read_int(){
    int ret;
    fscanf(stdin,"%d",&ret);
    return ret;
}

int
main(int argc, char*argv[]){
    int offset;
    int value;
    
    do{
        offset = read_int();
        value = read_int();
        table[offset]=value;
    }while (offset<1024);

    exit(-1);

    printf("YOU WIN!\n");

}

