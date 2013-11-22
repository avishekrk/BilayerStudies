//ringarea.h 
#include <vector>

#include "vertex.h"
#include "graph.h"

void Hello(); 
std::vector<Vertex*> ringSort(std::vector<Vertex*> &ring, bool Debug=false);
float ringArea(std::vector<Vertex*>  &ring, float areaBucket[],float latticex, float latticey, bool Debug=false); 
float calcarea(std::vector<Vertex*> &ring, bool Debug=false); 
float avgbnd_length(Graph &bilayer,float latticex, float latticey);
float avgbnd_lengthtwo(Graph &bilayer,float latticex, float latticey);
void PolygonPBC(std::vector<std::vector<Vertex*> > &sortedCycles, bool Debug=false);
bool PBCcheck(std::vector<Vertex*> &ring); 
void outputConnect(Graph &bilayer,float latticex, float latticey); 
