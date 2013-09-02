"""
Plot script for bilayer stats 
"""
import numpy as np
import matplotlib.pyplot as plt

def ringhistogram():
    """
    Create ringhistogram
    """
    y=[]

    ring = open("ringhist.dat","r")
    
    mu2 = float(ring.readline())
    for line in ring:
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
    
    for i in range(4,12):
        makenringhistogram(ringsize,ringarea,i)

#nringhistogram("cornell_A_ringdist.dat")


    
def ringareahistogram():
    """
    Plot axes with shared x axes 
    """
    
    ringstats = []
    ring = open("ringhist.dat","r")
    mu2 = float(ring.readline())
    for line in ring:
        ringstats.append( line.strip('\n').split()[1] )
    ring.close()
    
    areastats = [] 
    area = open("areahist.dat","r")
    area_length = float(area.readline())
    for line in area:
        print line
        areastats.append( line.strip('\n').split()[1] )
    area.close()

    ind = np.arange(8)
    ringstats = np.array(ringstats,dtype=int)
    areastats = np.array(areastats,dtype=float)
    width = 0.35

    f, axarr = plt.subplots(3)
    rects1 = axarr[0].bar(ind+(0.35/2),ringstats,0.35,color='r')
    axarr[0].set_title("Ring Statistics, $\mu_{2} = $ %.2f" %(mu2))
    axarr[0].set_ylabel('Ring Count')
    axarr[0].set_ylim(0,250)
    axarr[0].set_xticks(ind+width)
    axarr[0].set_xticklabels( ('','','','','','','','') )
    rects2 = axarr[1].bar(ind+(0.35/2),areastats,0.35,color='b')
    axarr[1].set_title(r'Area per Ring $\frac{A}{<l>^{2}} = $ %.2f'%(area_length))
    axarr[1].set_ylabel(r'$\frac{A}{<l>^{2}}$')
    axarr[1].set_ylim(0,600)
    
    axarr[1].set_xticks(ind+width)
    axarr[1].set_xticklabels( ('','','','','','','','') )
    areaPerRing = (areastats/ringstats)
    areaPerRing[np.isnan(areaPerRing)] = 0 
    print "areaPerRing"
    print areaPerRing
    rects3 = axarr[2].bar(ind+(0.35/2),areaPerRing,0.35,color='b')
    axarr[2].set_title('Average Area per Ring')
    axarr[2].set_ylabel(r'$\frac{A}{<l>^{2}N_{r}}$')
    axarr[2].set_ylim(0,10)
    axarr[2].set_xticks(ind+width)
    axarr[2].set_xticklabels( ('4','5','6','7','8','9','10','11') )
    axarr[2].set_xlabel('Ring Size')

    for rect in rects1:
        height = rect.get_height()
        axarr[0].text(rect.get_x()+rect.get_width()/2., 1.025*height, '%d'%int(height),
                    ha='center', va='bottom')

    for rect in rects2:
        height = rect.get_height()
        axarr[1].text(rect.get_x()+rect.get_width()/2., 1.025*height, '%.2f'%float(height),
                      ha='center', va='bottom')


    for rect in rects3:
        height = rect.get_height()
        axarr[2].text(rect.get_x()+rect.get_width()/2., 1.025*height, '%.2f'%float(height),
                      ha='center', va='bottom')

    
    plt.show()
    plt.savefig("cornell_A_stats.png")
    plt.clf()
    
    #Lewis Plot
    plt.plot(range(4,12),areaPerRing,'ko')
    plt.title("Lewis's Law Cornell A Sample")
    plt.xlabel("Ring Size, $r$")
    plt.ylabel(r'Average Area,$\frac{ A_{r} }{ <l>^{2} }$')
    plt.show()
    plt.savefig("cornell_A_LewisLaw.png")           


def nringarea(ringsize,ringarea,ring):
    nringarea = []
    
    for i in range(len(ringsize)):
        if( ringsize[i] == ring ):
            nringarea.append(ringarea[i])

    return np.array(nringarea)

def plotareahists(): 
    
    #open the file 
    ringsize = []
    ringarea = []
    ring = open("cornell_A_ringdist.dat","r")
    
    for line in ring:
        ringsize.append( line.strip('\n').split()[0] )
        ringarea.append( line.strip('\n').split()[1] )

    ring.close()

    ringsize = np.array(ringsize,dtype=int)
    ringarea = np.array(ringarea,dtype=float)

    ring = 4
    
    f, axarr = plt.subplots(2,3)
    for i in range(3):
        for j in range(3):
            if ring > 9:
                break 
            print "%d %d"%(j,i)
            dist = nringarea(ringsize,ringarea,ring)
            avg = np.mean(dist)
            std = np.std(dist)
            hist,bins = np.histogram(dist,bins=50)
            width = 0.7*(bins[1]-bins[0])
            center = (bins[:-1]+bins[1:])/2
            axarr[i,j].bar(center,hist,align='center',width=width)
            axarr[i,j].set_title('Cornell A %d Ring $x =$ %f; $\sigma =$ %f'%(ring,avg,std))
            ring += 1 
        
    #f.tight_layout()
    plt.show()
    plt.savefig("cornellA_ringhist.png")
