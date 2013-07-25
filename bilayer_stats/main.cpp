#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

#include "graph.h"

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
      Vertex* pos = new Vertex(x,y,z); 
      list.push_back(pos); 
    }
  fclose(in);
  
  for(unsigned int i = 0; i < list.size(); i++)
    std::cout << list[i]->x << " " << list[i]->y << " " << list[i]->z << std::endl; 


}//read_xyz()

int main(int argc, char *argv[])
{
  
  if ( argc < 2 )
    {
      std::cerr << "Not enough input arguments: " << argc << std::endl; 
      exit(1);  
    }

  read_xyz(argv[1]); 
  Vertex v(4.0,23.5,0.0); 
  std::cout << v.type << " " << v.x << " " << v.y << " " << v.z << std::endl; 
  

  return 0; 
}
