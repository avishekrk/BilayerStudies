# -*- coding: utf-8 -*-
# <nbformat>3.0</nbformat>

# <headingcell level=1>

# For Plotting the Aboav Function

# <codecell>

def PlotAboav():
    file = open("ABOAV.dat","r")
    ringsize = []
    aring = []

     
    
    for line in file:
        ringsize.append(line.strip('\n').split()[0])
        aring.append(line.strip('\n').split()[1])
    
    ringsize = np.array(ringsize,dtype=int)
    aring = np.array(aring,dtype=float)
    print ringsize      
    print aring 
    
    print ringsize*aring
    
    plt.plot(ringsize[3:11],aring[3:11],'ro')
    plt.xlabel('ring size,$r$')
    plt.ylabel('Average Ring Size, $m_{n}$')
    plt.xlim(3.5,10.5)
    plt.ylim(4,8)
    plt.title('Cornell_A Aboav Function')
    plt.savefig('Cornell_A_Aboav.png')

# <codecell>

PlotAboav()

# <headingcell level=1>

# $\sin(x)$

# <codecell>


