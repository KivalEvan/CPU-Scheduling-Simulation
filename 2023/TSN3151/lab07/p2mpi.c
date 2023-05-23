#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 256

int main(int argc, char *argv[]) {
    int p, np;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &p);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int i, size, eachSize, *ary, *localAry;
    char filename[BUFFER_SIZE];
    FILE *outfile;

    if (!p) {
        printf("What is the file name you want to write to? ");
        fflush(stdout);
        scanf("%s", filename);
        printf("How many long integers to generate? ");
        fflush(stdout);
        scanf("%d", &size);
        outfile = fopen(filename, "w");
        if (!outfile) {
            fprintf(stderr, "Unable to open %s for writing.\n", filename);
            exit(1);
        }
        fprintf(outfile, "%d\n", size);
        ary = (int *)malloc(sizeof(int) * size);
    }

    srandom(time(0));
    MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    eachSize = size / np;
    localAry = (int *)malloc(sizeof(int) * eachSize);
    for (i = 0; i < eachSize; i++)
        localAry[i] = random();

    MPI_Gather(localAry, eachSize, MPI_INT, ary, eachSize, MPI_INT, 0, MPI_COMM_WORLD);

    if (!p) {
        for (i = 0; i < size - (size % np); i++)
            fprintf(outfile, "%ld\n", ary[i]);
        for (i = 0; i < size % np; i++)
            fprintf(outfile, "%ld\n", random());
        fclose(outfile);
    }

    MPI_Finalize();
}