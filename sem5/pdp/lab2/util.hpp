//
// Created by bratu on 10/20/2020.
//


#include <functional>

double make_random_double(double lo, double hi)
{
    double f = (double)rand() / RAND_MAX; // NOLINT(cert-msc50-cpp)
    return lo + f * (hi - lo);
}

std::vector<double> make_random_vector(int size)
{
    std::vector<double> new_vector(size);
    for (int i = 0; i < size; i++)
    {
        new_vector.push_back(make_random_double(-50, 50));
    }
    return new_vector;
}

double time_execution_seconds(const std::function<void()>& func)
{
    auto start = std::chrono::system_clock::now();
    func();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    return elapsed_seconds.count();
}