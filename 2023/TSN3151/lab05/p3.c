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

    double a, b, w, sum = 0, middle;
    int i, n;

    if (!rank) {
        printf("Enter the number of intervals : ");
        fflush(stdout);
        scanf("%d", &n);

        a = M_PI / 2;
        b = 2 * M_PI;

        // step length (width of each slice)
        w = (b - a) / n;
        middle = w / 2;

        startTime = MPI_Wtime();
        for (i = 0; i < n; i++) {
            sum += f((a + i * w) + middle);
        }

        sum = sum * w;
        endTime = MPI_Wtime();

        printf("Answer : %f \n", sum);
        printf("Time Taken : %f \n", endTime - startTime);
    }

    MPI_Finalize();
}