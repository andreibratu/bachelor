#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <unordered_map>
#include <boost/functional/hash.hpp>
#include "vertex.h"
#include "iterator.h"


class Graph {
private:
  typedef std::pair<int, int> Edge;
  std::vector<Vertex> vertices;
  std::unordered_map<Edge, int, boost::hash<Edge>> edges;
  std::vector<Vertex>::iterator find_vertex(int);
public:
  // Graph constructor
  Graph();

  Graph(const Graph&);

  Graph& operator = (const Graph&);

  /**
    Check if given edge exists.

    @param 'out' Outbound vertex label
    @param 'in' Inbound vertex label.
    @return Edge exists.
  */
  bool is_edge(int out, int in) const;

  /**
    Add new vertex into graph.

    @param `label` Label of the new vertex.
    @return Vertex label was not used already and new vertex was added.
  */
  bool add_vertex(int label);


  /**
    Remove vertex from graph.

    @param `label` Label of the vertex to be removed.
    @return Vertex existed and it was removed.
  */
  bool remove_vertex(int label);


  /**
    Add edge into graph.

    @param `out` Label of the outbound vertex.
    @param `in` Label of the inbound vertex.
    @return Edge did not exist already and it was added.
  */
  bool add_edge(int out, int in);


  /**
    Remove edge from graph.

    @param `out` Label of the outbound vertex.
    @param `in` Label of the inbound vertex.
    @return Edge was present and it was removed.
  */
  bool remove_edge(int out, int in);


  /**
    Get iterator over the outbound edges of given vertex.

    @param `label` Label of the inquired vertex.
    @return Iterator.
    @throw Vertex with given label does not exist.
  */
  Iterator<int> get_outbound_edges_it(int label);


  /**
    Get iterator over the inbound edges of given vertex.

    @param `label` Label of the inquired vertex.
    @return Iterator
    @throw Vertex with given label does not exist.
  */
  Iterator<int> get_inbound_edges_it(int label);


  /**
    Number of vertices in the graph.

    @return Number of vertices
  */
  int size() const;


  /**
    Get iterator over graph's vertices.

    @return Iterator.
  */
  Iterator<Vertex> get_graph_iterator() const;


  /**
    Get the associated property of an edge.

    @param `out` Label of the outbound vertex.
    @param `in` Label of the inbound vertex.
    @return Property
    @throw Edge does not exist
  */
  int get_edge_property(int out, int in);

  /**
    Set associated property of an edge.

    @param `out` Label of the outbound vertex.
    @param `in` Label of the inbound vertex.
    @param 'val' Value of the edge.
    @return Property
    @throw Edge does not exist
  */
  void set_edge_property(int out, int in, int val);
};

#endif
