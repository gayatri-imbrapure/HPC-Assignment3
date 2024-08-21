#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void initialize_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 100; 
        }
    }
}
void matrix_addition(int **A, int **B, int **C, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}
int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int threads[] = {2, 4, 8};
    int num_threads = sizeof(threads) / sizeof(threads[0]);

    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];
        int **A = (int **)malloc(size * sizeof(int *));
        int **B = (int **)malloc(size * sizeof(int *));
        int **C = (int **)malloc(size * sizeof(int *));
        
        for (int i = 0; i < size; i++) {
            A[i] = (int *)malloc(size * sizeof(int));
            B[i] = (int *)malloc(size * sizeof(int));
            C[i] = (int *)malloc(size * sizeof(int));
        }
        initialize_matrix(A, size);
        initialize_matrix(B, size);

        for (int t = 0; t < num_threads; t++) {
            omp_set_num_threads(threads[t]);

            double start_time = omp_get_wtime();
            matrix_addition(A, B, C, size);
            double end_time = omp_get_wtime();

            printf("Matrix Size: %d x %d, Threads: %d, Time: %f seconds\n",
                   size, size, threads[t], end_time - start_time);
        }

        for (int i = 0; i < size; i++) {
            free(A[i]);
            free(B[i]);
            free(C[i]);
        }
        free(A);
        free(B);
        free(C);
    }

    return 0;
}
