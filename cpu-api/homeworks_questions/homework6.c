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
        printf("Hello");
        exit(0);
    } else if (pid < 0) {
        perror("fork");
        return 1;
    } else {
        int rc_wait = waitpid(-1, NULL, 0);
        printf("\nReturned value: %d\n", rc_wait);
    }
    return 0;
}