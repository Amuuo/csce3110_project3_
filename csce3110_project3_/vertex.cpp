#include "vertex.h"

Vertex::Vertex() : 
  adj      {},                 
  indegree {},                                     
  dist     {numeric_limits<int>::max()},                 
  name     {},                   
  path     {},                    
  isKnown  {false} {}

Vertex::Vertex(char c) : 
  adj      {},                       
  indegree {},                       
  dist     {numeric_limits<int>::max()},                      
  name     {c},                        
  path     {},                       
  isKnown  {false} {}

Vertex::Vertex(const Vertex& v) {        
  adj      = v.adj;
  indegree = v.indegree;
  dist     = v.dist;
  name     = v.name;
  path     = v.path;
  isKnown  = v.isKnown;
}

Vertex::Vertex(Vertex&& v) {  
  adj      = move(v.adj);
  indegree = move(v.indegree);
  dist     = move(v.dist);
  name     = move(v.name);
  path     = move(v.path);
  isKnown  = move(v.isKnown);
}

// GETTERS
using map_ = map<char,int>;
const char Vertex::getName()     { return name;     }
const char Vertex::getPath()     { return path;     }
const bool Vertex::getIsKnown()  { return isKnown;  }
const map_ Vertex::getAdj()      { return adj;      }
const int  Vertex::getIndegree() { return indegree; }
const int  Vertex::getDist()     { return dist;     }

// SETTERS
void Vertex::setDist(int i)             { dist     = i; }
void Vertex::setName(char c)            { name     = c; }
void Vertex::setPath(char v)            { path     = v; }
void Vertex::setKnown(bool b)           { isKnown  = b; }
void Vertex::setIndegree(int i)         { indegree = i; }
void Vertex::setAdjVertex(char n,int d) { adj[n]   = d; }
void Vertex::incrementIndegree()        { indegree++  ; }

void Vertex::decrementIndegree() {
  --indegree;
}

void Vertex::operator=(const Vertex & v) {
  adj      = v.adj;
  indegree = v.indegree;
  dist     = v.dist;
  name     = v.name;
  path     = v.path;
  isKnown  = v.isKnown;
}

Vertex* Vertex::operator=(Vertex* v) {
  return v; 
}

bool Vertex::operator>( Vertex *v2) const {
  
  return dist > v2->getDist();
}

bool Vertex::operator<( Vertex * v1) const {
  return dist < v1->getDist();
}

bool Vertex::operator<( Vertex v) const {
  return dist < v.getDist();
}

bool Vertex::operator>( Vertex v) const {
  return dist > v.getDist();
}

void Vertex::printAdjacencyList() {
  for (auto& adj_vertex : adj)
    printf("->[%c,%d]",adj_vertex.first,adj_vertex.second);
}

