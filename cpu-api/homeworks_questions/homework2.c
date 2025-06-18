#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd = open("file.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    const char *msg = "what up";
    write(fd, msg, 7);
    char buffer[100];
    close(fd);
    fd = open("file.txt", O_RDWR);
    int pid = fork();
    if (pid == 0) {
        write(fd, "\nmore children please\n", 22);
        exit(0);
    } else if (pid < 0) {
        perror("fork");
        return 1;
    } else {
        write(fd, "\nmore parents please\n", 22);
    }
    close(fd);
    fd = open("file.txt", O_RDWR);
    int bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    buffer[bytes_read] = '\0';
    printf("We read: %s\n", buffer);
    return 0;
}