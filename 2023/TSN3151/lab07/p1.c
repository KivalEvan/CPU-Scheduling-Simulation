#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 256

int main(int argc, char *argv[]) {
    int *data, result;
    int size, i;
    FILE *infile;
    char buf[BUFFER_SIZE];
    printf("What is the name of the data file?\n");
    fgets(buf, BUFFER_SIZE, stdin);
    buf[strlen(buf) - 1] = '\0';
    // Remove the carriage return from the file name
    infile = fopen(buf, "r");
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
        printf("%d ", data[i]);
    }
    printf("\n");
    result = 0;
    for (i = 0; i < size; i++)
        result += data[i];
    printf("Result: %d\n", result);
}