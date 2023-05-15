#include <mpi.h>
#include <stdio.h>

#define BUFFSIZE 256

int main(int argc, char *argv[]) {
    int numprocs, rank, namelen;
    char buffer[BUFFSIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(buffer, &namelen);

    MPI_Send(buffer, BUFFSIZE, MPI_CHARACTER, 0, 0, MPI_COMM_WORLD);

    if (!rank) {
        for (int i = 0; i < numprocs; ++i) {
            MPI_Recv(buffer, BUFFSIZE, MPI_CHARACTER, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s: Process %d out of %d\n", buffer, i + 1, numprocs);
        }
    }

    MPI_Finalize();
}