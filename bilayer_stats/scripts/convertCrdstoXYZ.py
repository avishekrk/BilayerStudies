#!/usr/bin/env python
"""
Converts Mark Wilson's crds to xyz format 

./convertCrdstoXYZ FILE NUMO NUMSI
FILE:    .crds FILE
NUMO:    Number of Oxygens
NUMSI    Number of Silicons 
"""

import sys
import numpy as np 

if len(sys.argv) < 4:
    print "Not enough input arguments"
    print __doc__
    exit()

def main(verbose=False):
    
    #get basename of file
    basename = sys.argv[1].split("/")[-1].split('.')[0]
    numo = int(sys.argv[2])
    numsi = int(sys.argv[3])

    if(verbose):
        print "Basename: %s"%(basename) 

    coordinates = []
    infile = open(sys.argv[1],"r")
    for line in infile:
        coordinates.append(line.strip('\n').split())
    infile.close()
    coordinates = np.array(coordinates,dtype=float)

    assert len(coordinates) == numo + numsi, "Number of oxygens: %d and silicons: %d do not match"%(numo,numsi)

    
    #output into xyz format using numoxygens and numsilicons
    infile = open(basename+".xyz","w")
    infile.write("%d\n"%len(coordinates))
    infile.write("%s\n"%(basename))
    for line in coordinates[:numo]:
        infile.write("O ")
        infile.write("%f %f %f\n"%(line[0],line[1],line[2]))
    for line in coordinates[numo:]:
        infile.write("Si ")
        infile.write("%f %f %f\n"%(line[0],line[1],line[2]))
    infile.close()

if __name__ == "__main__":
    main(verbose=False)
