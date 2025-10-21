#include <stdio.h>
#include <fcntl.h>

void main()
{
    char buffer[]="1)";
    char text[100];

    char fname[ ]="myresult.txt";

    int fhandle=open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0600);

    int len = read(0, text, sizeof(text)-1);

    write(fhandle, buffer, sizeof(buffer)-1);
    write(fhandle, text, len);

    close(fhandle);
}
