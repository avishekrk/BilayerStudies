#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

#include "graph.h"
#include "vertex.h"

/*
  Constructor for Graph 
 */
Graph::Graph()
{
  
}//Graph()

/*
  performs the breadth first search algorthium
  @param xFind: x coordinate to find
  @param yFind: y coordinate to find
  @param searchDepth: how many generations the search will go
  @param fifo: first in first out queue
*/
Vertex* Vertex::BFSHelper(double xFind, double yFind, int searchDepth, std::vector<Vertex*>& fifo)
{
  int levelSize = 1;
  for(int i = 0; i < levelSize; i++)
    fifo.push_back(this);
  for(int k = 0; k < searchDepth; k++)
    {
      int newLevelSize = 0;
      for(int i = 0; i < levelSize; i++)
	{
	  if(fifo[0]->x == xFind && fifo[0]->y == yFind)
	    {
	      return fifo[0];//Found!!
	    }
	  for(unsigned int j = 0; j < fifo[0]->edges.size(); j++)
	    {
	      if(fifo[0]->edges[i] == fifo[0])
		continue;
	      fifo.push_back(fifo[0]->edges[i]);
	      newLevelSize++;
	    }
	  fifo.erase(fifo.begin());
	}
      levelSize = newLevelSize;
    }
  return 0;
}//BFSHelper()

/*
  performs the breadth first search algorthium
  @param xFind: x coordinate to find
  @param yFind: y coordinate to find
  @param searchDepth: how many generations the search will go
  @param fifo: first in first out queue
*/
Vertex* Vertex::BFS(double xFind, double yFind, int searchDepth)
{
	std::vector<Vertex*> fifo;
	return BFSHelper(xFind, yFind, searchDepth, fifo);	
}//BFS()


/*
  prevent counting rings that are made up of smaller rings
  @param cycleList: list of all cycles
*/
void avoidSuperRing(vector <vector<Vertex*> > &cycleList)
{
  vector <int> list;
  list.clear();
  for(unsigned int i =0; i<cycleList.size(); i++) sort(cycleList[i].begin(), cycleList[i].end()); //sort the entire cycleList
  for(unsigned int i =0; i<cycleList.size(); i++)
    {
      
      if(cycleList[i].size() < 8) continue;
      vector <Vertex*> iCycle = cycleList[i]; 
      bool erase = true; 
      for(unsigned int j =0; j<cycleList.size(); j++)
        {
	  
          if(cycleList[j].size() > 5) continue;
	  vector <Vertex*> jCycle = cycleList[j];
	  erase = true;
	  for(unsigned int k =0; k<jCycle.size(); k++) // examine all the vertices of the miniRing 
            {
              bool found = false;
              for(unsigned int l =0; l<iCycle.size(); l++) //compare all vertices of the BigRing to one of the miniRing 
                {
		  if(iCycle[l] == jCycle[k]){found = true;} //if they are the same 
		}
	      if(!found){ erase = false; break;} //if none of the vertices were the same stop comparing with the miniRing
            }
	  if(erase) break;
        }
      if(erase)
	{ 
	  cycleList.erase(cycleList.begin() + i);
	  i--; 
	  
	}
      
    }
  
}//avoidSuperRing()

/*
  Compares the current cycle with all the cycles on the cycleList if they are the same it is not added 
  to the cyclelist
  @param cycleList: List of all Cycles
  @param cycle found by findCyclesToSelf
*/
void AddNoRepeats(std::vector<std::vector<Vertex*> > &cycleList, std::vector<Vertex*>& cycle)
{
  std::sort(cycle.begin(), cycle.end());
  for(unsigned int i = 0; i < cycleList.size(); i++)
    {
      if(cycleList[i].size() == cycle.size())
	{
	  bool theSame = true;
	  for(unsigned int j = 0; j < cycle.size(); j++)
	    {
	      if((cycleList[i])[j] != cycle[j])
		{
		  theSame = false;
		  break;
		}
	    }
	  
	  if(theSame)
	    return;
	}
    }
  cycleList.push_back(cycle);
}

