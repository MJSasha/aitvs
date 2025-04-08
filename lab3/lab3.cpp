#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, numprocs;
    int N = 1000000; // длина массива
    double *A = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    // Выделяем память для массива (лишь у процесса 0, далее данные рассылаются)
    if (rank == 0) {
        A = (double *)malloc(N * sizeof(double));
        for (int i = 0; i < N; i++) {
            A[i] = i;
        }
    }

    // Определяем размеры блоков для каждого процесса
    int chunk = N / numprocs;
    double *local_A = (double *)malloc(chunk * sizeof(double));

    // Рассылка блока данных каждому процессу (используем MPI_Scatter)
    MPI_Scatter(A, chunk, MPI_DOUBLE, local_A, chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Каждый процесс преобразует свой блок: умножает элементы на 10
    for (int i = 0; i < chunk; i++) {
        local_A[i] = local_A[i] * 10.0;
    }

    // Сбор обработанных блоков в исходный массив на процессе 0 (MPI_Gather)
    MPI_Gather(local_A, chunk, MPI_DOUBLE, A, chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Процесс 0 может проверить результат
    if (rank == 0) {
        printf("After multiplication A[0] = %f, A[N-1] = %f\n", A[0], A[N-1]);
        free(A);
    }
    free(local_A);

    MPI_Finalize();
    return 0;
}
