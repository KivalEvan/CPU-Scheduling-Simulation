#include <mpi.h>
#include <stdio.h>

#define BUFFSIZE 256

double f(double x) {
    return 4 / (1 + x * x);
}

double pi(int part, int index, int numprocs) {
    double s = 1.0 / part;
    double x, total = 0;
    int section = (index + 1) * (part / numprocs);
    if (index == (numprocs - 1)) {
        section += part % numprocs;
    }
    int i = (index) * (part / numprocs);

    for (; i < section; i++) {
        x = (s / 2) + s * i;
        total = total + f(x);
    }

    return total * s;
}

int main(int argc, char *argv[]) {
    int numprocs, rank, namelen;
    char buffer[BUFFSIZE];

    int partitions;
    double localResult, result;
    double startTime, endTime;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(buffer, &namelen);

    if (!rank) {
        printf("Calculating Pi: How many partitions? ");
        fflush(stdout);
        scanf("%d", &partitions);
    }

    startTime = MPI_Wtime();
    MPI_Bcast(&partitions, 1, MPI_INT, 0, MPI_COMM_WORLD);
    localResult = pi(partitions, rank, numprocs);
    MPI_Reduce(&localResult, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    endTime = MPI_Wtime();

    if (!rank) {
        printf("Pi is approximately %1.20f using %d partitions section with %d processes in %fs\n", result, partitions, numprocs, endTime - startTime);
    }

    MPI_Finalize();
}