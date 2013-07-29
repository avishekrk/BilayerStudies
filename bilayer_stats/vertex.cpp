#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdio>

#include "vertex.h"

/*
  Contstructor for Vertex Objects
 */

Vertex::Vertex()
{
  x = 0; 
  y = 0; 
  z = 0; 
}//Vertex()

Vertex::Vertex(int type,float xIn, float yIn, float zIn)
{
  atomno = type; 
  x = xIn; 
  y = yIn;
  z = zIn; 
  
}//Vertex()

Vertex::Vertex(Vertex &v)
{
  x = v.x;
  y = v.y;
  z = v.z; 
  index = v.index;
  edges.clear(); 

  for(unsigned int i = 0; i<v.edges.size(); i++)
    edges.push_back(v.edges[i]);

  for(unsigned int i = 0; i<rings.size(); i++)
    rings[i].clear(); 

  for(unsigned int i = 0; i < v.rings.size(); i++)
    {
      for(unsigned int j = 0; j < v.rings[i].size(); j++)
	{
	  rings[i].push_back(v.rings[i][j]);
	}//j loop 
    }//i loop 
 
}//Vertex()

/*
  Creates an Edge between to vertices
  @param: Pointer to Vertex object 
 */
void Vertex::AddEdge(Vertex* edge)
{
  for(unsigned int i = 0; i < edges.size(); i++)
    {
      if(edges[i] == edge)
	return; 
    }

  edges.push_back(edge); 
  edge->AddEdge((Vertex*)this);
}

/*
Delete an edge by pointer to adjacent vertex
@param edges: pointer of edge to be deleted
*/
int Vertex::RemoveEdge(Vertex* edge)
{
  for(unsigned int i = 0; i < edges.size(); i++)
    {
      if(edges[i] == edge)
	{
	  Vertex* pointerToNeighbor = edges[i];
          edges.erase(edges.begin() + i);
          pointerToNeighbor->RemoveSingleEdge((Vertex*)this);
          return 0;
  
	}
    }
  return -1; 
}//RemoveEdge()

/*
  Remove edge from one list only
  @param edges: Removes a single edge
 */
int Vertex::RemoveSingleEdge(Vertex* edge)
{
  for(unsigned int i = 0; i < edges.size(); i++)
    {
      if(edges[i] == edge)
        {
          edges.erase(edges.begin() + i);
          return 0;
        }
    }
  return -1;

}//RemoveSingleEdge()
