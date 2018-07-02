
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
  
  vertexes[v.get_name()] = move(&v);  
}
/* iterate through each vertex and print their adjacency list */
void Graph::print_vertexes() {

  for (auto& vertex : vertexes) {
    printf("\n\t%c: ",vertex.first);
    vertex.second->print_adjacency_list();
  }
}
/* iterate through each vertexes' adjacency list
   and update each vertexes indegree */
void Graph::update_vertex_parameters() {

  for (auto& vertex : vertexes) {
    for (auto& adj_vertex : vertex.second->get_adj()) {
      vertexes[adj_vertex.first]->increment_indegree();
    }
  }
}
void Graph::print_vertex_parameters() {

  for (auto& vertex : vertexes) {
    
    printf("\n\n\t%c: ",vertex.second->get_name());
    printf("\n\n\t%-9s: ","adj_list");    
    vertex.second->print_adjacency_list();
    printf("\n\t%-9s: %d","indegree",vertex.second->get_indegree());
    printf("\n\t%-9s: %d","distance",vertex.second->get_dist());
    printf("\n\t%-9s: %c","path"    ,vertex.second->get_path());
    printf("\n\t%-9s: %s","known"   ,vertex.second->get_is_known()?"true":"false");
  }
}

void Graph::input_graph_data() {  

  ifstream  in_stream;
  string    input_line{};
  string    filename;
  Graph     graph{};


  // open input file & check for error
  //printf("\n\tEnter input filename: ");
  //cin >> filename;
  filename = "input.txt";
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
    vertexes[v.get_name()] = new Vertex{v};
  }  
}
void Graph::calculate_shortest_paths(char vertex_name, int distance) {
   
  Vertex* small_v{};  
  Vertex* tmp{};
  int smallest_dist = inf;
  char    current_path;
  stack<Vertex*> smallest_stack;
  
  if (!source_set){
    vertexes[vertex_name]->set_dist(0);
    vertexes[vertex_name]->set_known(true);
    vertexes[vertex_name]->set_path(vertex_name);
    source = vertexes[vertex_name];
    source_set = true;
    //dijkstra_queue.push_front(&vertexes[vertex_name]);
  }
  
  //smallest_vertex = nullptr;  
  for (auto& v : vertexes[vertex_name]->get_adj()) {
    
    if (!vertexes[v.first]->get_is_known()) {
      
      
      if (v.second+distance < vertexes[v.first]->get_dist()) {
        vertexes[v.first]->set_dist(v.second+distance);
        vertexes[v.first]->set_path(vertex_name);
      }
      if (v.second <= smallest_dist) {
        small_v = vertexes[v.first];
        dijkstra_queue.push_front(small_v);
        smallest_dist = small_v->get_dist();
      }
      else{
        dijkstra_queue.push_back(vertexes[v.first]);
      }

    }
  } 
  //vertexes[min_v.first].set_known(true);
  
  while (!dijkstra_queue.empty()){    
    int small = dijkstra_queue.front()->get_dist();      
  
    for(auto& d : dijkstra_queue){
      d->get_dist()==small?d->set_known(true):void();
    }
  
    tmp = dijkstra_queue.front();
    dijkstra_queue.pop_front();
    
    calculate_shortest_paths(tmp->get_name(),tmp->get_dist());
    //tmp->set_known(true);
  }  
}

void Graph::print_shortest_paths(char vertex_name) {

  stack<Vertex*> paths;
  Vertex*        tmp;
  
  for (auto& v : vertexes) {
    
    if (v.second->get_dist() != inf) { 
      tmp = v.second;
      
      do {
        paths.push(tmp);
        //if(tmp->get_path() != '\0') 
        tmp = vertexes[tmp->get_path()];
      } while (tmp->get_name() != source->get_name());
      
      printf("\n\t%c",source->get_name());
      
      while (!paths.empty()) {
        printf("->%c",paths.top()->get_name());        
        paths.pop();
      }
      printf(" : %d",v.second->get_dist());      
    }
    else {
      printf("\n\tNo path to %c",v.second->get_name());      
    }
  }
  reset_vertexes();
  update_vertex_parameters();
}
void Graph::print_vertexes_indegree() {

  for (auto& v : vertexes) {
    cout << "\n\t" << v.first << ": " << v.second->get_indegree();
  }
}
void Graph::reset_vertexes() {  
  for (auto& v : vertexes) {    
    v.second->set_dist(inf);
    v.second->set_path('\0');
    v.second->set_known(false);
  }
  source_set = false;
}
/*checks if graph is empty*/
bool Graph::empty() {
  
  if(vertexes.empty()) { return true; }
  return false;
}

