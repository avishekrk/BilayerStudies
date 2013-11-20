# -*- coding: utf-8 -*-
# <nbformat>3.0</nbformat>

# <headingcell level=1>

# Lewis's Law Plots

# <codecell>

import numpy as np 
import matplotlib.pyplot as plt
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

def LewisPlot(ringfile,areafile,title,r_0=3.5):
        mu2, ring = getData(ringfile)
        area_length, area = getData(areafile)
        ring = np.array(ring,dtype=int)
        area = np.array(area,dtype=float)
        area_ring = (area/ring)
        area_ring[np.isnan(area_ring)] = 0 
        print ring
        totalarea = np.sum(area)
        totalring = 0. 
        ringsize = 4.
        for nring in ring:
            totalring += ringsize*nring
            ringsize +=1
        totalring = (totalring/3.)
           
        Lewis =[]
        
        
        for i in range(4,12): 
            Lewis.append( (2*totalarea/totalring)*((i-r_0)/(6-r_0)) )
        
        np.array(Lewis,dtype=float)
        print "Lewis:"
        print Lewis
        print "area: "
        print area 
          
        plt.plot(range(len(area_ring),area_ring,'ro')   
        #plt.plot(range(4,12),area_ring,'ro')
        #plt.plot(6,(2*totalarea/totalring),'ko')
        #plt.plot(range(4,12),Lewis, 'b')
        plt.xlabel('Ring Size $r$')
        plt.ylabel(r'Average Area per Ring $\frac{A_{r}}{<l>^{2}}$')
        #plt.xlim(3.5,10.5)
        #plt.legend([title,"2a",'Lewis $r_{o}$=%.2f'%r_0],loc=2)
        plt.title(title + " Lewis's Law")
        
        #Linear fit 
        #plt.show()       
        plt.savefig(title+"_lewis.png",dpi=125)
        plt.show()
        #plt.clf()
        
    

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

    #print title
    #plt.show()
    plt.savefig(title+"_stats.png",dpi=125)
    #plt.clf()
        

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
    #plt.show()
    plt.savefig(title+"_stats.png",dpi=125)
    #plt.clf()

# <codecell>

ringareahistogram1(ringfiles[-1],areafiles[-1],titles[-1])

# <codecell>

LewisPlot(ringfiles[-1],areafiles[-1],titles[-1],r_0=3.610)

# <headingcell level=2>

# All Data on a Single Plot

# <codecell>

def LewisPlots(ringfiles,areafiles,titles):
    for i in range(len(ringfiles)-2):
        mu2, ring = getData(ringfiles[i])
        area_length, area = getData(areafiles[i])
        ring = np.array(ring,dtype=int)
        area = np.array(area,dtype=float)
        area_ring = (area/ring)
        area_ring[np.isnan(area_ring)] = 0 
        plt.plot(range(4,12),area_ring,'+')
    
    for i in [int(5),int(6)]:
        mu2, ring = getData(ringfiles[i])
        area_length, area = getData(areafiles[i])
        ring = np.array(ring,dtype=int)
        area = np.array(area,dtype=float)
        area_ring = (area/ring)
        area_ring[np.isnan(area_ring)] = 0 
        plt.plot(range(4,12),area_ring,'x')
    
    x = np.array(range(4,11),dtype=float)
    y = (x)/(4*np.tan(np.pi/x)
    plt.plot(x,y)
    plt.xlim(3.7,10.3)
    plt.xlabel('Ring size $r$')
    plt.ylabel(r'Average area per ring')
    plt.title("Lewis's Law")
    legend(titles,loc=4,fontsize='small')
    plt.savefig("lewis.png",dpi=125)
    #plt.show()
    #plt.clf()
LewisPlots(ringfiles,areafiles,titles)

# <codecell>

def LewisPlots2(ringfiles,areafiles,titles):
    for i in range(len(ringfiles)-2):
        mu2, ring = getData(ringfiles[i])
        area_length, area = getData(areafiles[i])
        ring = np.array(ring,dtype=int)
        area = np.array(area,dtype=float)
        area_ring = (area/ring)
        area_ring[np.isnan(area_ring)] = 0 
        plt.plot(range(4,12),area_ring,'+')
    for i in [int(5),int(6)]:
        mu2, ring = getData(ringfiles[i])
        area_length, area = getData(areafiles[i])
        ring = np.array(ring,dtype=int)
        area = np.array(area,dtype=float)
        area_ring = (area/ring)
        area_ring[np.isnan(area_ring)] = 0 
        if(5 == i):
            plt.plot(range(4,12),area_ring,'x',color='red')
        else:
            plt.plot(range(4,12),area_ring,'x')
    
    x=np.array(range(4,11),dtype=float)
    y = x/(4*np.tan(np.pi/x))
    plt.plot(x,y,'b-',label="Area Function")
    
    totalarea = np.sum(area)
    totalring = 0. 
    ringsize = 4.
    for nring in ring:
        totalring += ringsize*nring
        ringsize +=1
        
    totalring = (totalring/3.)
           
    Lewis =[]
    r_0=3.610
    for i in range(4,12): 
        Lewis.append( (2*totalarea/totalring)*((i-r_0)/(6-r_0)) )
    np.array(Lewis,dtype=float)
    print Lewis
    plt.plot(range(4,12),Lewis,'b--')
    titles.append("$r_o=3.610$")
    plt.xlim(3.7,10.3)
    plt.xlabel("Ring size, $r$")
    plt.ylabel("Average are per ring")
    plt.legend(titles,fontsize="small",loc=4)
    plt.savefig("lewis_key.png",dpi=150)

# <codecell>

LewisPlots2(ringfiles,areafiles,titles)

# <codecell>


