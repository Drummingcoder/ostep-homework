#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Vector;

// Initialize the vector
void vector_init(Vector *vec) {
    vec->size = 0;
    vec->capacity = 4; // initial capacity
    vec->data = malloc(vec->capacity * sizeof(int));
}

// Add an element to the vector
void vector_push_back(Vector *vec, int value) {
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        int *new_data = realloc(vec->data, vec->capacity * sizeof(int));
        if (!new_data) {
            fprintf(stderr, "realloc failed\n");
            exit(1);
        }
        vec->data = new_data;
    }
    vec->data[vec->size++] = value;
}

// Get an element at a specific index
int vector_get(Vector *vec, size_t index) {
    if (index >= vec->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(1);
    }
    return vec->data[index];
}

// Free the vector
void vector_free(Vector *vec) {
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

// Example usage
int main() {
    Vector vec;
    vector_init(&vec);

    for (int i = 0; i < 10; i++) {
        vector_push_back(&vec, i * 10);
    }

    for (size_t i = 0; i < vec.size; i++) {
        printf("vec[%zu] = %d\n", i, vector_get(&vec, i));
    }

    vector_free(&vec);
    return 0;
}