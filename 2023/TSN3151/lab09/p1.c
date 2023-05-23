#include <omp.h>
#include <stdio.h>

int main() {
    int i;
    printf("Hello World\n");
#pragma omp parallel for shared(i)
    for (i = 0; i < 6; i++)
        printf("Iter:%d\n", i);

    printf("GoodBye World\n");
}