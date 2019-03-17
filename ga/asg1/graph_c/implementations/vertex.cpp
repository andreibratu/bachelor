#include <algorithm>
#include "../interfaces/vertex_iterator.h"
#include "../interfaces/vertex.h"


template <class T>
Vertex<T>::Vertex(T label) {
  this->label = label;
}


template <class T>
void Vertex<T>::remove_inbound(T label) {
  auto it = std::find(this->inbound.begin(), this->inbound.end(), label);
  if(it != this->inbound.end()) {
    this->inbound.erase(it);
  }
}


template <class T>
void Vertex<T>::remove_outbound(T label) {
  auto it = std::find(this->outbound.begin(), this->outbound.end(), label);
  if(it != this->outbound.end()) {
    this->outbound.erase(it);
  }
}


template <class T>
int Vertex<T>::get_degree_in() const {
  return (int)this->inbound.size();
}


template <class T>
int Vertex<T>::get_degree_out() const {
  return (int)this->outbound.size();
}


template <class T>
bool Vertex<T>::add_inbound(T label) {
  auto it = std::find(this->inbound.begin(), this->inbound.end(), label);
  if(it == this->inbound.end()) {
    this->inbound.push_back(label);
    return true;
  }
  return false;
}


template <class T>
bool Vertex<T>::add_outbound(T label) {
  auto it = std::find(this->outbound.begin(), this->outbound.end(), label);
  if(it == this->outbound.end()) {
    this->outbound.push_back(label);
    return true;
  }
  return false;
};


template <class T>
VertexIterator<T> Vertex<T>::get_inbound_edges_iterator() const {
  return VertexIterator<T>(this->inbound);
}


template <class T>
VertexIterator<T> Vertex<T>::get_outbound_edges_iterator() const {
  return VertexIterator<T>(this->outbound);
}


template class Vertex<int>;
