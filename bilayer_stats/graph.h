#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <algorithm>
#include <string>

using namespace std; 

class Vertex
{
  
  Vertex* BFSHelper(double xFind, double yFind, int searchDepth, std::vector<Vertex*>& fifo);
 public:
  float x; 
  float y; 
  float z; 
  int index;
  string type; 
  Vertex();
  std::vector<Vertex*> edges; 
  std::vector<vector<Vertex*> > rings;
  Vertex(float xIn, float yIn, float zIn);
  Vertex(Vertex &v);

  void AddEdge(Vertex* edge);
  int RemoveEdge(double xVert, double yVert);
  int RemoveEdge(Vertex* edge);
  int RemoveSingleEdge(Vertex* edge);
  void ClearConnection();
  void ModifyData(double xNew, double yNew, double zNew);


};

#endif 
