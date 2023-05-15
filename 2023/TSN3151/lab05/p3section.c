#include <math.h>
#include <mpi.h>
#include <stdio.h>

#define BUFFSIZE 256

float f(float x) {
    return (sin(x / 2) + 1);
}

int main(int argc, char *argv[]) {
    int numprocs, rank, namelen;
    char buffer[BUFFSIZE];
    double startTime, endTime;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(buffer, &namelen);

    double a, b, w, sum = 0, middle, result;
    int i, n;

    if (!rank) {
        printf("Enter the number of intervals : ");
        fflush(stdout);
        scanf("%d", &n);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    a = M_PI / 2;
    b = 2 * M_PI;

    // step length (width of each slice)
    w = (b - a) / n;
    middle = w / 2;

    int startIndex = n / numprocs * rank;
    int endIndex = n / numprocs * (rank + 1);
    if (rank == (numprocs - 1)) endIndex += n % numprocs;

    startTime = MPI_Wtime();
    for (i = startIndex; i < endIndex; i++) {
        sum += f((a + i * w) + middle);
    }
    MPI_Reduce(&sum, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (!rank) {
        result *= w;
        endTime = MPI_Wtime();
        printf("Answer : %f \n", result);
        printf("Time Taken : %f \n", endTime - startTime);
    }

    MPI_Finalize();
}
