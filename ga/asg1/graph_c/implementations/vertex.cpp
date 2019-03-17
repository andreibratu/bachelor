#include <algorithm>
#include "../interfaces/vertex_iterator.h"
#include "../interfaces/vertex.h"

Vertex::Vertex(int label) {
  this->label = label;
}

void Vertex::remove_inbound(int label) {
  auto it = std::find(this->inbound.begin(), this->inbound.end(), label);
  if(it != this->inbound.end()) {
    this->inbound.erase(it);
  }
}

void Vertex::remove_outbound(int label) {
  auto it = std::find(this->outbound.begin(), this->outbound.end(), label);
  if(it != this->outbound.end()) {
    this->outbound.erase(it);
  }
}

int Vertex::get_degree_in() const {
  return (int)this->inbound.size();
}

int Vertex::get_degree_out() const {
  return (int)this->outbound.size();
}

bool Vertex::add_inbound(int id) {
  auto it = std::find(this->inbound.begin(), this->inbound.end(), label);
  if(it == this->inbound.end()) {
    this->inbound.push_back(id);
    return true;
  }
  return false;
}

bool Vertex::add_outbound(int id) {
  auto it = std::find(this->outbound.begin(), this->outbound.end(), label);
  if(it == this->outbound.end()) {
    this->outbound.push_back(id);
    return true;
  }
  return false;
};

VertexIterator Vertex::get_inbound_edges_iterator() const {
  return VertexIterator(this->inbound);
}

VertexIterator Vertex::get_outbound_edges_iterator() const {
  return VertexIterator(this->outbound);
}
