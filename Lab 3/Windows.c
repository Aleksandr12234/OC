#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hFile, hStdOut;
    DWORD dwBytesRead;
    char buffer[4096];
    
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    
    hFile = CreateFile("read.txt", GENERIC_READ, 0,NULL, 
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    
    if (hFile == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        
        if (error == ERROR_FILE_NOT_FOUND) {
            WriteFile(hStdOut, "file not found\n", 15, NULL, NULL);
        } 
        else if (error == ERROR_SHARING_VIOLATION) {
            WriteFile(hStdOut, "file block\n", 11, NULL, NULL);
            
            while (TRUE)
             {
                Sleep(1000);
                hFile = CreateFile("read.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                if (hFile != INVALID_HANDLE_VALUE) {
                    break;
                }
            }
        }
    }
    
    WriteFile(hStdOut, "file:\n", 6, NULL, NULL);
    
    while (ReadFile(hFile, buffer, sizeof(buffer)-1, &dwBytesRead, NULL) && dwBytesRead > 0) {
        buffer[dwBytesRead] = '\0';
        WriteFile(hStdOut, buffer, dwBytesRead, NULL, NULL);
    }

    WriteFile(hStdOut, "\npress Enter\n", 13, NULL, NULL);
    getchar();
    
    CloseHandle(hFile);
    return 0;
}
