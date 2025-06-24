#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MB (1024 * 1024)

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <megabytes> [seconds]\n", argv[0]);
        return 1;
    }

    int mb = atoi(argv[1]);
    if (mb <= 0) {
        fprintf(stderr, "Invalid megabytes value.\n");
        return 1;
    }

    int seconds = 0;
    if (argc >= 3) {
        seconds = atoi(argv[2]);
        if (seconds < 0) seconds = 0;
    }

    size_t size = (size_t)mb * MB;
    char *array = malloc(size);
    if (!array) {
        perror("malloc");
        return 1;
    }

    printf("PID: %d, Allocating %d MB of memory\n", getpid(), mb);

    // Touch all memory to ensure allocation
    memset(array, 0, size);

    time_t start = time(NULL);

    while (1) {
        for (size_t i = 0; i < size; i += 4096) {
            array[i] = 1; // Touch each page
        }
        if (seconds > 0 && (time(NULL) - start) >= seconds) {
            break;
        }
    }

    free(array);
    return 0;
}