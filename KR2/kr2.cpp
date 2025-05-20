#include <iostream>
#include <omp.h>

int main() {
    // Установка числа нитей
    omp_set_num_threads(4);

    #pragma omp parallel
    {
        // Получение номера нити и количества нитей
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        #pragma omp critical
        // Вывод информации о нити
        std::cout << "Thread " << thread_id << " of " << num_threads << std::endl;

        #pragma omp single
        {
            // Вывод сообщения и номера нити, выполняющей single-секцию
            std::cout << "Hello single from thread " << omp_get_thread_num() << std::endl;
        }
    }

    return 0;
}
