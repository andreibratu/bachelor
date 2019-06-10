//
// Created by andreib on 23.05.2019.
//

#ifndef ASG4_MINIMUMSPANNINGTREE_H
#define ASG4_MINIMUMSPANNINGTREE_H

#include <unordered_set>
#include <queue>
#include "../asg1/graph_c/interfaces/graph.h"

typedef std::pair<int, std::pair<int, int>> Edge;
typedef std::unordered_set<int> Set;
typedef std::priority_queue<Edge, std::vector<Edge>, std::greater<>> PQueue;

Graph primMST(Graph& g);

void addUndirectedEdge(Graph &graph, int out, int in, int cost);

#endif //ASG4_MINIMUMSPANNINGTREE_H
