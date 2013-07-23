#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
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
  in = fopen(file,"r");
  if(in == NULL)
    {
      std::cerr << "Cannot open file: " << file << std::endl; 
      exit(1);
    }
  fscanf(in, "%d", &numatoms);
  printf("Number of Atoms: %d\n",numatoms);
  fscanf(in, "%s\n",&buffer);
  printf("%s\n",buffer);
  while(4 == fscanf(in,"%s %f %f %f\n",&atom,&x,&y,&z) )
    {
      printf("%s %f %f %f\n",atom,x,y,z); 
    }
  fclose(in);
}//read_xyz()

int main(int argc, char *argv[])
{
  
  if ( argc < 2 )
    {
      std::cerr << "Not enough input arguments: " << argc << std::endl; 
      exit(1);  
    }

  read_xyz(argv[1]); 

  std::cout<< "Hello Wold" << std::endl; 
  return 0; 
}
