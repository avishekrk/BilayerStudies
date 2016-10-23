#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <algorithm>

#include "vertex.h"

using namespace std; 

class Graph
{
  
 public:
  Graph();
  std::vector<Vertex*> vertices; 
    
  //Ring Counter Routines 
  void FirstSort(std::vector<std::vector<Vertex*> > &allCycles);
  void CountCycles(std::vector<std::vector<Vertex*> >& allCycles);

};

#endif 
