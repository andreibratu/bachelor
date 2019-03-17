#include <utility>
#include <exception>
#include <algorithm>
#include "../interfaces/graph.h"
#include "../interfaces/vertex.h"
#include "../interfaces/iterator.h"


template <class T>
Graph<T>::Graph() {}


template <class T>
typename std::vector<Vertex<T>>::iterator Graph<T>::find_vertex(T label) {
  return std::find_if(
    this->vertices.begin(),
    this->vertices.end(),
    [&label](const Vertex<T>& v) {return v.label == label;}
  );
}


template <class T>
bool Graph<T>::is_edge(T out, T in) const {
  auto it_edge = this->edges.find({out, in});

  return it_edge != this->edges.end();
}


template <class T>
bool Graph<T>::add_vertex(T label) {
  auto it = this->find_vertex(label);

  if (it == this->vertices.end()) {
    this->vertices.push_back(Vertex<T>(label));
    return true;
  }
  else return false;
}


template <class T>
bool Graph<T>::remove_vertex(T label) {
  auto v_it = this->find_vertex(label);

  if(v_it == this->vertices.end())
    return false;

  this->vertices.erase(v_it);
  Iterator<Vertex<T>> it = this->get_graph_iterator();
  for(; it.valid() ; it.next()) {
    Vertex<T> v = it.getCurrent();
    v.remove_inbound(label);
    v.remove_outbound(label);
  }
  return true;
}


template <class T>
bool Graph<T>::add_edge(T out, T in) {
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


template <class T>
bool Graph<T>::remove_edge(T out, T in) {
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


template <class T>
int Graph<T>::size() {
  return (int)this->vertices.size();
}


template <class T>
Iterator<Vertex<T>> Graph<T>::get_graph_iterator() const {
  return Iterator<Vertex<T>>(this->vertices);
}


template <class T>
int Graph<T>::get_edge_property(T out, T in) {
  if(!this->is_edge(in, out)) {
    throw std::exception();
  }

  return this->edges[{out, in}];
}


template <class T>
void Graph<T>::set_edge_property(T out, T in, int val) {
  if(!this->is_edge(out, in)) {
    throw std::exception();
  }

  this->edges[{out, in}] = val;
}
