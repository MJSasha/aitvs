#include <iostream>
#include <omp.h>

int main() {    // Параллельная область с 8 потоками
    #pragma omp parallel num_threads(8)
    {
        // Получаем ID текущего потока
        int thread_id = omp_get_thread_num();

        // Четный поток - "Hello", нечетный - "Goodbye"
        if (thread_id % 2 == 0) {
            std::cout << "Thread " << thread_id << ": Hello" << std::endl;
        } else {
            std::cout << "Thread " << thread_id << ": Goodbye" << std::endl;
        }
    }
    return 0;
}
