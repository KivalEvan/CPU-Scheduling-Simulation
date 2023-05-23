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

    double a, b, w, sum = 0, y[2], total;
    int i, n;

    if (!p) {
        printf("Enter the number of intervals : ");
        fflush(stdout);
        scanf("%d", &n);
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    a = M_PI / 2;
    b = 2 * M_PI;
    // step length (width of each trapezoid)
    w = (b - a) / n;

    int startIndex = n / np * p + 1;
    int endIndex = n / np * (p + 1);
    if (p == (np - 1)) endIndex += n % np;

    // Initialize the heights
    y[(startIndex - 1) % 2] = f(a + (startIndex - 1) * w);
    for (i = startIndex; i <= endIndex; i++) {
        y[i % 2] = f(a + i * w);
        sum += y[i % 2] + y[(i + 1) % 2];
    }
    // Multiply with half the width.
    sum = sum * w / 2;

    MPI_Reduce(&sum, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (!p) printf("Answer : %f \n", total);

    MPI_Finalize();
}