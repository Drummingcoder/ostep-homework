#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int x = 100;
    int pid = fork();
    if (pid == 0) {
        printf("My PID: %d. Variable value: %d\n", getpid(), x);
        x = 27;
        printf("My PID: %d. Variable value: %d\n", getpid(), x);
        exit(0);
    } else if (pid < 0) {
        perror("fork");
        return 1;
    } else {
        sleep(1);
        printf("My PID: %d. Variable value: %d\n", getpid(), x);
    }
    return 0;
}