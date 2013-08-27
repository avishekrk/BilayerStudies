//ringarea.cpp 
#include <iostream>
#include <vector>
#include <cmath>

#include "vertex.h"
#include "ringarea.h"


/*
  Test function to make sure things are working properly 
 */
void Hello()
{
  std::cout << "Hello World" << std::endl; 
}//Hello


/*
  sortRing, sorts ring vertices in the order that they are connected
  @param, ring, n vector of Vertex*
  @return, sring, sorted ring
 */
std::vector<Vertex*> ringSort(std::vector<Vertex*> &ring,bool Debug)
{
  std::vector<Vertex*> cycle = ring; 
  std::vector<Vertex*> sorted;
  unsigned int n = cycle.size(); 

  if(Debug)
    {
      std::cout << "Pre-Sorted Ring Coordinates" << std::endl; 
      for(unsigned int i = 0; i < cycle.size(); i++)
	std::cout << cycle[i]->x << " " << cycle[i]->y << std::endl; 
      
      for(unsigned int i = 0; i < cycle[0]->edges.size(); i++)
	{
	  std::cout << cycle[0]->edges[i]->index << ": " << cycle[0]->edges[i]->x << " " << cycle[0]->edges[i]->y << std::endl; 
	}

    }//end Debug 

  sorted.push_back(cycle[0]); 
  cycle.erase(cycle.begin());
  bool Match = false; 
  while(sorted.size() != n)
    {
      for(unsigned int i = 0; i < sorted.back()->edges.size(); i++)
	{
	  Match = false; 
	  for(unsigned int j = 0; j < cycle.size(); j++)
	    {
	      if(sorted.back()->edges[i] == cycle[j])
		{
		  if(Debug) std::cout << "Found a Match" << std::endl; 
		  sorted.push_back(cycle[j]); 
		  cycle.erase(cycle.begin()+j); 
		  Match = true; 
		  break; 
		}//if 
	    }
	  if(Match)
	    break; 
	}//i loop 
    }//while loop 


  if (Debug)
    {
      std::cout<< "Sorted List" << std::endl; 
      for(unsigned int i = 0; i < sorted.size(); i++)
	std::cout << sorted[i]->x << " " << sorted[i]->y << std::endl; 
    }

  return sorted; 

}//sortRing()

/*
  Given a sorted list output is the area
 */

float calcarea(std::vector<Vertex*> ring,bool Debug)
{
  float area; 
  unsigned int n = ring.size() + 1; 
  float *x = new float [n];
  float *y = new float [n]; 

  
  for(unsigned int i = 0; i < ring.size(); i++)
    {
      if (Debug) std::cout << "x= " << ring[i]->x << " y= " << ring[i]->y << std::endl; 
      x[i] = ring[i]->x; 
      y[i] = ring[i]->y;
    }//i loop 
  
  x[n-1] = ring[0]->x; 
  y[n-1] = ring[0]->y;
  
  //Calculate determinent for the area
  
  if(Debug)
    {
      std::cout << "Printing from array" << std::endl; 
      for(unsigned int i = 0; i < n; i++)
	std::cout << x[i] << " " << y[i] << std::endl; 
    }
  double a=0,b=0; 

  for(unsigned int i = 0; i < n-1; i++)
    {
      a += x[i]*y[i+1];
      b += y[i]*x[i+1]; 
    }

  area = (a-b)*0.5; 
  areaBucket[n-1] += abs(area); 

  if(Debug) std::cout << "Area is " << area << std::endl; 

  delete [] x; 
  delete [] y; 

  return abs(area); 
  
}//calcarea()

/*
  ringArea, calculated the area of of convex polygon and return a
  sorted ring list 
 */
float ringArea(std::vector<Vertex*>  &ring_unsorted, float areaBucket[], bool Debug)
{
  
  std::vector <Vertex*> ring = ringSort(ring_unsorted,Debug); 

  unsigned int n = ring.size() + 1; 
  float *x = new float [n];
  float *y = new float [n]; 
  float area; 

  
  for(unsigned int i = 0; i < ring.size(); i++)
    {
      if (Debug) std::cout << "x= " << ring[i]->x << " y= " << ring[i]->y << std::endl; 
      x[i] = ring[i]->x; 
      y[i] = ring[i]->y;
    }//i loop 
  
  x[n-1] = ring[0]->x; 
  y[n-1] = ring[0]->y;
  
  
  
  //Calculate determinent for the area
  
  if(Debug)
    {
      std::cout << "Printing from array" << std::endl; 
      for(unsigned int i = 0; i < n; i++)
	std::cout << x[i] << " " << y[i] << std::endl; 
    }
  double a=0,b=0; 

  for(unsigned int i = 0; i < n-1; i++)
    {
      a += x[i]*y[i+1];
      b += y[i]*x[i+1]; 
    }

  area = (a-b)*0.5; 
  areaBucket[n-1] += abs(area); 

  if(Debug) std::cout << "Area is " << area << std::endl; 

  delete [] x; 
  delete [] y; 
   
  return abs(area); 
}


/*
  Calculates the average bond length of all the bonds. 
 */
float avgbnd_length(Graph &bilayer)
{
  float bnd_length=0; 
  int nbonds = 0; 
  float xij,yij,zij,r;

  for(unsigned int i = 0; i < bilayer.vertices.size(); i++)
    {
      for(unsigned int j = 0; j < bilayer.vertices[i]->edges.size(); j++)
	{
	  xij = bilayer.vertices[i]->x - bilayer.vertices[i]->edges[j]->x;
	  yij = bilayer.vertices[i]->y - bilayer.vertices[i]->edges[j]->y;
	  zij = bilayer.vertices[i]->z - bilayer.vertices[i]->edges[j]->z;
	  r = sqrt( xij*xij + yij*yij + zij*zij );
	  bnd_length += r; 
	  nbonds += 1; 
	  
	}//j loop over the edges of the ith vertex 
    }//i loop over the vertices 

  return bnd_length/((float)nbonds); 
}//avgbnd_length 
