// trapezoidal
#include <math.h>
#include <mpi.h>
#include <stdio.h>

double f(double x) {
    return (sin(x / 2) + 1);
}

int main(int argc, char *argv[]) {
    int p, np;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &p);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    double a, b, w, sum = 0, y[2];
    int i, n;
    if (!p) {
        printf("Enter the number of intervals : ");
        fflush(stdout);
        scanf("%d", &n);
        a = M_PI / 2;
        b = 2 * M_PI;
        // step length (width of each trapezoid)
        w = (b - a) / n;
        // Initialize the heights
        y[0] = f(a);
        for (i = 1; i <= n; i++) {
            y[i % 2] = f(a + i * w);
            sum += y[i % 2] + y[(i + 1) % 2];
        }
        // Multiply with half the width.
        sum = sum * w / 2;
        printf("Answer : %f \n", sum);
    }
    MPI_Finalize();
}