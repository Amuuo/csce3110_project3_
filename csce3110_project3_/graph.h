#pragma once
#include<iostream>
#include<map>
#include<utility>
#include<fstream>
#include<sstream>
#include<string>
#include<stack>
#include<deque>
#include<set>
#include<algorithm>
#include"vertex.h"
using namespace std;

class Graph {

public:

  Graph();
  Graph(const Graph&);
  Graph(Graph&&);
  void insert_vertex(Vertex&&);
  void print_vertexes();
  void update_vertex_parameters();
  void print_vertex_parameters();
  void input_graph_data();
  void calculate_shortest_paths(char,int=0);
  void print_shortest_paths(char);
  void print_vertexes_indegree();
  void reset_vertexes();
  const int inf = numeric_limits<int>::max();
  bool empty();
  map<char,Vertex*> vertexes{};
  deque<Vertex*> dijkstra_queue{};
  Vertex* source;
  bool source_set;
};



