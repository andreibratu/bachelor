#include <iostream>
#include "../asg1/graph_c/interfaces/graph.h"
#include "MinimumSpanningTree.h"

int main()
{
    Graph g;
    for(int i = 0; i < 9; i++)
    {
        g.add_vertex(i);
    }
    addUndirectedEdge(g, 0, 1, 4);
    addUndirectedEdge(g, 0, 7, 8);
    addUndirectedEdge(g, 1, 7, 11);
    addUndirectedEdge(g, 1, 2, 8);
    addUndirectedEdge(g, 7, 8, 7);
    addUndirectedEdge(g, 7, 6, 1);
    addUndirectedEdge(g, 2, 8, 2);
    addUndirectedEdge(g, 8, 6, 6);
    addUndirectedEdge(g, 6, 5, 2);
    addUndirectedEdge(g, 2, 5, 4);
    addUndirectedEdge(g, 2, 3, 7);
    addUndirectedEdge(g, 6, 5, 2);
    addUndirectedEdge(g, 3, 5, 14);
    addUndirectedEdge(g, 5, 4, 10);
    addUndirectedEdge(g, 3, 4, 9);

    Graph mst = primMST(g);
    assert(mst.is_edge(0, 1));
    assert(mst.is_edge(0, 7));
    assert(mst.is_edge(7, 6));
    assert(mst.is_edge(6, 5));
    assert(mst.is_edge(2, 5));
    assert(mst.is_edge(2, 8));
    assert(mst.is_edge(2, 3));
    assert(mst.is_edge(3, 4));
    assert(!mst.is_edge(1, 2));
    assert(!mst.is_edge(5, 4));
    assert(!mst.is_edge(3, 5));
    assert(!mst.is_edge(1, 2));
    assert(!mst.is_edge(1, 2));
    assert(!mst.is_edge(7, 8));
}