#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int pipefd[2];
    pipe(pipefd);
    int pid = fork();
    if (pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        printf("What's going on...\n");
        close(pipefd[1]);
        exit(0);
    } else if (pid < 0) {
        perror("fork");
        return 1;
    } else {
        int pid2 = fork();
        if (pid2 == 0) {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            char buffer[128];
            fgets(buffer, sizeof(buffer), stdin);
            printf("Child 2 received: %s", buffer);
            close(pipefd[0]);
            exit(0);
        } else {
            wait(NULL);
            close(pipefd[0]);
            close(pipefd[1]);
        }
    }
    return 0;
}