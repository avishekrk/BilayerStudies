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
