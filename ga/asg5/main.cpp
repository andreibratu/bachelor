#include <iostream>
#include "../asg1/graph_c/interfaces/graph.h"
#include "HamiltonianCycle.h"

int main() {
    Graph g;

    for(int i = 0; i < 5; i++)
    {
        g.add_vertex(i);
    }

    g.add_edge(0, 1);
    g.set_edge_property(0, 1, 9);

    g.add_edge(0, 3);
    g.set_edge_property(0, 3, 8);

    g.add_edge(1, 0);
    g.set_edge_property(1, 0, 7);

    g.add_edge(1, 2);
    g.set_edge_property(1, 2, 1);

    g.add_edge(1, 4);
    g.set_edge_property(1, 4, 3);

    g.add_edge(2, 0);
    g.set_edge_property(2, 0, 5);

    g.add_edge(2, 4);
    g.set_edge_property(2, 4, 4);

    g.add_edge(3, 2);
    g.set_edge_property(3, 2, 6);

    g.add_edge(4, 3);
    g.set_edge_property(4, 3, 7);

    g.add_edge(4, 1);
    g.set_edge_property(4, 1, 1);

    auto ans = minimumHamiltonianCycle(g);
    assert(ans.second == 26);
    std::cout << ans.second << '\n';
    for(auto x : ans.first)
    {
        std::cout << x << ' ';
    }
    std::cout << '\n';
    return 0;
}