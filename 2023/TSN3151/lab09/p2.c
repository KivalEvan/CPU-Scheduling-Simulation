#include <omp.h>
#include <stdio.h>

float dot_prod(float* a, float* b, int N) {
    float sum = 0.0;
#pragma omp parallel for shared(sum)
    for (int i = 0; i < N; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}