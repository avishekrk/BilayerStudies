//aboav.cpp 
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "vertex.h"
#include "graph.h"

void aboavDiagnostic(std::vector<Vertex*> &iCycle, std::vector<vector <Vertex*> > &pairs, std::vector<vector<Vertex*> > &rings)
{
  FILE* out; 
  out = fopen("aboavDiagnostic.dat","w"); 
  fprintf(out, "#Ring Coordinates\n"); 
  for(unsigned int i =0; i < iCycle.size(); i++)
    {
      fprintf(out, "{%f,%f}\n", iCycle[i]->x, iCycle[i]->y); 
    }//i loop over coordinates of ring 

  fprintf(out, "\n#RingConnections\n");
  for(unsigned int i =0; i < iCycle.size(); i++)
    {
      fprintf(out, "#Ring {%f,%f}\n",iCycle[i]->x, iCycle[i]->y);
      for(unsigned int j =0; j < iCycle[i]->edges.size(); j++)
	{
	  fprintf(out, "{%f,%f}\n",iCycle[i]->edges[j]->x, iCycle[i]->edges[j]->y);
	}//j loop over connections 
      fprintf(out, "\n"); 
    }//i loop over vertices 
  
      fprintf(out, "\n#Pairs\n"); 
  for(unsigned int i =0; i < pairs.size(); i++)
    {

      fprintf(out, "{%f,%f} {%f,%f}\n", pairs[i][0]->x, pairs[i][0]->y, pairs[i][1]->x, pairs[i][1]->y); 
    }//i loop over the pairs 
  fprintf(out, "\n#SideRings\n"); 
  for(unsigned int i =0; i < rings.size(); i++)
    {
      for(unsigned int j =0; j < rings[i].size(); j++)
	{
	  fprintf(out, "{%f,%f}\n",rings[i][j]->x, rings[i][j]->y);  
	}//i loop over the rings 
      fprintf(out,"\n"); 
    }
  fclose(out); 
}//aboavDiagnostic()

/**
   finds the rings that are around a particular cycle 
   @param pairs the edges 
   @param iCycle the Cycle that you are trying to find the
   edges around 
   @return sideRings with the correlated rings 
*/

std::vector <vector <Vertex*> > sideRings(std::vector <vector <Vertex*> > &pairs, std::vector <Vertex*> &iCycle)
{
  std::vector <vector <Vertex*> > list; 
  list.clear(); 
  //bool foundiCycle= false; 
  for(unsigned int i =0; i < pairs.size(); i++)
    {
      for(unsigned int j =0; j < pairs[i][0]->rings.size(); j++)
	{
	  for(unsigned int k =0; k < pairs[i][0]->rings[j].size(); k++)
	    {
	      if(pairs[i][1] == pairs[i][0]->rings[j][k])
		{
		  if(iCycle == pairs[i][0]->rings[j])
		    {
		      break;  
		    }
		  else
		    {
		      list.push_back(pairs[i][0]->rings[j]); 
		      break; 
		    }
		}
	    }//k loop 
	}// j loop 
    }//i loop 
  return list; 
}

/**
   Calculates the local Aboav average 
   @param rings contains all the correlated rings 
   @return average is the average of the neighboring 
   rings 
 */
double aboavAverage(std::vector <std::vector<Vertex*> > &rings)
{
  double sum=0.0;  
  double Nrings = rings.size(); 
  for(unsigned int i =0; i < rings.size(); i++)
    {
      sum+=rings[i].size(); 
    }
  
  return sum/Nrings; 
}
/**
   Fill the Aboav Bucket 
   @param average value of the neighboring rings 
   @param iCycle the size of the ring 
 */
void fillAboavBucket(double aboavBucket[], double &average, std::vector<Vertex*> &iCycle, std::vector<std::vector<double> > &aboavStack, int ringmax)
{
  std::vector <double> list; 
  for(int i =0; i < ringmax; i++) aboavBucket[i]=0; //12
  aboavBucket[iCycle.size()]= average; 
  for(int i =0; i < ringmax; i++) list.push_back(aboavBucket[i]); //12 
  aboavStack.push_back(list); 
  list.clear(); 
}
/**
 Calculate the global Aboav function and output into a file 
 @param aboavStack has neighboring rings averages
 @return vector containing the aboav function 
*/
std::vector <double> globalAboav(std::vector<std::vector<double> > &aboavStack, int ringmax)
{
  std::vector <double> aboavfunction; 
  for(int i =0; i < ringmax; i++) aboavfunction.push_back(0); //12 
    
  double sum, counter;  
  for(unsigned int i =0; i < aboavStack[0].size(); i++)
    {
      sum = 0; 
      counter =0; 
      for(unsigned int j =0; j < aboavStack.size(); j++)
	{
	  if(aboavStack[j][i] != 0)
	    {
	      sum += aboavStack[j][i]; 
	      counter++; 
	    }
	}//j loop 
      if(counter == 0)
	{
	  aboavfunction[i] =0; 
	}
      else
	{
	  aboavfunction[i] = sum/counter; 
	}
      
    }//i loop
  return aboavfunction; 
}

