#include <mpi.h>
#include <stdio.h>

#define BUFFSIZE 256

int main(int argc, char *argv[]) {
    int numprocs, rank, namelen;
    char buffer[BUFFSIZE];

    int value = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(buffer, &namelen);

    while (value >= 0) {
        if (!rank) {
            printf("Enter an integer: ");
            fflush(stdout);
            scanf("%d", &value);
        }

        MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);

        printf("Process %d | %d : %d\n", rank + 1, numprocs, value);
    }

    MPI_Finalize();
}