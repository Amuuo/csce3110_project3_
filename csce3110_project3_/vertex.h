#pragma once
#include<map>
#include<limits>
using namespace std;

class Vertex {

public:

  Vertex();
  Vertex(char);
  Vertex(const Vertex&);
  Vertex(Vertex&&);
  
  void printAdjacencyList();

  /* GETTERS */
  const map<char,int>& getAdj();
  const int&  getIndegree();
  const int&  getDist();
  const char& getName();
  const char& getPath();
  const bool& getIsKnown();
  
  /* SETTERS */
  void setAdjVertex(char,int);
  void setDist(int);
  void setName(char);
  void setPath(char);
  void setKnown(bool);
  void setIndegree(int);
  void incrementIndegree();

  void operator=(const Vertex&);
  Vertex* operator=(Vertex*);

private:

  map<char,int> adj;
  int   indegree;
  int   dist;
  char  name;
  char  path;
  bool  isKnown;
};