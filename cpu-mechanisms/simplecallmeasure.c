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
    int repeat = 100000;
    int pipefd[2];
    char buffer[1];

    pipe(pipefd);
    gettimeofday(&start, NULL);
    for (int i = 0; i < repeat; i++) {
        read(pipefd[0], buffer, 0);
    }
    gettimeofday(&end, NULL);
    close(pipefd[0]);
    close(pipefd[1]);

    long seconds = end.tv_sec - start.tv_sec;
    long useconds = end.tv_usec - start.tv_usec;
    long total = seconds * 1000000 + useconds;

    printf("Time taken: %ld microseconds\n", total);
    printf("Time per call: %f microseconds\n", (double) total / repeat);
    return 0;
}