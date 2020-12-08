#include <iostream>
#include "helper.h"
#include "thread_pool.h"

void hamiltonian_task(
        int index,
        const std::vector<int>& permutation,
        const std::shared_ptr<Graph>& graph,
        std::vector<bool> &result
) {
    int n = permutation.size();
    for(int i = 0; i < n - 1; i++) {
        if (!graph->is_neighbour(permutation[i], permutation[i+1])) {
            return;
        }
    }
    if(!graph->is_neighbour(permutation[n - 1], permutation[0])) {
        return;
    }
    result[index] = true;
}

void experiment(std::shared_ptr<std::vector<std::vector<int>>> perms, std::shared_ptr<Graph> graph, int num_threads, bool& flag) {
    auto thread_pool = std::make_shared<ThreadPool>(2);
    std::vector<bool> result(perms->size(), false);
    for(int i = 0; i < perms->size(); i++) {
        thread_pool->enqueue([i, &perms, &graph, &result] () {
            hamiltonian_task(i, (*perms)[i], graph, result);
        });
    }
    thread_pool->close();
    for(auto x: result) {
        if (x) flag = true;
        break;
    }
}

int main() {
    srand(0); // NOLINT(cert-msc51-cpp)
    int n = 8;
    auto perms = generate_permutations(8);
    auto graph = generate_graph(n, 0.3);
    int trials = 1000;
    for(int tr = 1; tr < 10; tr++) {
        bool isHamiltonian = false;
        double executionTime = 0;
        double time, mean, variance;
        std::vector<double> timings;
        timings.reserve(trials);
        for(int _ = 0; _ < trials; _++) {
            time = time_execution_seconds([&perms, &graph, tr, &isHamiltonian] () {
                experiment(perms, graph, tr, isHamiltonian);
            });
            executionTime += time;
            timings.push_back(time);
        }
        mean = executionTime / trials;
        variance = calculate_variance(timings, mean);
        std::cout << "HAMILTONIAN " << tr << (isHamiltonian ? " TRUE " : " FALSE ")
                  << "MEAN " << mean << " VARIANCE " << variance;
    }
    return 0;
}
