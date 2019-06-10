#include <iostream>

#include "../asg1/graph_c/interfaces/graph.h"
#include "MinCostWalk.h"

int main() {
    Graph g;
    for(int i = 0; i < 4; i++) {
        g.add_vertex(i);
    }
    g.add_edge(0, 0);
    g.set_edge_property(0, 0, 1);

    g.add_edge(0, 1);
    g.set_edge_property(0, 1, 7);

    g.add_edge(1, 2);
    g.set_edge_property(1, 2, 2);

    g.add_edge(2, 1);
    g.set_edge_property(2, 1, 6);

    g.add_edge(1, 3);
    g.set_edge_property(1, 3, 7);

    g.add_edge(2, 3);
    g.set_edge_property(2, 3, 4);

    std::pair<std::vector<int>, int> answer = matrixMultiplicationMinWalk(g, 0, 3);
    std::cout << answer.second << '\n';
    assert(answer.second == 13);
    for(auto x: answer.first) std::cout << x << ' ';
    std::cout << '\n';
    return 0;
}