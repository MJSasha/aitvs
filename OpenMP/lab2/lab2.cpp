#include <iostream>
#include <omp.h>

int main() {    int a = 10, b = 20, c, d, f;

    // Параллельная область с 3 потоками, a, b, c, d, f - общие
    #pragma omp parallel num_threads(3) shared(a, b, c, d, f)
    {
        // Разделяем работу на независимые секции
        #pragma omp sections
        {
            #pragma omp section
            {
                c = a + 1;
                std::cout << "Thread " << omp_get_thread_num() << ": c = " << c << std::endl;
            }

            #pragma omp section
            {
                d = b * 2;
                std::cout << "Thread " << omp_get_thread_num() << ": d = " << d << std::endl;
            }

            #pragma omp section
            {
                f = a + b;
                std::cout << "Thread " << omp_get_thread_num() << ": f = " << f << std::endl;
            }
        }
    }

    std::cout << "c = " << c << ", d = " << d << ", f = " << f << std::endl;
    return 0;
}
