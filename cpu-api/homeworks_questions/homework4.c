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
        char *myargs[2];
        myargs[0] = "./bin/ls";
        myargs[1] = NULL;
        execvp(myargs[0], myargs);
        exit(0);
    } else if (pid < 0) {
        perror("fork");
        return 1;
    } else {
        wait(NULL);
        printf("goodbye\n");
    }
    return 0;
}