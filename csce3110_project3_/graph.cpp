
#include "graph.h"


Graph::Graph() : vertexes{} {}
Graph::Graph(const Graph & g) {
  
  vertexes = g.vertexes;
}
Graph::Graph(Graph && g) : vertexes{g.vertexes} {
  
  g.vertexes.clear();
}
/* insert vertex into graph's vertex map<char,Vertex> */
void Graph::insert_vertex(Vertex v) {
  
  vertexes[v.get_name()] = v;  
}
/* iterate through each vertex and print their adjacency list */
void Graph::print_vertexes() {
  
  for (auto& vertex : vertexes) {
    printf("\n\t%c: ",vertex.first);
    vertex.second.print_adjacency_list();
  }
}
/* iterate through each vertexes' adjacency list
   and update each vertexes indegree */
void Graph::update_vertex_parameters() {
  
  for (auto& vertex : vertexes) {
    for (auto& adj_vertex : vertex.second.get_adj()) {
      vertexes[adj_vertex.first].increment_indegree();
    }
  }
}
void Graph::print_vertex_parameters() {
  
  for (auto& vertex : vertexes) {
    
    printf("\n\n\t%c: ",vertex.second.get_name());
    printf("\n\n\t%-9s: ","adj_list");    
    vertex.second.print_adjacency_list();
    printf("\n\t%-9s: %d","indegree",vertex.second.get_indegree());
    printf("\n\t%-9s: %d","distance",vertex.second.get_dist());
    printf("\n\t%-9s: %c","path"    ,vertex.second.get_path());
    printf("\n\t%-9s: %s","known"   ,vertex.second.get_known()?"true":"false");
  }
}

void Graph::input_graph_data() {  
    
  ifstream  in_stream;
  string    input_line{};
  string    filename;
  Graph     graph{};
  char      vertex_name{};
  int       vertex_distance{};

  // open input file & check for error
  printf("\n\tEnter input filename: ");
  cin >> filename;
  in_stream.open(filename);      
  if (in_stream.fail()) { 
    printf("\nInput file failed to open. Exiting..."); 
    exit(1);
  }
  // input each line of graph data
  while (in_stream) {        
    getline(in_stream,input_line);
    Vertex v{input_line[0]};
    istringstream iss{input_line.substr(1)};

    while(iss){
      iss >> vertex_distance >> vertex_name;
      v.set_adj(vertex_name, vertex_distance);
      //v.adj[vertex_name] = vertex_distance;     
    }    
    vertexes[v.get_name()] = v;
  }  

}
/*checks if graph is empty*/
bool Graph::empty() {
  
  if(vertexes.empty()) { return true; }
  return false;
}

