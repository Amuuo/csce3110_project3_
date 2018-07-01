#include "vertex.h"

Vertex::Vertex() {}
Vertex::Vertex(char c) : name{c} {}
char Vertex::get_name() {
  
  return name;
}
char Vertex::get_path() {
  return path;
}
bool Vertex::get_known() {
  return known;
}
map<char, int> Vertex::get_adj() {
  return adj;
}
void Vertex::set_adj(char c, int i) {
  adj[c] = i;
}
void Vertex::increment_indegree() {
  indegree++;
}
void Vertex::insert_neighbor(char name,int distance) {
  adj[name]=distance;
}
void Vertex::print_adjacency_list() {
  for (auto& adj_vertex : adj) {
      printf("->{%c,%d}",adj_vertex.first,adj_vertex.second);
    }
}

int Vertex::get_indegree() {
  return indegree;
}

int Vertex::get_dist() {
  return dist;
}
