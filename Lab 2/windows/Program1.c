#include <stdio.h>
#include <windows.h>

void main()
{
    DWORD actlen;
    HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);

    char buffer[]="1)";
    char text[100];
    char fname[ ]="myresult.txt";

    HANDLE fhandle=CreateFile(fname, GENERIC_WRITE, 0, 0,CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

    ReadFile(hstdin, text, 100, &actlen, NULL);

    WriteFile(fhandle, buffer, 2, NULL, NULL);
    WriteFile(fhandle, text, actlen, NULL, NULL);

    CloseHandle(fhandle);
}
