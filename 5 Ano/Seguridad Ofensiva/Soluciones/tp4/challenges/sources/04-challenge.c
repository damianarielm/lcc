#include<assert.h>
int
main(int argc, char*argv[]){
    int size = 0;
    int buf[1024];

    read(0,&size,sizeof(size));
    assert (size <= 1024);
    read(0,buf,size*sizeof(int));

    if (size > 0 && size < 100 && buf[999] == 'B')
        printf("YOU WIN!\n");

return 0;
}

