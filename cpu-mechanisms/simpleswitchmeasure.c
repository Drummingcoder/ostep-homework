#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct timeval start, end;
    int repeat = 1000;
    int pipefd1[2], pipefd2[2];
    char buffer[1];

    pipe(pipefd1);
    pipe(pipefd2);
    int pid = fork();

    if (pid == 0) {
        for (int i = 0; i < repeat; i++) {
            read(pipefd1[0], buffer, 0);
            write(pipefd2[1], "t", 1);
        }
    } else {
        gettimeofday(&start, NULL);
        for (int i = 0; i < repeat; i++) {
            write(pipefd1[1], "d", 1);
            read(pipefd2[0], buffer, 0);
        }
        gettimeofday(&end, NULL);

        long seconds = end.tv_sec - start.tv_sec;
        long useconds = end.tv_usec - start.tv_usec;
        long total = seconds * 1000000 + useconds;

        printf("Time taken: %ld microseconds\n", total);
        printf("Time per call: %f microseconds\n", (double) total / repeat);
    }
    return 0;
}