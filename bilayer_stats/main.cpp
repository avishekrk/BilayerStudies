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
void read_xyz(char *file)
{
  int numatoms;
  char buffer[3],atom[2];
  float x,y,z;
  FILE *in; 
  std::vector<Vertex*> list; 
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
      if (atom[0] == 'C')
	{
	  Vertex* pos = new Vertex(4,x,y,z); 
	  list.push_back(pos); 
	  
	}
      else
	{
	  Vertex* pos = new Vertex(14,x,y,z); 
	  list.push_back(pos); 
	}
      
    }
  fclose(in);
  
  for(unsigned int i = 0; i < list.size(); i++)
    std::cout << list[i]->atomno << " " << list[i]->x << " " << list[i]->y << " " << list[i]->z << std::endl; 


}//read_xyz()

int main(int argc, char *argv[])
{
  
  if ( argc < 2 )
    {
      std::cerr << "Not enough input arguments: " << argc << std::endl; 
      exit(1);  
    }

  
  read_xyz(argv[1]); 
    

  return 0; 
}//main()
