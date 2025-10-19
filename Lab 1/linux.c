#include <stdio.h>
#include <unistd.h>

int main() {
    char buffer[256];
    
    if (isatty(1)) {
        char text[] = "input: ";
        write(1, text, sizeof(text)-1);
    }
    
    ssize_t bytesRead = read(0, buffer, sizeof(buffer) - 1);
    
    char text[] = "out: ";
    write(1, text, sizeof(text)-1);
    write(1, buffer, bytesRead);
    
    return 0;
}