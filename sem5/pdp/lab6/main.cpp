#include <iostream>
#include "helper.h"
#include "thread_pool.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

std::atomic<int> count(0);
int trials = 10;

void hamiltonian_task(
        const std::vector<int>& permutation,
        const std::shared_ptr<Graph>& graph,
        std::atomic<bool> &foundFlag
) {
    count++;
    if (count % 1000 == 0)
        std::cout << count << '\n';
    int n = permutation.size();
    for(int i = 0; i < n - 1; i++) {
        if (!graph->is_neighbour(permutation[i], permutation[i+1])) {
            return;
        }
    }
    if(!graph->is_neighbour(permutation[n - 1], permutation[0])) {
        return;
    }
    print_hamiltonian_path(permutation);
    foundFlag = true;
}

void experiment(
        std::shared_ptr<std::vector<std::vector<int>>> perms,
        std::shared_ptr<Graph> graph,
        int num_threads, int trial_c,
        std::atomic<bool> &foundFlag
) {
    std::cout << "EXPERIMENT " << num_threads << ' ' << trial_c << "/ " << trials << '\n';
    count = 0;
    sleep(2);
    auto thread_pool = std::make_shared<ThreadPool>(num_threads);
    for(int i = 0; i < perms->size(); i++) {
        if (foundFlag) break;
        thread_pool->enqueue([i, &perms, &graph, &foundFlag] () {
            hamiltonian_task((*perms)[i], graph, foundFlag);
        });
    }
    thread_pool->close();
}

int main() {
    srand(0); // NOLINT(cert-msc51-cpp)
    int n = 8;
    auto perms = generate_permutations(n);
    std::cout << "TOTAL " << perms->size() << '\n';
    auto graph = generate_graph(n, 0.15);
    graph->printGraph();
    sleep(5);
    for(int tr = 1; tr <= 10; tr++) {

        std::atomic<bool> isHamiltonian(false);
        double executionTime = 0;
        double time, mean, variance;
        std::vector<double> timings;
        timings.reserve(trials);
        for(int trial_c = 0; trial_c < trials; trial_c++) {
            time = time_execution_seconds([&perms, &graph, tr, trial_c, &isHamiltonian] () {
                experiment(perms, graph, tr, trial_c, isHamiltonian);
            });
            executionTime += time;
            timings.push_back(time);
        }
        mean = executionTime / trials;
        variance = calculate_variance(timings, mean);
        std::cout << "HAMILTONIAN " << tr << (isHamiltonian ? " TRUE " : " FALSE ")
                  << "MEAN " << mean << " VARIANCE " << variance << '\n';
    }
    return 0;
}
