//
// Created by Andrei Bratu on 08.12.2020.
//

#ifndef LAB6_GRAPH_H
#define LAB6_GRAPH_H

#include <algorithm>
#include <unordered_map>
#include <unordered_set>

class Graph {
private:
    int n;
    std::unordered_map<int, std::unique_ptr<std::unordered_set<int>>> edges;
public:
    Graph(int n) {
        assert(n >= 1);
        this->n = n;
        for(int i = 0; i < n; i++) {
            edges[i] = std::make_unique<std::unordered_set<int>>();
        }
    }

    void add_edge(int start, int end) {
        edges[start]->insert(end);
    }

    std::unordered_set<int>* get_neighbours(int node) {
        return this->edges[node].get();
    }

    bool is_neighbour(int node, int neighbour) {
        return this->edges[node]->find(neighbour) != this->edges[node]->end();
    }
};

#endif //LAB6_GRAPH_H
