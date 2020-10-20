#include <iostream>
#include <vector>
#include <cassert>
#include <thread>
#include "Queue.hpp"
#include "util.hpp"

void produce(Queue<double>& queue, const std::vector<double>& vec_one, const std::vector<double>& vec_two)
{
    assert(vec_one.size() == vec_two.size());
    int n = vec_one.size();
    for (int i = 0; i < n; i++)
    {
        const double prod = vec_one[i] * vec_two[i];
        while(!queue.offer(prod));
    }
    while(!queue.offer(std::numeric_limits<double>::infinity()));
}

void consume(Queue<double>& queue)
{
    double sum = 0;
    while(true)
    {
        double value = queue.take();
        if (value == std::numeric_limits<double>::infinity())
        {
            break;
        }
        sum += value;
    }
    std::cout << "SMART PRODUCT " << sum << '\n';
}

void smart_product(Queue<double> &buffer, std::vector<double> &one, std::vector<double> &two)
{
    std::thread first([&](){produce(buffer, one, two);});
    std::thread second([&buffer](){consume(buffer);});
    first.join();
    second.join();
}

void dumb_product(std::vector<double> &one, std::vector<double> &two)
{
    assert(one.size() == two.size());
    double product = 0;
    for(int i = 0; i < one.size(); i++)
    {
        product += one[i] * two[i];
    }
    std::cout << "DUMB PRODUCT " << product << '\n';
}

int main()
{
    auto buffer = Queue<double>(100);
    std::vector<double> vec_one = make_random_vector(1000000);
    std::vector<double> vec_two = make_random_vector(1000000);

    std::cout << time_execution_seconds(
            [&vec_one, &vec_two]()
            {
                dumb_product(vec_one, vec_two);
            }) << '\n';
    std::cout << time_execution_seconds(
            [&vec_one, &vec_two, &buffer](){
                smart_product(buffer, vec_one, vec_two);
            }) << '\n';
    return 0;
}
