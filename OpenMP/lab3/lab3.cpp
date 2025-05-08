#include <iostream>
#include <omp.h>

int main() {
    int a = 11;

    // Параллельная область с 4 потоками, a - общая
    #pragma omp parallel num_threads(4) shared(a)
    {
        int thread_id = omp_get_thread_num();
        std::cout << "Thread " << thread_id << ": Hello" << std::endl;

        // Критическая секция - только один поток может выполнять этот код
        #pragma omp critical
        {
            a += 1;
            std::cout << "Thread " << thread_id << ": a = " << a << " after increment" << std::endl;
        }
    }

    std::cout << "a = " << a << std::endl;
    return 0;
}
