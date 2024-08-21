#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void vector_scalar_addition_dynamic(int *vector, int size, int scalar, int chunk_size) {
    #pragma omp parallel for schedule(dynamic, chunk_size)
    for (int i = 0; i < size; i++) {
        vector[i] += scalar;
    }
}

int main() {
    int size = 200;
    int scalar = 5;
    int chunk_sizes[] = {1, 5, 10, 20}; 
    int num_chunks = sizeof(chunk_sizes) / sizeof(chunk_sizes[0]);
    int *vector = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 100; 
    }

    for (int c = 0; c < num_chunks; c++) {
        int chunk_size = chunk_sizes[c];

        double start_time = omp_get_wtime();
        vector_scalar_addition_dynamic(vector, size, scalar, chunk_size);
        double end_time = omp_get_wtime();

        printf("Dynamic Schedule, Chunk Size: %d, Time: %f seconds\n", chunk_size, end_time - start_time);
    }

    free(vector);
    return 0;
}
