#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

int main(int argc, char *argv[]) {
    int p, np;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &p);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int *data, result;
    int size, i;
    FILE *infile;
    char buffer[BUFFER_SIZE];

    int *eachData, eachSize, eachResult;

    if (!p) {
        printf("What is the name of the data file?\n");
        fflush(stdout);
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        // Remove the carriage return from the file name
        infile = fopen(buffer, "r");
        if (infile == NULL) {
            perror("Opening file");
            exit(1);
        }
        fscanf(infile, "%d", &size);  // Find out how big the data is
        printf("Size = %d\n", size);
        data = (int *)malloc(sizeof(int) * size);  // Allocate the space
        for (i = 0; i < size; i++) {
            // Read the data
            fscanf(infile, "%d", &data[i]);
            // printf("%d ", data[i]);
        }
        printf("\n");
    }

    MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    eachSize = size / np;
    eachData = (int *)malloc(sizeof(int) * eachSize);
    MPI_Scatter(data, eachSize, MPI_INT, eachData, eachSize, MPI_INT, 0, MPI_COMM_WORLD);

    result = 0;
    eachResult = 0;
    for (i = 0; i < eachSize; i++)
        eachResult += eachData[i];

    if (!p) {
        i = size - (size % np);
        while (data[i]) {
            eachResult += data[i++];
        }
    }

    MPI_Reduce(&eachResult, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (!p) {
        printf("Result: %d\n", result);
    }

    MPI_Finalize();
}