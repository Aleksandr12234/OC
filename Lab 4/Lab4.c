#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd;
    char buffer[1024];
    ssize_t bytes_read;
    pid_t pid = getpid();
    struct flock lock;
    
    fd = open("read.txt", O_RDWR | O_CREAT, 0600);
    if (fd == -1) {
        write(STDERR_FILENO, "error open file\n", 17);
        return 1;
    }
    
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = pid;
    

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        write(STDOUT_FILENO, "file blocked from out\n", 23);
        lock.l_type = F_WRLCK;
        if (fcntl(fd, F_SETLKW, &lock) == -1) {
            write(STDERR_FILENO, "error\n", 7);
            close(fd);
            return 1;
        }
    }
    
    write(STDOUT_FILENO, "blocked sucsful\n", 17);
    
    lseek(fd, 0, SEEK_SET);
    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        write(STDOUT_FILENO, "file:\n", 7);
        write(STDOUT_FILENO, buffer, bytes_read);
        write(STDOUT_FILENO, "\n", 1);
    } 
    
    write(STDOUT_FILENO, "\nwait\n", 6);
    sleep(7);
    
    lock.l_type = F_UNLCK;

    close(fd);
    
    return 0;
}