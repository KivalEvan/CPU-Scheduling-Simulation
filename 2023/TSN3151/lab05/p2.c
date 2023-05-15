#include <mpi.h>
#include <stdio.h>

#define BUFFSIZE 256

double f(double x) {
    return 4 / (1 + x * x);
}

double pi(int part) {
    double step = 1.0 / part;
    double x, total = 0;
    int i;

    for (i = 0; i < part; i++) {
        x = (step / 2) + step * i;
        total = total + f(x);
    }

    return total * step;
}

int main(int argc, char *argv[]) {
    int numprocs, rank, namelen;
    char buffer[BUFFSIZE];

    int partitions;
    double result;
    double startTime, endTime;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(buffer, &namelen);

    if (!rank) {
        printf("Calculating Pi: How many partitions? ");
        fflush(stdout);
        scanf("%d", &partitions);

        startTime = MPI_Wtime();
        result = pi(partitions);
        endTime = MPI_Wtime();

        printf("Pi is approximately %1.20f using %d partitions in %fs\n", result, partitions, endTime - startTime);
    }

    MPI_Finalize();
}