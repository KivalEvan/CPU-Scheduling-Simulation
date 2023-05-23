#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

int xsize = 20000, ysize = 10000, maxIteration = 512;
double cx = -0.79, cy = 0.15, xscale = 3.5, xoffset = 1.7, yscale = 2.0, yoffset = 1.0;

int julia(int x, int y) {
    double zx = (double)x / xsize * xscale - xoffset;
    double zy = (double)y / ysize * yscale - yoffset;

    int iteration = 0;

    while ((iteration < maxIteration) && (zx * zx + zy * zy < 4)) {
        double xtemp = zx * zx - zy * zy;
        zy = 2 * zx * zy + cy;
        zx = xtemp + cx;

        iteration++;
    }

    return iteration;
}

int main(int argc, char *argv[]) {
    int p, np;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &p);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int x, y;
    int **picture;
    char buff[BUFFER_SIZE];
    FILE *outfile;

    if (!p) {
        printf("Program to generate a Julia fractal\n");
        printf("What file should I store the picture in? [E.g. julia.pgm] ");
        fflush(stdout);
        fgets(buff, BUFFER_SIZE, stdin);
        buff[strlen(buff) - 1] = 0;  // Remove the ending line feed
        printf("How wide and tall should the picture be? [E.g. 1920 1080] ");
        fflush(stdout);
        scanf("%d %d", &xsize, &ysize);
        printf("What is the x scale and x offset? [E.g. 3.5 1.7] ");
        fflush(stdout);
        scanf("%lf %lf", &xscale, &xoffset);
        printf("What is the y scale and y offset? [E.g. 2.0 1.0] ");
        fflush(stdout);
        scanf("%lf %lf", &yscale, &yoffset);
        printf("What are the x and y components of the Julia constant? [E.g -0.79 0.15] ");
        fflush(stdout);
        scanf("%lf %lf", &cx, &cy);
        printf("How many times to iterate? [E.g. 512] ");
        fflush(stdout);
        scanf("%d", &maxIteration);
    }

    MPI_Bcast(&xsize, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&xoffset, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&xscale, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&ysize, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&yoffset, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&yscale, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&cx, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&cy, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&maxIteration, 1, MPI_INT, 0, MPI_COMM_WORLD);

    picture = (int **)malloc(sizeof(int *) * ysize);

    if (!p)
        for (y = 0; y < ysize; y++)
            picture[y] = (int *)malloc(sizeof(int) * xsize);

    for (y = p; y < ysize; y += np) {
        if (p) picture[y] = (int *)malloc(sizeof(int) * xsize);
        for (x = 0; x < xsize; x++)
            picture[y][x] = julia(x, y);
    }

    if (p)
        for (y = p; y < ysize; y += np) {
            MPI_Send(picture[y], xsize, MPI_INT, 0, y, MPI_COMM_WORLD);
        }

    if (!p)
        for (y = 0; y < ysize; y++) {
            if (p != y % np) {
                MPI_Recv(picture[y], xsize, MPI_INT, y % np, y, MPI_COMM_WORLD, &status);
            }
        }

    printf("process %d done\n", p);
    if (!p) {
        printf("gaming\n");
        outfile = fopen(buff, "w");
        fprintf(outfile, "P2\n%d %d %d\n", xsize, ysize, maxIteration);
        for (y = 0; y < ysize; y++)
            for (x = 0; x < xsize; x++)
                fprintf(outfile, "%d\n", picture[y][x]);

        fclose(outfile);
    }

    MPI_Finalize();
}
