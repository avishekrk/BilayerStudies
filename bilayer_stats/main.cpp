#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

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
	  Vertex* pos = new Vertex(8,x,y,z); 
	  bilayer.vertices.push_back(pos); 
	  std::cout<< bilayer.vertices.size() << std::endl; 
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

void connectatoms(Graph &bilayer,int atomno1, int atomno2)
{
  for(unsigned int i = 0; i < bilayer.vertices.size(); i++)
    {
      std::cout << "Atomic Number: " << bilayer.vertices[i]->atomno << std::endl; 
      if(bilayer.vertices[i]->atomno == 8)
	{
	  std::cout << bilayer.vertices[i]->x << " " << bilayer.vertices[i]->y << " " << bilayer.vertices[i]->z << std::endl; 
	}
    }
}//connectatoms

int main(int argc, char *argv[])
{
  
  if ( argc < 2 )
    {
      std::cerr << "Not enough input arguments: " << argc << std::endl; 
      exit(1);  
    }

  
  read_xyz(argv[1],bilayer);
  connectatoms(bilayer,8,14);

  return 0; 
}//main()
