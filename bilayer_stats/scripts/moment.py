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
    if(3 == len(sys.argv)):
        maxring=int(sys.argv[2])
    else:
        maxring=12

    countBucket=np.zeros(maxring)

    #open and read file
    infile = open(sys.argv[1],"r")
    for line in infile:
        countBucket[int(line.strip('\n').split()[0])] += 1
    infile.close()

    for i in range(len(countBucket)):
        print "i:%d countBucket[i]:%d"%(i,countBucket[i])


if __name__ == "__main__":
    main(verbose=False)
