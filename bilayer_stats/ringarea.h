//ringarea.h 
#include <vector>

#include "vertex.h"

void Hello(); 
std::vector<Vertex*> ringSort(std::vector<Vertex*> &ring, bool Debug=false);
float ringArea(std::vector<Vertex*>  &ring, bool Debug=false); 
