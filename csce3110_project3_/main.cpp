#pragma once
#include "graph.h"

int main() {

  Graph graph{};
  graph.input_graph_data();
  graph.update_vertex_parameters();
  graph.print_vertexes();
  graph.print_vertex_parameters();
  graph.calculate_shortest_paths('A');
  return 0;
}

