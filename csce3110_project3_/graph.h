#pragma once
#include<iostream>
#include<map>
#include<utility>
#include<fstream>
#include<sstream>
#include<string>
#include<stack>
#include<deque>
#include<algorithm>
#include"vertex.h"
using namespace std;

class Graph {

public:

  Graph();
  Graph(const Graph&);
  Graph(Graph&&);
  void insertVertex(Vertex&&);
  void printVertexes();
  void updateVertexParameters();
  void printVertexParameters();
  void inputGraphData();
  void calculateShortestPaths(char,int=0);
  void printShortestPaths(char);
  void printVertexesIndegree();
  void resetVertexes();
  const int inf = numeric_limits<int>::max();
  bool empty();
  map<char,Vertex*> vertexes{};
  deque<Vertex*> dijkstraQueue{};
  Vertex* pathStart;
};



