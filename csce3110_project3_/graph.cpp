
#include "graph.h"


Graph::Graph() : vertexes{} {}

Graph::Graph(const Graph & g) { 
  vertexes = g.vertexes;
}

Graph::Graph(Graph && g) : vertexes{g.vertexes} {  
  g.vertexes.clear();
}

/* insert vertex into graph's vertex map<char,Vertex> */
void Graph::insertVertex(Vertex&& v) {  
  vertexes[v.getName()] = move(&v);  
}

/* iterate through each vertex and print their adjacency list */
void Graph::printVertexes() {
  for (auto& vertex : vertexes) {
    printf("\n\t%c: ",vertex.first);
    vertex.second->printAdjacencyList();
  }
}

/* iterate through each vertexes' adjacency list
   and update each vertexes indegree */
void Graph::updateVertexParameters() {
  for (auto& vertex : vertexes)
    for (auto& adjVertex : vertex.second->getAdj()) 
      vertexes[adjVertex.first]->incrementIndegree();
}

void Graph::printVertexParameters() {
  Vertex* currVertex{};
  
  for (auto& vertex : vertexes) {    
    currVertex = vertex.second;
    printf("\n\n\t%c: ",currVertex->getName());
    printf("\n\n\t%-9s: ","adj_list"); currVertex->printAdjacencyList();
    printf("\n\t%-9s: %d","indegree",  currVertex->getIndegree());
    printf("\n\t%-9s: %d","distance",  currVertex->getDist());
    printf("\n\t%-9s: %c","path"    ,  currVertex->getPath());
    printf("\n\t%-9s: %s","known"   ,  currVertex->getIsKnown()?"true":"false");
  }
}

void Graph::inputGraphData() {  

  ifstream  inStream;
  string    inputLine{};
  string    filename;
  Graph     graph{};

  // open input file & check for error
  printf("\n\tEnter input filename: ");
  cin>>filename;
  inStream.open(filename);      
  
  if (inStream.fail()) { 
    printf("\nInput file failed to open. Exiting..."); 
    exit(1);
  }
  // input each line of graph data
  while (inStream) {            
    char vertexName{};
    int  vertexDistance{};    
    
    getline(inStream,inputLine);
    Vertex v{inputLine[0]};
    istringstream iss{inputLine.substr(1)};

    while (iss){
      iss >> vertexDistance >> vertexName;
      if (vertexName != '\0') 
        v.setAdjVertex(vertexName,vertexDistance);          
    }  
    vertexes[v.getName()] = new Vertex{v};
  }  
}

void Graph::calculateShortestPaths(char currVertexName,int currDistFromSource) {
  // all variables to help make code more readable  
  Vertex* adjacentVertex{};             
  Vertex* currentVertex = vertexes[currVertexName];
  int     distFromCurr;
    
  // run dijkstra's
  for (auto& v : currentVertex->getAdj()) {          
    adjacentVertex = vertexes[v.first];
    distFromCurr   = v.second;

    if (!adjacentVertex->getIsKnown()) {            
      
      if (distFromCurr+currDistFromSource <= adjacentVertex->getDist()) {
        adjacentVertex->setDist(distFromCurr+currDistFromSource);
        adjacentVertex->setPath(currVertexName);
      }
      if (distFromCurr<=currentVertex->getDist()){
        dijkstraQueue.push_front(adjacentVertex);                        
      
      } else { dijkstraQueue.push_back(adjacentVertex); }         
    }
  }
  while (!dijkstraQueue.empty()){    
    // check if there are multiple equivalent minimum distances      
    int size = dijkstraQueue.front()->getDist();
    for (auto i = 0; dijkstraQueue[i]->getDist()!=size; ++i)        
      dijkstraQueue[i]->setKnown(true);      
      
    /* pop the smallest distance vertex and send it through */
    Vertex* tmp = dijkstraQueue.front();        
    dijkstraQueue.pop_front();        
    calculateShortestPaths(tmp->getName(),tmp->getDist());
  }
}

void Graph::printShortestPaths(char vertex_name) {
  stack<Vertex*> pathToSource;     // stack to hold each vertex until start
  Vertex*        currVertex{};     // current vertex in main for-loop
  
  /* iterate through all vertexes */
  for (auto& v : vertexes) { currVertex = v.second;     
    /* if vertex distance is inf then there is no path */
    if (currVertex->getDist() != inf) { 
      /* push vertexes into stack until tmp->path == starting vertex */      
      do {
        pathToSource.push(currVertex);
        currVertex = vertexes[currVertex->getPath()];
      } while (currVertex->getName() != pathStart->getName());

      printf("\n\t%c",pathStart->getName());  
      while (!pathToSource.empty()) {
        printf("->%c",pathToSource.top()->getName());                
        pathToSource.pop();
      } printf(" : %d",v.second->getDist());      
    
    } else { printf("\n\tNo path to %c",currVertex->getName()); }
  }
  // reset vertex parameters
  resetVertexes();
  updateVertexParameters();
}

void Graph::printVertexesIndegree() {
  for (auto& v : vertexes)
    printf("\n\t%c: %d",v.first,v.second->getIndegree());      
}

void Graph::resetVertexes() {  
  for (auto& v : vertexes) {    
    v.second->setDist(inf);
    v.second->setPath('\0');
    v.second->setKnown(false);
    v.second->setIndegree(0);
  }
}

/*checks if graph is empty*/
bool Graph::empty() {  
  if(vertexes.empty()) {
    return true;
  } else { return false; }
}

