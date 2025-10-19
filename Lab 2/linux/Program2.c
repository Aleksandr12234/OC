#include <stdio.h>
#include <fcntl.h>

void main()
{
    char fname[ ]="myresult.txt";

    int fhandle=open(fname, O_WRONLY, 0600);
    int fhandle2 = dup(fhandle);
    int fhandle3=open(fname, O_WRONLY, 0600);

    lseek(fhandle, 10, SEEK_SET);

    char out[100];
    int len = sprintf(out, "\n%d\n%d\n%d", fhandle, fhandle2, fhandle3);
    write(fhandle, out, len);


    close(fhandle);
    close(fhandle2);
    close(fhandle3);
}
