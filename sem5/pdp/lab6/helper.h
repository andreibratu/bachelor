//
// Created by Andrei Bratu on 08.12.2020.
//

#ifndef LAB6_HELPER_H
#define LAB6_HELPER_H

#include <vector>
#include <chrono>
#include "graph.h"

float generate_random() {
     return static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // NOLINT(cert-msc50-cpp)
}

std::shared_ptr<std::vector<std::vector<int>>> generate_permutations(int n) {
    auto result = std::make_shared<std::vector<std::vector<int>>>();
    std::vector<int> permutation(n, 0);
    for(int i = 0; i < n; i++) {
        permutation[i] = i;
    }
    result->push_back(permutation);
    while(next_permutation(permutation.begin(), permutation.end())) {
        result->push_back(permutation);
    }
    return result;
}

std::shared_ptr<Graph> generate_graph(int n, float edge_bound) {
    auto graph = std::make_shared<Graph>(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (i == j) continue;
            if (generate_random() < edge_bound) {
                graph->add_edge(i, j);
            }
        }
    }
    return graph;
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

double calculate_variance(const std::vector<double>& samples, double mean) {
    double variance = 0;
    for(auto& x : samples) {
        variance += (x - mean) * (x - mean);
    }
    return variance / (samples.size() - 1); // NOLINT(cppcoreguidelines-narrowing-conversions)
}

void print_hamiltonian_path(const std::vector<int> &permutation) {
    std::cout << "HAMILTONIAN PATH ";
    for(auto& x: permutation) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

#endif //LAB6_HELPER_H
