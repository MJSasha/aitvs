#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, numprocs;
    int data;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    if (numprocs != 2) {
        if (rank == 0) {
            printf("This example is intended to be run with exactly two processes.\n");
        }
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        // Process 0 sends data to process 1
        data = 12345;
        printf("Process 0 sends data %d to process 1.\n", data);
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        // Process 1 receives data from process 0
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Process 1 received data %d from process 0.\n", data);
    }

    MPI_Finalize();
    return 0;
}
