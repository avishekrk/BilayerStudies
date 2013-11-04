//ringarea.h 
#include <vector>

#include "vertex.h"
#include "graph.h"

void Hello(); 
std::vector<Vertex*> ringSort(std::vector<Vertex*> &ring, bool Debug=false);
float ringArea(std::vector<Vertex*>  &ring, float areaBucket[], bool Debug=false); 
float calcarea(std::vector<Vertex*> &ring, bool Debug=false); 
float avgbnd_length(Graph &bilayer);
void PolygonPBC(std::vector<std::vector<Vertex*> > &sortedCycles);  
