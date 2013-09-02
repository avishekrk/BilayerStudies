//aboav.cpp 
void aboavDiagnostic(std::vector<Vertex*> &iCycle, std::vector<vector <Vertex*> > &pairs, std::vector<vector<Vertex*> > &rings)
{
  FILE* out; 
  out = fopen("aboavDiagnostic.dat","w"); 
  fprintf(out, "#Ring Coordinates\n"); 
  for(unsigned int i =0; i < iCycle.size(); i++)
    {
      fprintf(out, "{%f,%f}\n", iCycle[i]->getX(), iCycle[i]->getY()); 
    }

  fprintf(out, "\n#RingConnections\n");
  for(unsigned int i =0; i < iCycle.size(); i++)
    {
      fprintf(out, "#Ring {%f,%f}\n",iCycle[i]->getX(), iCycle[i]->getY());
      for(unsigned int j =0; j < iCycle[i]->edges.size(); j++)
	{
	  fprintf(out, "{%f,%f}\n",iCycle[i]->edges[j]->getX(), iCycle[i]->edges[j]->getY());
	}
      fprintf(out, "\n"); 
    }
  
      fprintf(out, "\n#Pairs\n"); 
  for(unsigned int i =0; i < pairs.size(); i++)
    {

      fprintf(out, "{%f,%f} {%f,%f}\n", pairs[i][0]->getX(), pairs[i][0]->getY(), pairs[i][1]->getX(), pairs[i][1]->getY()); 
    }
  fprintf(out, "\n#SideRings\n"); 
  for(unsigned int i =0; i < rings.size(); i++)
    {
      for(unsigned int j =0; j < rings[i].size(); j++)
	{
	  fprintf(out, "{%f,%f}\n",rings[i][j]->getX(), rings[i][j]->getY());  
	}
      fprintf(out,"\n"); 
    }
  fclose(out); 
}

/**
   finds the rings that are around a particular cycle 
   @param pairs the edges 
   @param iCycle the Cycle that you are trying to find the
   edges around 
   @return sideRings with the correlated rings 
*/

std::vector <vector <Vertex*> > sideRings(std::vector <vector <Vertex*> > &pairs, std::vector <Vertex*> &iCycle)
{
  std::vector <vector <Vertex*> > list; 
  list.clear(); 
  bool foundiCycle= false; 
  for(unsigned int i =0; i < pairs.size(); i++)
    {
      for(unsigned int j =0; j < pairs[i][0]->rings.size(); j++)
	{
	  for(unsigned int k =0; k < pairs[i][0]->rings[j].size(); k++)
	    {
	      if(pairs[i][1] == pairs[i][0]->rings[j][k])
		{
		  if(iCycle == pairs[i][0]->rings[j])
		    {
		      break;  
		    }
		  else
		    {
		      list.push_back(pairs[i][0]->rings[j]); 
		      break; 
		    }
		}
	    }//k loop 
	}// j loop 
    }//i loop 
  return list; 
}

/**
   Calculates the local Aboav average 
   @param rings contains all the correlated rings 
   @return average is the average of the neighboring 
   rings 
 */
double aboavAverage(std::vector <std::vector<Vertex*> > &rings)
{
  double sum;  
  for(unsigned int i =0; i < rings.size(); i++)
    {
      sum+=rings[i].size(); 
    }
  return sum/rings.size(); 
}
/**
   Fill the Aboav Bucket 
   @param average value of the neighboring rings 
   @param iCycle the size of the ring 
 */
void fillAboavBucket(int aboavBucket[], double &average, std::vector<Vertex*> &iCycle)
{
  std::vector <int> list; 
  for(unsigned int i =0; i < 12; i++) aboavBucket[i]=0; 
  aboavBucket[iCycle.size()]= average; 
  for(unsigned int i =0; i < 12; i++) list.push_back(aboavBucket[i]); 
  aboavStack.push_back(list); 
  list.clear(); 
}
/**
 Calculate the global Aboav function and output into a file 
 @param aboavStack has neighboring rings averages
 @return vector containing the aboav function 
*/
std::vector <double> globalAboav()
{
  std::vector <double> aboavfunction; 
  for(unsigned int i =0; i < 12; i++) aboavfunction.push_back(0); 
    
  double sum, counter;  
  for(unsigned int i =0; i < aboavStack[0].size(); i++)
    {
      sum = 0; 
      counter =0; 
      for(unsigned int j =0; j < aboavStack.size(); j++)
	{
	  if(aboavStack[j][i] != 0)
	    {
	      sum += aboavStack[j][i]; 
	      counter++; 
	    }
	}//j loop 
      if(counter == 0)
	{
	  aboavfunction[i] =0; 
	}
      else
	{
	  aboavfunction[i] = sum/counter; 
	}
      
    }//i loop
  return aboavfunction; 
}

/**
 AboavStack Dump into a file 
 @param aboavStack contains all the info 
 */
void AboavStackDump()
{
  FILE* out; 
  out = fopen("AboavStack.dat","w"); 
  for(unsigned int i =0; i < aboavStack.size(); i++)
    {
      for(unsigned int j =0; j < aboavStack[i].size(); j++)
	{
	  fprintf(out, "%f ",aboavStack[i][j]); 
	}
      fprintf(out,"\n"); 
    }
  fclose(out); 
}

/**
   Calculates the Aboav function 
 */
void Aboav()
{
  double average, value;  
  std::vector <Vertex*> iCycle; 
  std::vector <vector <Vertex*> > pairs; 
  std::vector <std::vector <Vertex*> > rings; 
  for(unsigned int i =0; i < allCycles.size(); i++)
    {
       iCycle = allCycles[i]; 
       pairs =findEdges(iCycle); 
      //Now find the other rings in the pairs 
       rings =sideRings(pairs, iCycle); 
      aboavDiagnostic(iCycle, pairs, rings); 
      //Calculate Average 
      average = aboavAverage(rings);
      fillAboavBucket(aboavBucket, average, iCycle);
      iCycle.clear(); 
      pairs.clear(); 
      rings.clear(); 
     }
  std::vector <double> aboavfunction = globalAboav(); 
  AboavStackDump(); 
  
  for(unsigned int i =0; i < aboavfunction.size(); i++)
    {
      std::cout << i << "   " <<  aboavfunction[i]  << std::endl; 
    }
 
  FILE* ringAvg; 
  ringAvg = fopen("ABOAV.dat","w"); 
  for(unsigned int i =0; i < aboavfunction.size(); i++)
    {
      fprintf(ringAvg, "%d  %f\n", i, aboavfunction[i]); 
    }
  fclose(ringAvg); 
}
