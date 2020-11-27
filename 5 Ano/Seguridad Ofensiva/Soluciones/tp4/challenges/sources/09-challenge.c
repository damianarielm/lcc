#include <string.h>
#include <stdio.h>
#include <assert.h>
int
main(int argc, char*argv[]){
    char buf[256];

    read(0,buf,256);
    assert( strstr(buf, "WIN!") == NULL);

    printf(buf);

return 0;
}
