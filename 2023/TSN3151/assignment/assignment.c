#include <mpi.h>
#include <stdio.h>

#define BUFFERSIZE 256

int main(int argc, char *argv[]) {
  int p, np, min, max;
char buffer[256];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &p);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  if (!p) {
    printf("Enter text file name:");
    fflush(stdout);
    scanf("%s", buffer);

    printf("Enter minimum and maximum number of word length:");
    fflush(stdout);
    scanf("%d %d", &min, &max);
    printf("\n");
  }

  MPI_Bcast(&min, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&max, 1, MPI_INT, 0, MPI_COMM_WORLD);

  if (min > max) {
    return 1;
  }



  MPI_Finalize();
}
