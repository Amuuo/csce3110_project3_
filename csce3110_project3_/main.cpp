#pragma once
#include "graph.h"

void print_menu(Graph& graph, const char* s="") {
  int menu_choice;
  printf("\n\n\t1 - Load Graph Data from File");
  printf("\n\t2 - Print Vertex Details");
  printf("\n\t3 - Print Single-Source Shortest Paths");
  printf("\n\t4 - Print Adjacency List");
  printf("\n\t5 - Print Indegree of Each Vertex");
  printf("\n\t6 - Print Topological Sort of Graph");
  printf("\n\t7 - Exit");

  if (s != "") printf("\n\n\t>> %s",s);

  printf("\n\n\tSelection: "); cin >> menu_choice;
  
  system("clear");

  switch (menu_choice) {
    
    case 1:      
      graph.vertexes.clear();
      graph.inputGraphData();      
      graph.updateVertexParameters();
      print_menu(graph);
      break;
    
    case 2:       
      graph.printVertexParameters(); 
      print_menu(graph);
      break;
    
    case 3:{
      char name; // char to store vertex name

      /* print all available vertexes to choose from */
      input_check:
      printf("\n\tAvailable Vertexes: ");
      for (auto& v : graph.vertexes) {
        printf("%c%c ",v.first, 
                ++graph.vertexes.find(v.first)!=graph.vertexes.end()?',':'\n');
      }
      /* check for vertex input errors and repeat if necessary */
      printf("\n\tInsert Starting Vertex: "); cin >> name;             
      if(graph.vertexes.find(name) == graph.vertexes.end()){
        system("clear");
        printf("\n\tThat vertex doesn't exist...\n");                
        goto input_check;
      }
      
      
      graph.pathStart = graph.vertexes[name];
      graph.pathStart->setKnown(true);
      graph.pathStart->setPath(name);
      graph.pathStart->setDist(0);
      graph.calculateShortestPaths(graph.pathStart->getName());                
      graph.printShortestPaths(graph.pathStart->getName());
      print_menu(graph);
      break;
    }
    
    case 4: 
      //system("clear");
      graph.printVertexes(); 
      print_menu(graph); 
      break;
    
    case 5: 
      //system("clear");
      graph.printVertexesIndegree();
      print_menu(graph);
      break;
    
    case 6:
      //system("clear");
      graph.printTopologicalSort();
      break;

    case 7:
      printf("\n\nExiting program...");
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

