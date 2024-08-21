#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>


int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int reverse_compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int n = 100000;  
    int *vectorA = (int *)malloc(n * sizeof(int));
    int *vectorB = (int *)malloc(n * sizeof(int));
    long long min_scalar_product = 0;
    srand(0);
    for (int i = 0; i < n; i++) {
        vectorA[i] = rand() % 100;
        vectorB[i] = rand() % 100;
    }
    qsort(vectorA, n, sizeof(int), compare);
    qsort(vectorB, n, sizeof(int), reverse_compare);
    #pragma omp parallel for reduction(+:min_scalar_product)
    for (int i = 0; i < n; i++) {
        min_scalar_product += (long long)vectorA[i] * vectorB[i];
    }

    printf("Minimum Scalar Product: %lld\n", min_scalar_product);

    free(vectorA);
    free(vectorB);

    return 0;
}
