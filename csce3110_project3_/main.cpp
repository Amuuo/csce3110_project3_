#pragma once
#include "graph.h"

void print_menu(Graph&);

//=======================================================
int main() {

  Graph graph{};
  print_menu(graph);  
  return 0;
}
//=======================================================

void print_menu(Graph& graph) {
  
  int menu_choice;

  printf("\n\n\t1 - Load Graph Data from File");
  printf("\n\t2 - Print Vertex Details");
  printf("\n\t3 - Print Single-Source Shortest Paths");
  printf("\n\t4 - Print Adjacency List");
  printf("\n\t5 - Print Indegree of Each Vertex");
  printf("\n\t6 - Print Topological Sort of Graph");
  printf("\n\t7 - Exit");

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
      printf("\n\tNo vertex named %c exist...\n", name);
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
    graph.printVertexes(); 
    print_menu(graph); 
    break;    
  case 5:       
    graph.printVertexesIndegree();
    print_menu(graph);
    break;    
  case 6:      
    graph.printTopologicalSort();
    print_menu(graph);
    break;
  case 7:
    printf("\n\nExiting program...");
    exit(1); 
    break;
    
   default: break;
  }
}
