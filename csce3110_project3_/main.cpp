#pragma once
#include "graph.h"

void print_menu(Graph& graph, const char* s="") {
  int menu_choice;
  printf("\n\n\t1 - Load Graph Data from File");
  printf("\n\t2 - Print Vertex Details");
  printf("\n\t3 - Print Single-Source Shortest Paths");
  printf("\n\t4 - Print Adjacency List");
  printf("\n\t5 - Print Indegree of Each Vertex");
  printf("\n\t6 - Exit");

  if (s != "") printf("\n\n\t>> %s",s);

  printf("\n\n\tSelection: "); cin >> menu_choice;
  
  switch (menu_choice) {
    
    case 1:
      graph.input_graph_data();      
      graph.update_vertex_parameters();
      print_menu(graph, "Graph info loaded into graph");
      break;
    
    case 2: 
      graph.print_vertex_parameters(); 
      print_menu(graph,"Printed Vertex Parameters.");
      break;
    
    case 3:{
      char name;       
      insert_vertex:
      cout << "\n\tInsert Source Vertex: "; cin >> name; 
      graph.source = graph.vertexes[name];
      try {
        graph.calculate_shortest_paths(graph.source->get_name());                
        graph.print_shortest_paths(graph.source->get_name());
      }
      catch(exception& e){
        cout << "\n\tThat vertex doesn't exist (" << e.what() << ")";
        goto insert_vertex;
      }
      print_menu(graph,"Shortest Paths Printed");
      break;
    }
    
    case 4: 
      graph.print_vertexes(); 
      print_menu(graph,"Adjacency list printed."); 
      break;
    
    case 5: 
      graph.print_vertexes_indegree();
      print_menu(graph, "Vertex Indegree Printed.");
      break;
    
    case 6: 
      exit(1); 
      break;
    
    default: break;
  }
}

int main() {

  Graph graph{};
  print_menu(graph);  
  return 0;
}

