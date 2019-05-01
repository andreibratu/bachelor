//
// Created by andreib on 26.04.2019.
//


#include <limits.h>
#include <vector>
#include <iostream>
#include "MinCostWalk.h"


int dp_min_walk(Graph& g, int source, int destination) {
    int n = g.size();
    #define MAX_WALK_LENGTH (n*n+1)
    #define NODES (n)
    #define INF (INT_MAX)
    std::vector<std::vector<int>> w(MAX_WALK_LENGTH, std::vector<int>(NODES, INF));
    w[0][source] = 0;

    for(int k=1; k < MAX_WALK_LENGTH; k++) {
        for(int x = 0; x < NODES; x++) {
            for(auto it = g.get_inbound_edges_it(x) ; it.valid(); it.next()) {
                int y = it.getCurrent();
                if(w[k-1][y] == INF) continue;

                int cost = g.get_edge_property(y, x);
                w[k][x] = std::min(w[k-1][x], w[k-1][y] + cost);
            }
        }
    }

    int best = INF;
    for(int i = 0; i < MAX_WALK_LENGTH; i++) best = std::min(best, w[i][destination]);

    if(best == INF) return -1;

    return best;
}
