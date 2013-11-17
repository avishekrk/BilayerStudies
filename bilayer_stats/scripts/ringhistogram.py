#!/usr/bin/env python
"""
Plot the ringhistogram graph. 

./ringhistogram.py RINGHIST AREAHIST

RINGHIST:    Ringhist file
AREAHIST:    Areahist file     
"""

import numpy as np 
import matplotlib.pyplot as plt
import sys 

ringfiles=["cornell-A_ringhist.dat","cornell-B_ringhist.dat","heyde_ringhist.dat","berlin-A_ringhist.dat","berlin-B_ringhist.dat","432b-Wilson_ringhist.dat","836-Wilson_ringhist.dat","cornell-A_wO_ringhist.dat","cAO_ringhist.dat"]
areafiles=["cornell-A_areahist.dat","cornell-B_areahist.dat","heyde_areahist.dat","berlin-A_areahist.dat","berlin-B_areahist.dat","432b-Wilson_areahist.dat","836-Wilson_areahist.dat","cornell-A_wO_areahist.dat","cAO_areahist.dat"]
titles = []
for file in ringfiles:
    titles.append( file.split('_')[0] )
 

# <codecell>

def getData(filename):
    """
    Returns a top level value (e.g. mu2 or area length) and 
    list of values 
    """
    data = []
    file = open(filename,"r")
    value = float(file.readline())
    for line in file:
        data.append( line.strip('\n').split()[1] )
    file.close()
    
    return value,data

# <codecell>



def ringareahistogram(ringfile,areafile,title):
    """
    Plot axes with shared x axes 
    """
    mu2, ring = getData(ringfile)
    area_length, area = getData(areafile)
    ringstats = np.array(ring,dtype=int)
    areastats = np.array(area,dtype=float)
    ind = np.arange(8)
    width = 0.35

  #  density = np.sum(ringstats)/(3.*area_length)
    i = 4.
    density = 0.
    print "area_length:%f"%(area_length)
    for ring in ringstats:
        print "i:%f "%i
        print "ring:%d "%ring
        density += ((i*ring)/(3.0) )
    #    print "density:%f"%(density)
        i += 1.0        
    
    print "density (before):%f" %density
    density = area_length/density
    print "density:%f"%(density)
    
        
    f, axarr = plt.subplots(3)
    rects1 = axarr[0].bar(ind+(0.35/2),ringstats,0.35,color='r')
    axarr[0].set_title("Ring Statistics, $\mu_{2} = $ %.2f" %(mu2))
    axarr[0].set_ylabel('Ring Count')
    axarr[0].set_ylim(0,250)
    axarr[0].set_xticks(ind+width)
    axarr[0].set_xticklabels( ('','','','','','','','') )
    
    rects2 = axarr[1].bar(ind+(0.35/2),areastats,0.35,color='b')
    axarr[1].set_title(r'Area per Ring $\frac{A}{<l>^{2}} = $ %.2f $\rho=$%.4f'%(area_length,density))
    axarr[1].set_ylabel(r'$\frac{A}{<l>^{2}}$')
    axarr[1].set_ylim(0,600)
    axarr[1].set_xticks(ind+width)
    axarr[1].set_xticklabels( ('','','','','','','','') )
    
    areaPerRing = (areastats/ringstats)
    areaPerRing[np.isnan(areaPerRing)] = 0 
    print "areaPerRing"
    print areaPerRing
    
    rects3 = axarr[2].bar(ind+(0.35/2),areaPerRing,0.35,color='b')
    axarr[2].set_title(r'Average Area per Ring')
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
    plt.savefig(title+"_stats.png",dpi=125)
            

# <codecell>

def ringareahistogram1(ringfile,areafile,title):
    """
    Plot axes with shared x axes 
    """
    mu2, ring = getData(ringfile)
    area_length, area = getData(areafile)
    ringstats = np.array(ring,dtype=int)
    areastats = np.array(area,dtype=float)
    ind = np.arange(8)
    width = 0.35

  #  density = np.sum(ringstats)/(3.*area_length)
    i = 8.
    density = 0.
    print "area_length:%f"%(area_length)
    for ring in ringstats:
        print "i:%f "%i
        print "ring:%d "%ring
        density += ((i*ring)/(6.0) )
    #    print "density:%f"%(density)
        i += 2.0        
    
    print "density (before):%f" %density
    density = area_length/density
    print "density:%f"%(density)
    
        
    f, axarr = plt.subplots(3)
    rects1 = axarr[0].bar(ind+(0.35/2),ringstats,0.35,color='r')
    axarr[0].set_title("Ring Statistics, $\mu_{2} = $ %.2f" %(mu2))
    axarr[0].set_ylabel('Ring Count')
    axarr[0].set_ylim(0,250)
    axarr[0].set_xticks(ind+width)
    axarr[0].set_xticklabels( ('','','','','','','','') )
    
    rects2 = axarr[1].bar(ind+(0.35/2),areastats,0.35,color='b')
    axarr[1].set_title(r'$<l>=$1.01 Area per Ring $\frac{A}{2<l>^{2}N} = $ %.2f $\rho=$%.4f'%(area_length/(2*ringstats.sum()),1/density))
    axarr[1].set_ylabel(r'$\frac{A}{<l>^{2}}$')
    axarr[1].set_ylim(0,2400)
    axarr[1].set_xticks(ind+width)
    axarr[1].set_xticklabels( ('','','','','','','','') )
    
    areaPerRing = (areastats/ringstats)
    areaPerRing[np.isnan(areaPerRing)] = 0 
    print "areaPerRing"
    print areaPerRing
    
    rects3 = axarr[2].bar(ind+(0.35/2),areaPerRing,0.35,color='b')
    axarr[2].set_title(r'Average Area per Ring')
    axarr[2].set_ylabel(r'$\frac{A}{<l>^{2}N_{r}}$')
    axarr[2].set_ylim(0,40)
    axarr[2].set_xticks(ind+width)
    axarr[2].set_xticklabels( ('8','10','12','14','16','18','20','22') )
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

    #print title
    plt.show()
    plt.savefig(title+"_stats.png",dpi=125)
    #plt.clf()

# <codecell>

#ringareahistogram1(ringfiles[-1],areafiles[-1],titles[-1])

def main():
    ringareahistogram(sys.argv[1],sys.argv[2],"cornell-A")

if __name__ == "__main__":
    main()






