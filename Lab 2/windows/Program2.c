#include <stdio.h>
#include <windows.h>

void main()
{
    HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE inputH = GetStdHandle(STD_OUTPUT_HANDLE);
    char fname[ ]="myresult.txt";

    HANDLE fhandle=CreateFile(fname, GENERIC_READ | GENERIC_WRITE, 0, 0,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    HANDLE fhandle2;
    DuplicateHandle( GetCurrentProcess(), fhandle, GetCurrentProcess(), &fhandle2, 0, FALSE,0);
    HANDLE fhandle3=CreateFile(fname, GENERIC_READ | GENERIC_WRITE, 0, 0,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    SetFilePointer(fhandle, 10, 0, FILE_BEGIN);

    char out[100];
    int len = sprintf(out, "\n%d\n%d\n%d", fhandle, fhandle2, fhandle3);
    WriteFile(fhandle, out, len, NULL, NULL);

    char hOut1[7];
    ReadFile(fhandle, hOut1, 7, NULL, NULL);
    char hOut2[7];
    ReadFile(fhandle, hOut1, 7, NULL, NULL);
    char hOut3[7];
    ReadFile(fhandle, hOut1, 7, NULL, NULL);

    len = sprintf(out, "\n%d\n%d\n%d", hOut1, hOut2, hOut3);

    WriteFile(inputH, out, len, NULL, NULL);

    CloseHandle(fhandle);
    CloseHandle(fhandle2);
    CloseHandle(fhandle3);
}
