#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, numprocs;
    int N = 10;  // маленький массив
    double *A = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    // Проверим, что N кратно numprocs (иначе мы сейчас не обработаем этот случай)
    if (rank == 0) {
        if (N % numprocs != 0) {
            printf("Warning! N = %d is not divisible by numprocs = %d\n", N, numprocs);
            printf("This example code expects N %% numprocs == 0\n");
        }
    }

    int chunk = N / numprocs;  // размер блока для каждого процесса

    if (rank == 0) {
        A = (double *)malloc(N * sizeof(double));
        for(int i = 0; i < N; i++) {
            A[i] = i;
        }
    }

    double *local_A = (double *)malloc(chunk * sizeof(double));

    // Рассилка блоков
    MPI_Scatter(A, chunk, MPI_DOUBLE, local_A, chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Обработка локального блока
    for(int i = 0; i < chunk; i++) {
        local_A[i] *= 10.0;
    }

    // Сбор обратно
    MPI_Gather(local_A, chunk, MPI_DOUBLE, A, chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Процесс 0 печатает весь массив
    if (rank == 0) {
        printf("Modified array A after multiplication by 10:\n");
        for (int i = 0; i < N; i++) {
            printf("%f ", A[i]);
        }
        printf("\n");
        free(A);
    }

    free(local_A);
    MPI_Finalize();
    return 0;
}
