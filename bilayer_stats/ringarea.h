//ringarea.h 
#include <vector>

#include "vertex.h"
#include "graph.h"

void Hello(); 
std::vector<Vertex*> ringSort(std::vector<Vertex*> &ring, bool Debug=false);
float ringArea(std::vector<Vertex*>  &ring, float areaBucket[], int ringmax, bool Debug=false); 
float avgbnd_length(Graph &bilayer);
 
