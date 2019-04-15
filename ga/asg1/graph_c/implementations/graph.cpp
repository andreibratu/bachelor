#include <utility>
#include <exception>
#include <algorithm>
#include "../interfaces/graph.h"
#include "../interfaces/vertex.h"
#include "../interfaces/iterator.h"


Graph::Graph() {}


Graph::Graph(const Graph& g) {
  for(auto x:g.vertices) {
    this->vertices.push_back(Vertex(x));
  }
  this->edges = std::unordered_map<Edge, int, boost::hash<Edge>>(g.edges);
}


Graph& Graph::operator = (const Graph& g) {
  for(auto x:g.vertices) {
    this->vertices.push_back(Vertex(x));
  }
  this->edges = std::unordered_map<Edge, int, boost::hash<Edge>>(g.edges);

  return *this;
}


std::vector<Vertex>::iterator Graph::find_vertex(int label) {
  return std::find_if(
    this->vertices.begin(),
    this->vertices.end(),
    [&label](const Vertex& v) {return v.label == label;}
  );
}


bool Graph::is_edge(int out, int in) const {
  auto it_edge = this->edges.find({out, in});

  return it_edge != this->edges.end();
}


bool Graph::add_vertex(int label) {
  auto it = this->find_vertex(label);

  if(it != this->vertices.end()) {
    return false;
  }

  Vertex v{label};
  this->vertices.push_back(v);
  return true;
}


bool Graph::remove_vertex(int label) {
  auto v_it = this->find_vertex(label);

  if(v_it == this->vertices.end())
    return false;

  // Remove the vertex
  this->vertices.erase(v_it);

  // Remove vertex's edges
  Iterator<Vertex> it = this->get_graph_iterator();
  for(it.first(); it.valid() ; it.next()) {
    Vertex v = it.getCurrent();
    v.remove_inbound(label);
    v.remove_outbound(label);
  }

  // Decrement all larger vertices
  for(auto& x: this->vertices) {
    if(x.label > label) x.label -= 1;
  }

  // Update edges with the new vertices
  std::unordered_map<Edge, int, boost::hash<Edge>> new_edges;
  for(auto e: this->edges) {
    auto key = e.first;
    auto val = e.second;
    if(key.first > label) key.first -= 1;
    if(key.second > label) key.second -= 1;
    new_edges[key] = val;
  }
  this->edges = new_edges;

  return true;
}


bool Graph::add_edge(int out, int in) {
  if(this->is_edge(out, in))
    return false;

  auto it_v_in = this->find_vertex(in);
  auto it_v_out = this->find_vertex(out);

  if(it_v_in == this->vertices.end() || it_v_out == this->vertices.end())
    return false;

  this->edges[{out, in}] = 0;
  it_v_in->add_inbound(out);
  it_v_out->add_outbound(in);
  return true;
}


bool Graph::remove_edge(int out, int in) {
  if(!this->is_edge(out, in))
    return false;

  auto it_v_out = this->find_vertex(out);
  auto it_v_in = this->find_vertex(in);

  auto it_edge = this->edges.find({out, in});
  this->edges.erase(it_edge);

  it_v_in->remove_inbound(out);
  it_v_out->remove_outbound(in);
  return true;
}


int Graph::size() const {
  return (int)this->vertices.size();
}


Iterator<Vertex> Graph::get_graph_iterator() const {
  return Iterator<Vertex>(this->vertices);
}


int Graph::get_edge_property(int out, int in) {
  if(!this->is_edge(in, out)) {
    throw std::exception();
  }

  return this->edges[{out, in}];
}


void Graph::set_edge_property(int out, int in, int val) {
  if(!this->is_edge(out, in)) {
    throw std::exception();
  }

  this->edges[{out, in}] = val;
}


Iterator<int> Graph::get_outbound_edges_it(int label) {
  auto it = this->find_vertex(label);

  if(it == this->vertices.end())
    throw std::exception();

  return it->get_outbound_edges_iterator();
}


Iterator<int> Graph::get_inbound_edges_it(int label) {
  auto it = this->find_vertex(label);

  if(it == this->vertices.end())
    throw std::exception();

  return it->get_inbound_edges_iterator();
}
