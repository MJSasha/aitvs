#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 100000

int main(int argc, char *argv[]) {
    int rank, numprocs;
    double *array = NULL; // Pointer to the array that will be broadcast

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get the rank of the current process
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs); // Get the total number of processes

    /* The process with the highest rank creates the initial array */
    if (rank == numprocs - 1) {
        array = (double *)malloc(ARRAY_SIZE * sizeof(double));
        for (int i = 0; i < ARRAY_SIZE; i++) {
            array[i] = (double)i * 0.5;  // Fill with arbitrary values
        }
        printf("Process %d prepared the data array of size %d\n", rank, ARRAY_SIZE);
    } else {
        /* Other processes allocate memory to receive the array */
        array = (double *)malloc(ARRAY_SIZE * sizeof(double));
    }

    /* Broadcast the array: all processes receive a copy of the array.
       Use MPI_Bcast, called by all processes.
       The root process is the one with rank numprocs-1 */
    MPI_Bcast(array, ARRAY_SIZE, MPI_DOUBLE, numprocs - 1, MPI_COMM_WORLD);

    /* Each process can check that the data was received correctly: */
    printf("Process %d received array[0] = %f\n", rank, array[0]);

    free(array);
    MPI_Finalize();
    return 0;
}
