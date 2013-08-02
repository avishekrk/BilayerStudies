#!/usr/bin/env python 
"""
Creates a network of corner sharing triangles. 

corner_triangles.py CORD CONNECT 

CORD    :a-G coordinates file 
CONNECT :a-G connectivity table 
"""

import sys  
if len(sys.argv) != 3:
    print __doc__
    exit()

import numpy as np

def read(filename,Debug=False):
    """
    read, reads the a-G files, skipping any line 
                    that starts with #
    parameters,
       filename, string of input file name
       Debug, bool for verbose output 
    return, 
        coordinates, a list  
    """
    coordinates=[]
    with open(filename,"r") as cords:
        for cord in cords:
            if cord.startswith("#"):
                continue
            else:
                if(Debug):
                    print cord.strip('\n').split()[:]
                coordinates.append(cord.split()[:])

    return coordinates 

def print_atom(coordinates,atom="C"):
    """
    print atom
        print to stdout in x y z format
    parameters
        coordinates, a (N,2) numpy array of coordinates 
        atom, string for the atom type default is carbon  
    """
    for cord in coordinates:
        print "%s %f %f 0.00000" %(atom,cord[0],cord[1])


def main(Debug=False):
    
    coordfile = sys.argv[1]
    connectfile = sys.argv[2]
    #lattice vectors 
    a=np.array([38.34,0])
    b=np.array([0.,29.5141])

    coordinates = np.array(read(coordfile),dtype=float)
    connect = np.array(read(connectfile),dtype=int)
    
    #ouput connections
    midpoints=[]
    for i in range(0,len(connect)):
        vertex = connect[i][0]
        for j in range(1,len(connect[i])):
            repeat = False
            atomj = connect[i][j]
            rij = coordinates[vertex] + coordinates[atomj]
            if(Debug):
                print coordinates[vertex]
                print coordinates[atomj]
            rij = coordinates[vertex] - coordinates[atomj]
            ghost = coordinates[atomj]
            if rij[0] > a[0]/2.:
                ghost = ghost - a
            if rij[0] < -(a[0]/2.):
                ghost = ghost + a
            if rij[1] > b[1]/2.:
                ghost = ghost - b
            if rij[1] < -(b[1]/2):
                ghost = ghost + b 
            midpoint = 0.5*(coordinates[vertex] + ghost)
            
            for mid in midpoints:
                if all(midpoint == mid):
                    repeat = True
                    break 
            if(repeat):
                continue
            else:
                midpoints.append(midpoint)
            

    numatom = len(coordinates) + len(midpoints)
    print numatom
    print "a 38.34 0. ",
    print "b 0. 29.5141"
    print_atom(coordinates)
    print_atom(midpoints,"O")
        


if __name__ == "__main__":
    main(Debug=False)
