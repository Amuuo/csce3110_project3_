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
#include<thread>
#include<vector>
#include<functional>
#include<queue>
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
  void twoPointPrintShortest(char,char);
  void printVertexesIndegree();
  void resetVertexes();
  void printTopologicalSort();
  void initStartVertex(char);
  bool empty();
  
  const int               inf = numeric_limits<int>::max();
  map<char,Vertex*>       vertexes{};
  //priority_queue<Vertex*,less<int>> dijkstraQueue{};
  Vertex*                 pathStart;
};



