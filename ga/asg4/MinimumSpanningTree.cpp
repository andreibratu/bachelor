//
// Created by andreib on 23.05.2019.
//

#include "MinimumSpanningTree.h"

// Check if graph is undirected
bool undirected(Graph &graph)
{
    for(int i = 0; i < graph.size(); i++) for(int j = 0; j < graph.size(); j++)
    {
        if(graph.is_edge(i, j)) if(!graph.is_edge(j, i))
        {
            return false;
        }
    }

    return true;
}

// Check if the graph has vertices in domain 0..n-1
bool ordered(Graph &g)
{
    int n = g.size();
    Set vertices;
    for(int i = 0; i < n; i++) vertices.insert(i);
    auto it = g.get_graph_iterator();
    while(it.valid())
    {
        int v = it.getCurrent().label;
        if(vertices.find(v) != vertices.end())
        {
            vertices.erase(vertices.find(v));
        }
        it.next();
    }

    return vertices.empty();
}

// Add undirected edge to graph
void addUndirectedEdge(Graph &graph, int out, int in, int cost)
{
    graph.add_edge(out, in);
    graph.set_edge_property(out, in, cost);
    graph.add_edge(in, out);
    graph.set_edge_property(in, out, cost);
}

// Initialise Prim algorithm which starts from 0
void primMSTInit(Graph& g, Set &unused, Set &used, PQueue &pQueue)
{
    auto vertexIterator = g.get_graph_iterator();
    while(vertexIterator.valid())
    {
        int vertex = vertexIterator.getCurrent().label;
        if(vertex != 0)
        {
            unused.insert(vertex);
        }
        vertexIterator.next();
    }
    auto it = g.get_outbound_edges_it(0);
    while(it.valid())
    {
        int v = it.getCurrent();
        int cost = g.get_edge_property(0, v);
        pQueue.push({cost, {0, v}});
        it.next();
    }
    used.insert(0);
}

/**
 * Determine MST for given graph
 * Throws if given graph is directed
 */
Graph primMST(Graph& g)
{
    if(!undirected(g) || !ordered(g)) throw std::exception();
    Set used;
    Set unused;
    PQueue pQueue;
    Graph mst;
    for(int i = 0; i < g.size(); i++) mst.add_vertex(i);
    primMSTInit(g, unused, used, pQueue);

    while(!unused.empty())
    {
        int oldNode = pQueue.top().second.first;
        int newNode = pQueue.top().second.second;
        int cost = pQueue.top().first;
        pQueue.pop();

        if(used.find(newNode) != used.end()) continue;

        unused.erase(unused.find(newNode));
        used.insert(newNode);
        addUndirectedEdge(mst, oldNode, newNode, cost);

        auto outboundIterator = g.get_outbound_edges_it(newNode);
        while(outboundIterator.valid())
        {
            int neighbour = outboundIterator.getCurrent();
            if(used.find(neighbour) == used.end())
            {
                // Neighbour is not used
                int edgeCost = g.get_edge_property(newNode, neighbour);
                pQueue.push({edgeCost, {newNode, neighbour}});
            }
            outboundIterator.next();
        }
    }

    return mst;
}