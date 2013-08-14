//ringarea.cpp 
#include <iostream>
#include <vector>

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
  ringArea, calculated the area of of convex polygon 
 */
void ringArea(std::vector<Vertex*>  &ring)
{
  unsigned int n = ring.size() + 1; 
  float *x = new float [n];
  float *y = new float [n]; 
  float area; 

  for(unsigned int i = 0; i < ring.size(); i++)
    {
      std::cout << "x= " << ring[i]->x << " y= " << ring[i]->y << std::endl; 
      x[i] = ring[i]->x; 
      y[i] = ring[i]->y;
    }//i loop 
  
  x[n-1] = ring[0]->x; 
  y[n-1] = ring[0]->y;
  
  std::cout << "Printing from array" << std::endl; 
  
  //Calculate determinent for the area
  

  for(unsigned int i = 0; i < n; i++)
    std::cout << x[i] << " " << y[i] << std::endl; 
  
  double a=0,b=0; 

  for(unsigned int i = 0; i < n-1; i++)
    {
      a += x[i]*y[i+1];
      b += y[i]*x[i+1]; 
    }

  area = (a-b)*0.5; 

  std::cout << "Area is " << area << std::endl; 

  delete [] x; 
  delete [] y; 
   
  
}
