//abaov.h 

#include <vector>

#include "graph.h"
#include "vertex.h"

void aboavDiagnostic(std::vector<Vertex*> &iCycle, std::vector<vector <Vertex*> > &pairs, std::vector<vector<Vertex*> > &rings); 
std::vector <vector <Vertex*> > sideRings(std::vector <vector <Vertex*> > &pairs, std::vector <Vertex*> &iCycle); 
double aboavAverage(std::vector <std::vector<Vertex*> > &rings); 
void fillAboavBucket(double aboavBucket[], double &average, std::vector<Vertex*> &iCycle, std::vector<std::vector<double> > &aboavStack, int ringmax); 
std::vector <double> globalAboav(std::vector<std::vector<double> > &aboavStack); 
void AboavStackDump(std::vector<std::vector <double> > &aboavStack); 
void Aboav(std::vector<std::vector<Vertex*> > &allCycles, double aboavBucket [], std::vector<std::vector<double> > &aboavStack, int ringmax); 
std::vector <double> globalAboav(std::vector<std::vector<int> > &aboavStack, int ringmax); 
bool doubleCount(std::vector <Vertex*> &list, std::vector<std::vector<Vertex*> > &pairs); 