void Vertex::findCyclesToSelf(int maxCycleSize, std::vector<std::vector<Vertex*> > &cycleList)
{
  double xFind = x; //Coordinates to find 
  double yFind = y; //Coordinates to find 
  
  int levelSize = 1;
  std::vector<Vertex*> fifo;
  std::vector<Vertex*> parentFo;
  std::vector<std::vector<Vertex*> > cycleTron;
  std::vector<std::vector<Vertex*> > cycleTronNew;
  for(int i = 0; i < levelSize; i++)
    fifo.push_back(this); //push vertex pointer into queue
  parentFo.push_back(fifo[0]); //push onto ParentFo
  std::vector<Vertex*> parentTron;
  //parentTron.push_back(this);
  cycleTron.push_back(parentTron);
  for(int k = 0; k < maxCycleSize; k++) //start searching for self 
    {
      int newLevelSize = 0;
      for(int i = 0; i < levelSize; i++)
	{
	  
	  if(k != 0)//see if it just found itself after the first iteration of the loop 
	    {
	      if(fifo[0]->x == xFind && fifo[0]->y == yFind) 
		{
		  AddNoRepeats(cycleList, cycleTron[i]);
		}
	    }
	  for(unsigned int j = 0; j < fifo[0]->edges.size(); j++)
	    {
	      if(fifo[0]->edges[j] == parentFo[0])
		continue;
	      std::vector<Vertex*> currentPath;
	      currentPath = cycleTron[i];
	      currentPath.push_back(fifo[0]->edges[j]);
	      cycleTronNew.push_back(currentPath);
	      fifo.push_back(fifo[0]->edges[j]);
	      parentFo.push_back(fifo[0]);
	      newLevelSize++;
	    }
	  parentFo.erase(parentFo.begin());
	  fifo.erase(fifo.begin());
	}
      cycleTron = cycleTronNew;
      cycleTronNew.clear();
      levelSize = newLevelSize;
    }
  return;
}

/*
  CountCycles function BFS around a vertex until it finds itself and stores in allCycles
  @param: allCycles: CycleList 
  @param: countBucket: keeps track for ring statistics 
*/
void Vertex::CountCyclesLocally(std::vector<std::vector<Vertex*> >& allCycles)
{

  this->findCyclesToSelf(11, allCycles);
  
  for(unsigned int i = 0; i < allCycles.size(); i++) //Make sure cycle doesn't go back on itself                            {
    {
      for(unsigned int j = 0; j < allCycles[i].size(); j++)
	{ 
	  bool ifbreak = false;
	  Vertex* current = (allCycles[i])[j];
	  for(unsigned int k = 0; k < allCycles[i].size(); k++)
	    {
	      if(current == (allCycles[i])[k] && k != j)
		{
		  allCycles.erase(allCycles.begin() + i);
		  i--;
		  ifbreak = true; break;
		}
	    }
	  if(ifbreak) break;
	}//j loop over cycle 
    }//i loop over cyclelist 
  
  //    avoidSuperRing(allCycles); //makes sure none of the big rings are apart of smaller rings. maybe make apart of AddNoRepeats                                                           
  
}//CountCyclesLocally()

void Graph::FirstSort(std::vector<std::vector<Vertex*> > &allCycles)
{
  avoidSuperRing(allCycles); 
}


void Graph::CountCycles(std::vector<std::vector<Vertex*> >& allCycles)
{
  allCycles.clear(); //empty the cycleList
  for(unsigned int i = 0; i < vertices.size(); i++) //BFS to find itself 
    {
      vertices[i]->findCyclesToSelf(11, allCycles);
    }	
  for(unsigned int i = 0; i < allCycles.size(); i++) //Make sure cycle doesn't go back on itself 
    {
      for(unsigned int j = 0; j < allCycles[i].size(); j++)
	{ bool ifbreak = false;
	  Vertex* current = (allCycles[i])[j];
	  for(unsigned int k = 0; k < allCycles[i].size(); k++)
	    {
	      if(current == (allCycles[i])[k] && k != j)
		{
		  allCycles.erase(allCycles.begin() + i);
		  i--;
		  ifbreak = true; break;
		}
	    }
	  if(ifbreak) break;
	}
    }
  
  avoidSuperRing(allCycles); //makes sure none of the big rings are apart of smaller rings. maybe make apart of AddNoRepeats 
  
}//CountCycles()

