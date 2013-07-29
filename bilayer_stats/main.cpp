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
std::vector<std::vector<Vertex*> > allCycles;
std::vector<std::vector<Vertex*> > tempCycles;
int countBucket[12];
std::vector<std::vector<int> > stack; 

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
void connectAtoms(Graph &bilayer,float dist,int Debug=0)
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
	    bilayer.vertices[i]->AddEdge(bilayer.vertices[j]); 
	    

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

void fillCountBucket(int countBucket[], std::vector <std::vector<Vertex*> > &allCycles)
{
  std::vector <int> list;
  for(unsigned int i =0; i<12; i++) countBucket[i] =0;
  for(unsigned int i =0; i<allCycles.size(); i++) countBucket[allCycles[i].size()]++;
  for(unsigned int i =0; i<12; i++) list.push_back(countBucket[i]);
  
  stack.push_back(list);
  list.clear();
  
  // std::cout << "Rings Statistics" << std::endl;                                                                                                                                                                                                                                
  // for(int i =0; i < 12; i++) std::cout << i << " rings: " << countBucket[i] << std::endl;                                                                                                                                                                                      
  int ring_sum =0;
  for(int i =0; i < 12; i++) { ring_sum += i*countBucket[i];}
  int sum =0;
  for(int i = 0; i < 12; i++){sum += countBucket[i];}
  //std::cout << "RING SUM " << ring_sum << std::endl;                                                                                                                                                                                                                            
  //std::cout << "SUM " << sum << std::endl;                                                                                                                                                                                                                                      
  double average = (double) ring_sum/sum;
  //std::cout << "AVERAGE " << average << std::endl;                                                                                                                                                                                                                                
  FILE* count;
  
  count = fopen( "countBucket.dat", "w");
  fprintf(count, "Ring Statistics\n");
  for(int i =0; i < 12; i++) fprintf(count, "%d RINGS: %d\n", i, countBucket[i]);
  fprintf(count, "RING SUM: %d\n",ring_sum);
  fprintf(count, "SUM: %d\n", sum);
  fprintf(count, "AVERAGE: %f\n",average);
  fprintf(count, "\n");
  fclose(count);

}//fillCountBucket()

/*Outputs Rings*/
void cycleDump(std::vector <std::vector<Vertex*> > &allCycles)
{
  FILE* cycle;
  cycle = fopen("cycleList.dat" ,"w");


  for(int i = 0; i<12; i++)
    {
      fprintf(cycle,"\n");
      fprintf(cycle, "RING SIZE %d\n" , i);
      for(int j =0; j < allCycles.size(); j++)
        {
	  std::vector <Vertex*> Ring = allCycles[j];
          if(Ring.size() != i) continue;
          for(int k =0; k<Ring.size(); k++) fprintf(cycle, "Circle[{%f,%f},0.2],\n",Ring[k]->x,Ring[k]->y);
          fprintf(cycle,"\n");
        }
      fprintf(cycle, "\n");
    }

  fclose(cycle);
}//cycleDump()



int main(int argc, char *argv[])
{
  
  if ( argc < 2 )
    {
      std::cerr << "Not enough input arguments: " << argc << std::endl; 
      exit(1);  
    }
  
  
  
  read_xyz(argv[1],bilayer);
  connectAtoms(bilayer,2.1);

  bilayer.vertices[969]->AddEdge(bilayer.vertices[967]); 
  std::cout << bilayer.vertices[969]->x << " " << bilayer.vertices[969]->y << " " << bilayer.vertices[969]->z << std::endl; 
  std::cout << bilayer.vertices[967]->x << " " << bilayer.vertices[967]->y << " " << bilayer.vertices[967]->z << std::endl; 
  MakeHoney(bilayer,"honeycomb1.m"); 
  std::cout << bilayer.vertices[705]->x << " " << bilayer.vertices[705]->y << " " << bilayer.vertices[705]->z << std::endl;
  //start counting cycles 
  bilayer.vertices[705]->CountCyclesLocally(allCycles); 
  bilayer.FirstSort(allCycles); 
  
  fillCountBucket(countBucket,allCycles); 

  for(unsigned int i = 0; i < allCycles.size(); i++)
    {
      std::cout << "RING " << i+1 << std::endl; 
      for(unsigned int j = 0; j < allCycles[i].size(); j++)
	{
	  std::cout << allCycles[i][j]->x << " " << allCycles[i][j]->y << " " << allCycles[i][j]->z << std::endl; 
	}
    }
  cycleDump(allCycles);


  return 0; 
}//main()
