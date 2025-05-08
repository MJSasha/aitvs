#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, numprocs;
    double a, sum; // a - локальное значение, sum - результат редукции

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Получаем номер текущего процесса
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs); // Получаем общее количество процессов

    /* Каждый процесс вычисляет своё значение */
    a = 0.01 * rank;
    printf("Process %d has value a = %f\n", rank, a);

    /* Выполняется операция редукции (суммирование) */    MPI_Reduce(&a, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    /* Процесс с номером 0 выводит результат */
    if (rank == 0) {
        printf("Sum of values from all processes = %f\n", sum);
    }

    MPI_Finalize();
    return 0;
}
