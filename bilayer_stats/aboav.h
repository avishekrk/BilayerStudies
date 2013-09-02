//abaov.h 

#include <vertex>

#include "graph.h"
#include "vertex.h"

void aboavDiagnostic(std::vector<Vertex*> &iCycle, std::vector<vector <Vertex*> > &pairs, std::vector<vector<Vertex*> > &rings); 
std::vector <vector <Vertex*> > sideRings(std::vector <vector <Vertex*> > &pairs, std::vector <Vertex*> &iCycle); 
double aboavAverage(std::vector <std::vector<Vertex*> > &rings); 
void fillAboavBucket(int aboavBucket[], double &average, std::vector<Vertex*> &iCycle, std::vector<std::vector<int> > &aboavStack); 
std::vector <double> globalAboav(); 
void AboavStackDump(std::vector<std::vector <int> > &aboavStack); 
void Aboav(std::vector<std::vector<Vertex*> > &allCycles, int aboavBucket [], std::vector<std::vector<int> > &aboavStack); 
std::vector <double> globalAboav(std::vector<std::vector<int> > &aboavStack); 
bool doubleCount(std::vector <Vertex*> &list, std::vector<std::vector<Vertex*> > &pairs); 
