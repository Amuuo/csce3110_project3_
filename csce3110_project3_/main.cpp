#include "graph.h"

enum menu_options { LOAD_GRAPH_DATA        = 1,
                    PRINT_VERTEX_DETAILS   = 2,
                    PRINT_SHORTEST_PATHS   = 3,
                    PRINT_ADJACENCY_LIST   = 4,
                    PRINT_INDEGREES        = 5,
                    PRINT_TOPOLOGICAL_SORT = 6,
                    EXIT                   = 7 };

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

  printf("\n");
  printf("\n\t1 - Load Graph Data from File");
  printf("\n\t2 - Print Vertex Details");
  printf("\n\t3 - Print Single-Source Shortest Paths");
  printf("\n\t4 - Print Adjacency List");
  printf("\n\t5 - Print Indegree of Each Vertex");
  printf("\n\t6 - Print Topological Sort of Graph");
  printf("\n\t7 - Exit");

  printf("\n\n\tSelection: "); cin >> menu_choice;  
  system("clear");

  switch (menu_choice) {
    
  case LOAD_GRAPH_DATA:
    graph.vertexes.clear();
    graph.inputGraphData();      
    graph.updateVertexParameters();
    print_menu(graph); break;    
  
  case PRINT_VERTEX_DETAILS: 
    graph.printVertexParameters(); 
    print_menu(graph); break;    
  
  case PRINT_SHORTEST_PATHS:{
    input_check:
    /* print all available vertexes to choose from */
    printf("\n\tAvailable Vertexes: ");
    for (auto& v : graph.vertexes) {
      printf("%c%c ",v.first, 
              ++graph.vertexes.find(v.first)!=graph.vertexes.end()?',':'\n');
    }
    /* check for vertex input errors and repeat if necessary */
    char name; 
    printf("\n\tInsert Starting Vertex: "); cin >> name;             
    if(graph.vertexes.find(name) == graph.vertexes.end()){
      system("clear");
      printf("\n\tNo vertex named %c exist...\n", name);
      goto input_check;
    }            
    graph.initStartVertex(name);
    graph.calculateShortestPaths(graph.pathStart->getName());                
    graph.printShortestPaths(graph.pathStart->getName());
    print_menu(graph); break;
  }   

  case PRINT_ADJACENCY_LIST:
    graph.printVertexes(); 
    print_menu(graph); break;    
 
  case PRINT_INDEGREES:
    graph.printVertexesIndegree();
    print_menu(graph); break;    
  
  case PRINT_TOPOLOGICAL_SORT: 
    graph.printTopologicalSort();
    print_menu(graph); break;
  
  case EXIT:
    printf("\n\nExiting program...");
    exit(1); break;
    
    default: break;
  }
}
