#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int pid = fork();
    if (pid == 0) {
        printf("hello\n");
        exit(0);
    } else if (pid < 0) {
        perror("fork");
        return 1;
    } else {
        sleep(1);
        printf("goodbye\n");
    }
    return 0;
}