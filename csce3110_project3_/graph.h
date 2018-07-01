#pragma once
#include<iostream>
#include<map>
#include<utility>
#include<fstream>
#include<sstream>
#include<string>
#include"vertex.h"
using namespace std;

class Graph {

public:

  Graph();
  Graph(const Graph&);
  Graph(Graph&&);
  void insert_vertex(Vertex);
  void print_vertexes();
  void update_vertex_parameters();
  void print_vertex_parameters();
  void input_graph_data();
  bool empty();
  map<char,Vertex> vertexes{};
};



