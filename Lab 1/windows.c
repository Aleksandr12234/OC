#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE inputHandle = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD bytesRead;

    CHAR buffer[256];
    
    CHAR out[100];
    int length= sprintf(out, "Input Handle: %p\n", inputHandle);
    WriteFile(outputHandle, out, length, NULL, NULL);
    length = sprintf(out, "output Handl: %p\n", outputHandle);
    WriteFile(outputHandle, out, length, NULL, NULL);
    
    WriteFile(outputHandle, "input: ", sizeof("input: ")-1, NULL, NULL);
    ReadFile(inputHandle, buffer, sizeof(buffer) - 1, &bytesRead, NULL);
    
    WriteFile(outputHandle, "out: ", sizeof("out: ")-1, NULL , NULL);
    WriteFile(outputHandle, buffer, bytesRead, NULL, NULL);
    
    return 0;
}