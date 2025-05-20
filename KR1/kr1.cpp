#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Проверяем что работает минимум с 3 процессами
    if(size < 3) {
        if(rank == 0)
            printf("This program requires at least 3 MPI processes.\n");
        MPI_Finalize();
        return 1;
    }

    if(rank == 1) {
        int a = 555;
        int b = 666;
        // Отправляем a процессу 0
        MPI_Send(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        // Отправляем b процессу 2
        MPI_Send(&b, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
    }
    else if(rank == 0) {
        int a;
        MPI_Recv(&a, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received a = %d from process 1\n", a);
    }
    else if(rank == 2) {
        int b;
        MPI_Request request;
        MPI_Irecv(&b, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);

        // Ждём завершения неблокирующего приема
        MPI_Wait(&request, MPI_STATUS_IGNORE);

        printf("Process 2 received b = %d from process 1\n", b);
        printf("Total number of processes in MPI_COMM_WORLD = %d\n", size);
    }

    MPI_Finalize();
    return 0;
}
