#include <iostream>
#include <fstream>
#include "matrix_multiply.h"
#include "util.h"

int main()
{
    srand(std::time(nullptr)); // NOLINT(cert-msc51-cpp)
    std::ofstream file("report");

    Matrix a = make_random_matrix(600, 600);
    Matrix b = make_random_matrix(600, 600);
    Matrix result = make_result_matrix(a, b);

    int trials = 10;

    file << "A " << a.size() << ' ' << a[0].size() << '\n';
    file << "B " << b.size() << ' ' << b[0].size() << '\n';
    file << "TRIALS " << trials << '\n';

    double avg = 0;
    for(int i = 0; i < trials; i++)
    {
        avg += time_execution_seconds([&a, &b, &result](){multiply(a, b, result);});
    }
    avg /= trials;
    file << "ITERATIVE " << avg << '\n';

    avg = 0;
    for(int i = 0; i < trials; i++)
    {
        avg += time_execution_seconds([&a, &b, &result](){multiply_parallel(a, b, result);});
    }
    avg /= trials;
    file << "THREADS " << avg << '\n';

    for (int threads = 2; threads <= 10; threads++)
    {
        avg = 0;
        std::unique_ptr<ThreadPool> pool(new ThreadPool(threads));
        for(int i = 0; i < trials; i++)
        {
            avg += time_execution_seconds([&a, &b, &result, &pool](){
                multiply_parallel_pool(a, b, result, pool);
            });
        }
        avg /= trials;
        file << "THREAD_POOL " << threads << " " << avg << '\n';
    }
    file.close();
    return 0;
}
