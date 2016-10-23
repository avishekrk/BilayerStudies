# Silica Bilayer Studies

---

# Abstract

The recent synthesis and characterization of bilayers of vitreous slica has
produced valuable new information on ring sizes and distributions. In this paper,
we compare the ring statistics of experimental samples with computer generated
samples. The average ring size is fixed at six by topology, but the width, 
skewness and other moments of the distribution of ring edges and chracteristics
of particular samples. We examine the Aboav-Weaire law that quantifies the
propensity of smaller rings to be adjacent to larger rings, and find similiar 
results for available experimental samples which however differ somewhat from
computer-generated bilayers currently. We introduce a new law for the areas of 
rings of various sizes. 

---

# Dependencies

The bilayer analysis code is written in C++ and compiled with g++ on Ubuntu
Linux 14.04. The two-dimensional visualization of the networks is done in
Mathematica. The plotting of distributions is done in Python. The 
three-dimensional networks are plotted in Jmol.

---

# Installation

---

# Usage 

```
./main.e coordinates.xyz coordinates.xml coordinates.con
```

* coordinates.xyz: coordiantes files
* coordinates.xml: parameter file
* coordiantes.con: connectivity matrix

---

# References
    
1. Kumar A, Sherrington D, Wilson M, Thorpe MF: Ring statistics of silica 
bilayers. Journal of Physics: Condensed Matter 2014, 26:395401. 
[DOI](http://dx.doi.org/10.1088/0953-8984/26/39/395401)

---
