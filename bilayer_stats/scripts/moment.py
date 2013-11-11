#!/usr/bin/env python
"""
Calculates moments of ring distribution from
the ring distribution file. 

./moment FILE NUMRING
FILE:    ._ringdist.dat FILE
NUMRING: Maximum number of rings (default=12)
"""

import sys
import numpy as np 

if len(sys.argv) < 2:
    print "Not enough input arguments"
    print __doc__
    exit()

def main(verbose=False):
    #set the max ring size
    
    for network in sys.argv[1:]:
        maxring=12
        countBucket=np.zeros(maxring)
        infile = open(network,"r")
        for line in infile:
            countBucket[int(line.strip('\n').split()[0])] += 1
        infile.close()
        
        total=countBucket.sum()
        avg=0.0 
        for i in range(len(countBucket)):
            avg += i*float(countBucket[i])/total
    
        moment0, moment1, moment2, moment3, moment4 = 0.,0.,0.,0.,0.
        for i in range(len(countBucket)):
            moment0 += countBucket[i]/total
            moment1 += (i-avg)*(countBucket[i]/total) 
            moment2 += (i-avg)*(i-avg)*(countBucket[i]/total)
            moment3 += (i-avg)*(i-avg)*(i-avg)*(countBucket[i]/total)
            moment4 += (i-avg)*(i-avg)*(i-avg)*(i-avg)*(countBucket[i]/total)

        if(verbose):
            for i in range(len(countBucket)):
                print "i:%d countBucket[i]:%d"%(i,countBucket[i])

        name=network.strip('_ringdist.dat\n').split('/')[-1]
        print "|%s| mu0:%.2f| mu1:%.2f| mu2:%.2f| mu3:%.2f| curtosis:%.2f| average:%.2f|"%(name,moment0,moment1,moment2,moment3,(moment4/moment2)-3,avg)

if __name__ == "__main__":
    main(verbose=False)
