#pragma once
#include<map>
using namespace std;

class Vertex {

public:

  Vertex();
  Vertex(char);
  void insert_neighbor(char,int);
  void print_adjacency_list();
  int get_indegree();
  int get_dist();
  char get_name();
  char get_path();
  bool get_known();
  map<char,int> get_adj();
  void set_adj(char,int);
  void increment_indegree();

private:

  map<char,int> adj{};
  int           indegree{};
  int           dist{};
  char          name{};
  char          path{};
  bool          known{};
};