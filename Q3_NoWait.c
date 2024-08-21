#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void vector_scalar_addition_nowait(int *vector, int size, int scalar) {
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < size; i++) {
            vector[i] += scalar;
        }
        #pragma omp for
        for (int i = 0; i < size; i++) {
            vector[i] *= 2;
        }
    }
}

int main() {
    int size = 200; 
    int scalar = 5;
    int *vector = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 100; 
    }
    double start_time = omp_get_wtime();
    vector_scalar_addition_nowait(vector, size, scalar);
    double end_time = omp_get_wtime();

    printf("Nowait Clause, Time: %f seconds\n", end_time - start_time);

    free(vector);
    return 0;
}
