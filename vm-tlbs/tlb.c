#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define PAGE_SIZE 4096

long get_time_in_ns() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long)ts.tv_sec * 1000000000L + ts.tv_nsec;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s <num_pages> <num_trials>\n", argv[0]);
        exit(1);
    }

    int num_pages = atoi(argv[1]);
    int num_trials = atoi(argv[2]);
    int array_size = num_pages * PAGE_SIZE;
    char *array = malloc(array_size);
    if (array == NULL) {
        perror("malloc");
        exit(1);
    }

    // Touch each page once to ensure allocation
    for (int i = 0; i < num_pages; i++) {
        array[i * PAGE_SIZE] = 0;
    }

    long start = get_time_in_ns();

    volatile int dummy_sum = 0;  // Prevent optimization
    for (int t = 0; t < num_trials; t++) {
        for (int i = 0; i < num_pages; i++) {
            array[i * PAGE_SIZE]++;
            dummy_sum += array[i * PAGE_SIZE];
        }
    }

    long end = get_time_in_ns();
    double total_accesses = (double)num_pages * num_trials;
    double avg_time_per_access_ns = (double)(end - start) / total_accesses;

    printf("Average time per page access: %.2f ns\n", avg_time_per_access_ns);

    if (dummy_sum < 0) printf("Dummy: %d\n", dummy_sum);

    free(array);
    return 0;
}
