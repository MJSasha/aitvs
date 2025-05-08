#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 5 // Short array size

int main(int argc, char *argv[]) {
    int rank, numprocs;
    int *array = NULL; // Changed to int for easier printing

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    /* The process with the highest rank creates the initial array */
    if (rank == numprocs - 1) {
        array = (int *)malloc(ARRAY_SIZE * sizeof(int));
        for (int i = 0; i < ARRAY_SIZE; i++) {
            array[i] = rank * 10 + i; // Fill with rank-specific values
        }
        printf("Process %d prepared the data array: ", rank);
        for(int i = 0; i < ARRAY_SIZE; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
    } else {
        /* Other processes allocate memory to receive the array */
        array = (int *)malloc(ARRAY_SIZE * sizeof(int));
    }

    /* Broadcast the array: all processes receive a copy of the array.
       Use MPI_Bcast, called by all processes.
       The root process is the one with rank numprocs-1 */
    MPI_Bcast(array, ARRAY_SIZE, MPI_INT, numprocs - 1, MPI_COMM_WORLD); // Changed MPI_DOUBLE to MPI_INT

    /* Each process can check that the data was received correctly: */
    printf("Process %d received array: ", rank);
    for(int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    MPI_Finalize();
    return 0;
}
