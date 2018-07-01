
#include "graph.h"


Graph::Graph() : vertexes{} {}
Graph::Graph(const Graph & g) {
  
  vertexes = g.vertexes;
}
Graph::Graph(Graph && g) : vertexes{g.vertexes} {
  
  g.vertexes.clear();
}
/* insert vertex into graph's vertex map<char,Vertex> */
void Graph::insert_vertex(Vertex&& v) {
  
  vertexes.insert(make_pair(v.get_name(), move(v)));  
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
    printf("\n\t%-9s: %s","known"   ,vertex.second.get_is_known()?"true":"false");
  }
}

void Graph::input_graph_data() {  
    
  ifstream  in_stream;
  string    input_line{};
  string    filename;
  Graph     graph{};


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
    
    char vertex_name{};
    int  vertex_distance{};
    
    getline(in_stream,input_line);
    Vertex v{input_line[0]};

    istringstream iss{input_line.substr(1)};

    while(iss){
      iss >> vertex_distance >> vertex_name;
      if(vertex_name != '\0') v.set_adj_vertex(vertex_name, vertex_distance);      
      //v.adj[vertex_name] = vertex_distance;     
    }    
    vertexes.insert(make_pair(v.get_name(),v));
  }  
}
void Graph::calculate_shortest_paths(char vertex_name, int distance) {
   
  Vertex* small_v{};
  pair<char,int> min_v{make_pair('\0',numeric_limits<int>::max())};
  Vertex* tmp{}; 
  int     smallest_dist = numeric_limits<int>::max();
  char    current_path;
  stack<Vertex*> smallest_stack;
  
  if (!source_set){
    vertexes[vertex_name].set_dist(0);
    vertexes[vertex_name].set_known(true);
    vertexes[vertex_name].set_path(vertex_name);
    source = &vertexes[vertex_name];
    source_set = true;
    //dijkstra_queue.push_front(&vertexes[vertex_name]);
  }
  
  //smallest_vertex = nullptr;  
  for (auto& v : vertexes[vertex_name].get_adj()) {
    
    if (!vertexes[v.first].get_is_known()) {
      min_v = v.second < min_v.second ? make_pair(v.first,v.second) : min_v;
      
      if (v.second+distance < vertexes[v.first].get_dist()) {
        vertexes[v.first].set_dist(v.second+distance);
        vertexes[v.first].set_path(vertex_name);
      }
      dijkstra_queue.push_back(&vertexes[v.first]);
      /*if (v.second <= smallest_dist) {
        smallest_vertex = &vertexes[v.first];
        dijkstra_queue.push_front(smallest_vertex);
        smallest_dist = smallest_vertex->get_dist();
      }
      else {
        dijkstra_queue.push_back(&vertexes[vertex_name]);
      } */
    }
  } 
  //vertexes[min_v.first].set_known(true);
  
  while (!dijkstra_queue.empty()){    
    int small = vertexes[min_v.first].get_dist();      
  
    for(auto& d : dijkstra_queue){
      d->get_dist()==min_v.second?d->set_known(true):void();
    }
  
    tmp = dijkstra_queue.front();
    dijkstra_queue.pop_front();
    
    calculate_shortest_paths(tmp->get_name(),tmp->get_dist());
    //tmp->set_known(true);
  }
  print_shortest_paths(source->get_name());  
}

char Graph::print_shortest_paths(char vertex_name, int dist) {
  if (vertex_name == '\0') {
    cout << "->" << vertex_name;
  }
  else {
    for (auto v : vertexes) {
      if (v.second.get_path() == vertex_name) {
        return print_shortest_paths(v.second.get_name(),dist+v.second.get_dist());        
      }
    }
  }
}
/*checks if graph is empty*/
bool Graph::empty() {
  
  if(vertexes.empty()) { return true; }
  return false;
}