/**
 AboavStack Dump into a file 
 @param aboavStack contains all the info 
 */
void AboavStackDump(std::vector<std::vector <double> > &aboavStack)
{
  FILE* out; 
  out = fopen("AboavStack.dat","w"); 
  for(unsigned int i =0; i < aboavStack.size(); i++)
    {
      for(unsigned int j =0; j < aboavStack[i].size(); j++)
	{
	  fprintf(out, "%f ",float(aboavStack[i][j])); 
	}
      fprintf(out,"\n"); 
    }
  fclose(out); 
}


/*
  Don't double count edges the edges in the Aboav function 
  @param list is the edge that will be tested to see if already part 
  of the function 
  @param pairs contains all the pairs 
  @return boolean if it's already part of the cycle 
 */
bool doubleCount(std::vector <Vertex*> &list, std::vector<std::vector<Vertex*> > &pairs)
{
  for(unsigned int i =0; i < pairs.size(); i++)
    {
      if(list[0] == pairs[i][0] || list[0] == pairs[i][1])
	{
	  if(list[1] == pairs[i][0] || list[0] == pairs[i][1])
	    {
	      return true; 
	    }
	}
    }
  return false; 
}

/*
  Find edges from a cycleList and throw them in a file
  @param vector <Vertex*> ring -- ring to find out how everything is connected 
  Should be able to do cycle->edges[i] First put out a connectivty matrix 
 */
std::vector <std::vector <Vertex*> > findEdges(std::vector <Vertex*> &ring)
{
  bool repeat = false; 
  std::vector <std::vector <Vertex*> > pairs;   
  for(unsigned int i =0; i<ring.size(); i++)
    {
      for(unsigned int j =0; j < ring[i]->edges.size(); j++)
	{
	  for(unsigned int k =0; k <ring.size(); k++)
	    {
	      if(ring[i]->edges[j] == ring[k])
		{
		  std::vector <Vertex*> list; 
		  list.push_back(ring[i]);
		  list.push_back(ring[k]);
		  repeat = doubleCount(list, pairs); 
		  if(!repeat)
		    {
		      pairs.push_back(list);
		    }
		  
		  list.clear(); 
		
		}
	    }// k loop over the vertices 
	}//j loop over the connection of a single vertex
    }//i loop over vertices of ring
  return pairs; 
  
}//findEdges()


/**
   Calculates the Aboav function 
 */
void Aboav(std::vector<std::vector <Vertex*> > &allCycles, double aboavBucket [],std::vector<std::vector<double> > &aboavStack, int ringmax)
{
  double average; //value;  
  std::vector <Vertex*> iCycle; 
  std::vector <vector <Vertex*> > pairs; 
  std::vector <std::vector <Vertex*> > rings; 
  for(unsigned int i =0; i < allCycles.size(); i++)
    {
      iCycle = allCycles[i];
      pairs = findEdges(iCycle); 
      //Now find the other rings in the pairs 
      rings = sideRings(pairs, iCycle); 
      aboavDiagnostic(iCycle, pairs, rings); 
       //Calculate Average 
      average = aboavAverage(rings);
      fillAboavBucket(aboavBucket, average, iCycle,aboavStack,ringmax);
      iCycle.clear(); 
      pairs.clear(); 
      rings.clear(); 
    }
  std::vector <double> aboavfunction = globalAboav(aboavStack,ringmax); 
  AboavStackDump(aboavStack); 
  
  for(unsigned int i =0; i < aboavfunction.size(); i++)
    {
      std::cout << i << "   " <<  aboavfunction[i]  << std::endl; 
    }
 
  FILE* ringAvg; 
  ringAvg = fopen("ABOAV.dat","w"); 
  for(unsigned int i =0; i < aboavfunction.size(); i++)
    {
      fprintf(ringAvg, "%d  %f\n", i, aboavfunction[i]); 
    }
  fclose(ringAvg); 
}


