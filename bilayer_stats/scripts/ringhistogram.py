#!/usr/bin/env python
"""
Plot the ringhistogram graph. 

./ringhistogram.py RINGHIST AREAHIST BONDLENGTH

RINGHIST:    Ringhist file
AREAHIST:    Areahist file     
BONDLENGTH:  Bondlengths 

"""

import numpy as np 
import matplotlib.pyplot as plt
import sys 



def getData(filename):
    """
    Returns a top level value (e.g. mu2 or area length) and 
    list of values 
    """
    data = []
    ring = []
    file = open(filename,"r")
    value = float(file.readline())
    for line in file:
        ring.append( line.strip('\n').split()[0] )
        data.append( line.strip('\n').split()[1] )
    file.close()
    
    return value,data,ring



def ringareahistogram(ringfile,areafile,title):
    """
    Plot axes with shared x axes 
    """
    mu2, ring, xring = getData(ringfile)
    area_length, area, xarea = getData(areafile)
    ringstats = np.array(ring,dtype=int)
    areastats = np.array(area,dtype=float)
    ind = np.arange(8)
    width = 0.35

    xarea = np.array(xarea,dtype=int)
    newdensity = np.sum(xarea*ringstats)/3.0
    newdensity = area_length/newdensity

            
    f, axarr = plt.subplots(3)
    rects1 = axarr[0].bar(ind+(0.35/2),ringstats,0.35,color='r')
    axarr[0].set_title("Ring Statistics, $\mu_{2} = $ %.2f" %(mu2))
    axarr[0].set_ylabel('Ring Count')
    axarr[0].set_ylim(0,ringstats.max()+200)
    axarr[0].set_xticks(ind+width)
    axarr[0].set_xticklabels( ('','','','','','','','') )
    
    rects2 = axarr[1].bar(ind+(0.35/2),areastats,0.35,color='b')
    print "newdesnity",newdensity 
    if(xarea[0] == 8):
        print "Big Rings"
        axarr[1].set_title(r'$<l>_{proj}$=1.01 \pm 0.012 \rho = %.4f$'%(1/(2*newdensity)))
    else:
        axarr[1].set_title(r'$<l>_{proj}$=1.99 $\pm$ 0.043 $\rho =$%.4f'%(1/newdensity))
    axarr[1].set_ylabel(r'$\frac{A}{<l>^{2}}$')
    axarr[1].set_ylim(0,areastats.max()+400)
    axarr[1].set_xticks(ind+width)
    axarr[1].set_xticklabels( ('','','','','','','','') )
    
    areaPerRing = (areastats/ringstats)
    areaPerRing[np.isnan(areaPerRing)] = 0 
    rects3 = axarr[2].bar(ind+(0.35/2),areaPerRing,0.35,color='b')

    if(xarea[0] == 8):
        print "Big Rings"
        axarr[2].set_title(r'Area per Ring $\frac{A}{2N<l>^{2}} = $ %.2f '%(area_length/(2*np.sum(ringstats))))
    else:
        axarr[2].set_title(r'Area per Ring $\frac{A}{2N<l>^{2}} = $ %.2f'%(area_length/(2*np.sum(ringstats))))
    axarr[2].set_ylabel(r'$\frac{A}{<l>^{2}N_{r}}$')
    axarr[2].set_ylim(0,areaPerRing.max()+10)
    axarr[2].set_xticks(ind+width)
    axarr[2].set_xticklabels( xring )
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

 
    plt.savefig(title+"_stats.png",dpi=125)
    print "Figure saved to %s_stats.png"%title


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
    ringfile=sys.argv[1]
    areafile=sys.argv[1]
    title=sys.argv[1].split('_')[0]
    ringareahistogram(sys.argv[1],sys.argv[2],title)

if __name__ == "__main__" and len(sys.argv) == 3:
    main()
else:
    print "Not enough input arguements: %d"%(len(sys.argv))
    print __doc__






