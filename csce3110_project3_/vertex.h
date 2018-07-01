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
  
  void print_adjacency_list();

  // GETTERS
  const map<char,int>& get_adj();
  const int&           get_indegree();
  const int&           get_dist();
  const char&          get_name();
  const char&          get_path();
  const bool&          get_is_known();
  
  // SETTERS
  void set_adj_vertex(char,int);
  void set_dist(int);
  void set_name(char);
  void set_path(char);
  void set_known(bool);
  void increment_indegree();

  void operator=(const Vertex&);
  Vertex* operator=(Vertex*);

private:

  map<char,int> adj;
  int           indegree;
  int           dist;
  char          name;
  char          path;
  bool          is_known;
};