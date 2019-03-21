#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "iterator.h"


class Vertex {
private:
  std::vector<int> inbound;
  std::vector<int> outbound;
public:
  int label;

  /**
    Vertex constructor.

    @param: `label` Label to assign to the vertex.
  */
  Vertex(int label);


  // @return: How many inbound edges.
  int get_degree_in() const;


  // @return: How many outbound edges.
  int get_degree_out() const;


  /**
    Add inbound vertex neighbour.

    @param: `label` Label of the vertex
    @return: Neigbour did not exist and was added.
  */
  bool add_inbound(int label);


  /**
    Add outbound vertex neighbour.

    @param: `label` Label of the vertex.
    @return: Neigbour did not exist and was added.
  */
  bool add_outbound(int);


  // @return: Iterator over inbound neighbours.
  Iterator<int> get_inbound_edges_iterator() const;


  // @return: Iterator over outbound neighbours.
  Iterator<int> get_outbound_edges_iterator() const;


  /**
    Remove inbound neighbour.

    @param: `label` Label of inbound neighbour to be removed.
  */
  void remove_inbound(int label);


  /**
    Remove inbound neighbour.

    @param: `label` Label of outbound neighbour to be removed.
  */
  void remove_outbound(int label);
};

#endif
