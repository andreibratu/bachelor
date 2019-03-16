#include <utility>
#include <exception>
#include <algorithm>
#include "../interfaces/graph.h"
#include "../interfaces/vertex.h"
#include "../interfaces/graph_iterator.h"


bool Graph::is_edge(int in, int out) const {
  auto it_edge = this->edges.find(std::make_pair(in, out));

  return it_edge != this->edges.end();
}


Graph::Graph() {}


bool Graph::add_vertex(int label) {
  auto it = std::find_if(
    this->vertices.begin(),
    this->vertices.end(),
    [&label](const Vertex& v) {return v.label == label;}
  );

  if (it == this->vertices.end()) {
    this->vertices.push_back(Vertex(label));
    return true;
  }
  else return false;
}


bool Graph::remove_vertex(int label) {
  auto v_it = std::find_if(
    this->vertices.begin(),
    this->vertices.end(),
    [&label](const Vertex& v) {return v.label == label;}
  );
  if (v_it != this->vertices.end()) {
    this->vertices.erase(v_it);
    GraphIterator it = this->get_graph_iterator();
    for(; it.valid() ; it.getCurrent()) {
      Vertex v = it.getCurrent();
      v.remove_inbound(label);
      v.remove_outbound(label);
    }
    return true;
  }
  else return false;
}


bool Graph::add_edge(int out, int in) {
  if(this->is_edge(in, out))
    return false;

  auto it_v_in = std::find_if(
    this->vertices.begin(),
    this->vertices.end(),
    [&in](const Vertex& v) {return v.label == in;}
  );
  auto it_v_out = std::find_if(
    this->vertices.begin(),
    this->vertices.end(),
    [&out](const Vertex& v) {return v.label == out;}
  );

  if(it_v_in == this->vertices.end() || it_v_out == this->vertices.end())
    return false;

  this->edges.insert(std::make_pair(in, out));
  *it_v_in->add_outbound(out);
  *it_v_out->add_inbound(in);
  return true;
}


bool Graph::remove_edge(int in, int out) {
  if(!this->is_edge(in, out))
    return false;

  auto it_v_in = std::find_if(
    this->vertices.begin(),
    this->vertices.end(),
    [&in](const Vertex& v) {return v.label == in;}
  );

  auto it_v_in = std::find_if(
    this->vertices.begin(),
    this->vertices.end(),
    [&out](const Vertex& v) {return v.label == out;}
  );

  auto it_edge = find(
    this->edges.begin(),
    this->edges.end(),
    std::make_pair(in, out)
  );
  this->edges.erase(it_edge);

  *it_v_in->remove_outbound(out);
  *it_v_out->remove_inbound(in);
  return true;
}


int Graph::size() {
  return (int)this->vertices.size();
}


GraphIterator get_graph_iterator() {
  return GraphIterator(this->vertices);
}


int get_edge_property(int in, int out) {
  if(!this->is_edge(in, out)) {
    throw std::exception();
  }

  return this->edges[make_pair(in, out)];
}


void set_edge_property(int in, int out, int val) {
  if(!this->is_edge(in, out)) {
    throw std::exception();
  }

  this->edges[make_pair(in, out)] = val;
};
