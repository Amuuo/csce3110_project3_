#include "vertex.h"

Vertex::Vertex() : 
  adj      {},                 
  indegree {},                                     
  dist     {numeric_limits<int>::max()},                 
  name     {},                   
  path     {},                    
  is_known {false} {}

Vertex::Vertex(char c) : 
  adj      {},                       
  indegree {},                       
  dist     {numeric_limits<int>::max()},                      
  name     {c},                        
  path     {},                       
  is_known {false} {}

Vertex::Vertex(const Vertex& v) {
  for (auto v : v.adj) {
    adj[v.first] = v.second;
  }
  adj      = v.adj;
  indegree = v.indegree;
  dist     = v.dist;
  name     = v.name;
  path     = v.path;
  is_known = v.is_known;
}

Vertex::Vertex(Vertex&& v) {  
  for (auto& v : v.adj) {
    adj[move(v.first)] = move(v.second);
  }
  indegree = move(v.indegree);
  dist     = move(v.dist);
  name     = move(v.name);
  path     = move(v.path);
  is_known = move(v.is_known);
}
/*void Vertex::operator=(const Vertex&& v) {
  adj      = move(v.adj);
  indegree = move(v.indegree);
  dist     = move(v.dist);
  name     = move(v.name);
  path     = move(v.path);
  is_known = move(v.is_known);
} */

// GETTERS
using map_ = map<char,int>;
const char& Vertex::get_name()     { return name;     }
const char& Vertex::get_path()     { return path;     }
const bool& Vertex::get_is_known() { return is_known; }
const map_& Vertex::get_adj()      { return adj;      }
const int & Vertex::get_indegree() { return indegree; }
const int & Vertex::get_dist()     { return dist;     }

// SETTERS
void Vertex::set_dist(int i)              { dist     = i; }
void Vertex::set_name(char c)             { name     = c; }
void Vertex::set_path(char v)             { path     = v; }
void Vertex::set_known(bool b)            { is_known = b; }
void Vertex::set_adj_vertex(char n,int d) { adj[n]   = d; }
void Vertex::increment_indegree()         { indegree++  ; }

void Vertex::operator=(const Vertex & v) {
  adj      = v.adj;
  indegree = v.indegree;
  dist     = v.dist;
  name     = v.name;
  path     = v.path;
  is_known = v.is_known;
}

Vertex* Vertex::operator=(Vertex* v) {
  return v; 
}

void Vertex::print_adjacency_list() {
  for (auto& adj_vertex : adj)
    printf("->{%c,%d}",adj_vertex.first,adj_vertex.second);
}

