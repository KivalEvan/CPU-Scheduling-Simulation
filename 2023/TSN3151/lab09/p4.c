#include <math.h>
#include <omp.h>
#include <stdio.h>

#define START (M_PI / 2)
#define END (M_PI * 2)

double f(double x) { return sin(x / 2) + 1; }
int main(int argc, char *argv[]) {
  double total = 0, x;
  int partitions, i;
  double slice;
  double start, end;
  printf("How many partitions? ");
  fflush(stdout);
  scanf("%d", &partitions);
  start = omp_get_wtime();
  slice = (END - START) / partitions;
#pragma omp parallel for private(x) reduction(+ : total)
  for (i = 0; i < partitions; i++) {
    x = START + (slice / 2) + i * slice;
    total += f(x);
  }
  total *= slice;
  end = omp_get_wtime();
  printf("The integration is %1.20f\n", total);
  printf("Finished in %f seconds\n", end - start);
}
