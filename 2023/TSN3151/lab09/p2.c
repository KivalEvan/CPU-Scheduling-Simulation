#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MATRIX_SIZE 3

float dot_prod(float* a, float* b, int N) {
    float sum = 0.0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < N; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

int main(int argc, char *argv[]) {
    float aryA[MATRIX_SIZE], aryB[MATRIX_SIZE];
    srandom(time(0));
    for (int i = 0; i < MATRIX_SIZE; i++) {
        aryA[i] = i + 1;
        aryB[i] = i + 1;
    }
    printf("%f\n", dot_prod(aryA, aryB, MATRIX_SIZE));
}

