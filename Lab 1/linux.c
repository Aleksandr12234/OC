#include <stdio.h>
#include <unistd.h>

int main() {
    char buffer[256];
    
    if (isatty(STDIN_FILENO)) {
        char text[] = "input: ";
        write(STDERR_FILENO, text, sizeof(text)-1);
    }
    
    ssize_t bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
    
    char text[] = "out: ";
    write(STDOUT_FILENO, text, sizeof(text)-1);
    write(STDOUT_FILENO, buffer, bytesRead);
    
    return 0;
}