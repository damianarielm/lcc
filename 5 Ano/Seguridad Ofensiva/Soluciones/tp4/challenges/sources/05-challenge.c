#include<assert.h>
int
main(int argc, char*argv[]){
    int buf[1024];
    int size = 0;

    read(0,&size,sizeof(size));
    assert(size <= 1024);
    read(0,buf,size*sizeof(int));

    if (size == 0x10 && buf[1001] == 0xCAC0FACE)
        printf("YOU WIN!\n");

return 0;
}
