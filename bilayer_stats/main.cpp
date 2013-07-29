#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "vertex.h"
#include "graph.h"


//global variables 
Graph bilayer; 

/*
  read_xyz: reads a file in the xyz format 
  @param: file, xyz file 
*/
void read_xyz(char *file, Graph &bilayer)
{
  int numatoms;
  char buffer[3],atom[2];
  float x,y,z;
  FILE *in; 
  in = fopen(file,"r");
  if(in == NULL)
    {
      std::cerr << "Cannot open file: " << file << std::endl; 
      exit(1);
    }
  fscanf(in, "%d", &numatoms);
  printf("%d\n",numatoms);
  fscanf(in, "%s\n",&buffer);
  printf("%s\n",buffer);
  while(4 == fscanf(in,"%s %f %f %f\n",&atom,&x,&y,&z) )
    {
      printf("%s %.15f %.15f %.15f\n",atom,x,y,z);
      if (atom[0] == 'O')
	{
	  continue; 
	}
      else
	{
	  Vertex* pos = new Vertex(14,x,y,z); 
	  bilayer.vertices.push_back(pos); 
	  std::cout << bilayer.vertices.size() << std::endl; 
	}
      
    }
  fclose(in);
  
  for(unsigned int i = 0; i < bilayer.vertices.size(); i++)
    {
      bilayer.vertices[i]->index = i; 
    }


}//read_xyz()


/*
  Connect atoms within a certain distance 
 */
void connectatoms(Graph &bilayer,float dist,int Debug=0)
{
  
  for(unsigned int i = 0; i < bilayer.vertices.size(); i++)
    {
      for(unsigned int j = i+1; j < bilayer.vertices.size(); j++)
	{
	  float x_ij = bilayer.vertices[i]->x - bilayer.vertices[j]->x; 
	  float y_ij = bilayer.vertices[i]->y - bilayer.vertices[j]->y;
	  float z_ij = bilayer.vertices[i]->z - bilayer.vertices[j]->z;
	  float r = sqrt( x_ij*x_ij + y_ij*y_ij + z_ij*z_ij ); 
	  
	  if(Debug)
	    {
	      std::cout << "Vertex: " << i << " " << bilayer.vertices[i]->x << " " << bilayer.vertices[i]->y << " " << bilayer.vertices[i]->z << std::endl; 
	      std::cout << "Vertex: " << j << " " << bilayer.vertices[j]->x << " " << bilayer.vertices[j]->y << " " << bilayer.vertices[j]->z << std::endl; 
	      std::cout << "x_ij " << x_ij << std::endl; 
	      std::cout << "y_ij " << y_ij << std::endl; 
	      std::cout << "z_ij " << z_ij << std::endl; 
	      std::cout << "r: " << r << std::endl; 
	  
		
	    }
	  if(r > 0.0 && r < dist)
	    {
	      std::cout << "Match" << std::endl; 
	      bilayer.vertices[i]->AddEdge(bilayer.vertices[j]); 
	    }

	}//j loop 
    }//i loop
}//connectatoms

void MakeHoney(Graph& bilayer, char *nfile)
{
  FILE *outFile; 
  outFile = fopen(nfile , "w");
  fprintf(outFile, "Graphics[{Black");


  for(unsigned int j =0; j < bilayer.vertices.size(); j++)
    {
      for(unsigned int i =0; i < bilayer.vertices[j]->edges.size(); i++)
        {
          
	  fprintf(outFile, ", \nLine[{{%f,%f},{%f,%f}}]", bilayer.vertices[j]->x,
		  bilayer.vertices[j]->y,
		  bilayer.vertices[j]->edges[i]->x,
		  bilayer.vertices[j]->edges[i]->y);
	  
        }
    }

  fprintf(outFile, "\n}]");
  fclose(outFile);
}


int main(int argc, char *argv[])
{
  
  if ( argc < 2 )
    {
      std::cerr << "Not enough input arguments: " << argc << std::endl; 
      exit(1);  
    }

  
  read_xyz(argv[1],bilayer);
  connectatoms(bilayer,2.1);
  MakeHoney(bilayer,"honeycomb.m"); 

  return 0; 
}//main()
