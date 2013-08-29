"""
Plot script for bilayer stats 
"""
import numpy as np
import matplotlib.pyplot as plt

def ringhistogram():
    y=[]

    ring = open("ringhist.dat","r")
    
    mu2 = float(ring.readline())
    type(y)
    for line in ring:
        print line 
        y.append( line.strip('\n').split()[1] )

    ring.close()
    
    ind = np.arange(8)
    y = np.array(y,dtype=int)
    width = 0.35

    fig, ax = plt.subplots()
    rects1 = ax.bar(ind+(0.35/2),y,0.35,color='r')
    ax.set_ylabel('Ring Count')
    ax.set_xlabel('Ring Size')
    ax.set_title("Ring Statistics, $\mu_{2} = $ %.2f" %(mu2)) 
    ax.set_xticks(ind+width)
    ax.set_xticklabels( ('4','5','6','7','8','9','10','11') )

    for rect in rects1:
        height = rect.get_height()
        ax.text(rect.get_x()+rect.get_width()/2., 1.025*height, '%d'%int(height),
                ha='center', va='bottom')

    plt.show()
    plt.savefig("ringhist.png")

def areahistogram():
    y=[]

    area = open("areahist.dat","r")

    mu2 = float(area.readline())
    type(y)
    for line in area:
        print line
        y.append( line.strip('\n').split()[1] )

    area.close()

    ind = np.arange(8)
    y = np.array(y,dtype=float)
    width = 0.35

    print y 
    

    fig, ax = plt.subplots()
    rects1 = ax.bar(ind+(0.35/2),y,0.35,color='b')
    ax.set_ylabel(r'$\frac{A}{<l>^{2}}$')
    ax.set_xlabel('Ring Size')
    ax.set_title(r'Area per Ring $\frac{A}{<l>^{2}} = %.2f$'%(mu2))
    ax.set_xticks(ind+width)
    ax.set_xticklabels( ('4','5','6','7','8','9','10','11') )

    for rect in rects1:
        height = rect.get_height()
        ax.text(rect.get_x()+rect.get_width()/2., 1.01*height, '%.2f'%float(height),
                ha='center', va='bottom')
    plt.show()
    plt.savefig("areahist.png")

def makenringhistogram(ringsize,ringarea,ringcount):
    
    basename="cornell_A "
    nringarea = []
    for i in range(len(ringsize)):
        if (ringsize[i] == ringcount):
            nringarea.append(ringarea[i])
    
    nringarea = np.array(nringarea)
    avg = np.mean(nringarea)
    std = np.std(nringarea)
    print "Average: %f" %avg
    print "Std: %f" %std
    hist,bins = np.histogram(nringarea,bins=50)
    print hist
    print "Sum of Hist: %f" %(np.sum(hist))
    print bins
    print bins[:-1]
    width = 0.7*(bins[1]-bins[0])
    center = (bins[:-1]+bins[1:])/2
    
    title2 = "%d rings $x= %f$;$\sigma= %f$"%(ringcount,avg,std)
    plt.title(basename + " " + title2)
    plt.bar(center,hist,align='center',width=width)
    plt.show()
    plt.savefig(basename + "_%d_ringhistogram.png"%ringcount)
    plt.clf()

def nringhistogram(nfile):
    """
    Produces a ring for a given size
    """
    ringsize = []
    ringarea = [] 
    ring = open(nfile,"r")
    
    for line in ring:
        ringsize.append( line.strip('\n').split()[0] )
        ringarea.append( line.strip('\n').split()[1] )

    ring.close()

    ringsize = np.array(ringsize,dtype=int)
    ringarea = np.array(ringarea,dtype=float)

    print ringsize
    print ringarea 

    #start making histogram

    ringcount = int(7)
    maxring = 6
    for i in range(4,12):
        makenringhistogram(ringsize,ringarea,i)

nringhistogram("cornell_A_ringdist.dat")


    
