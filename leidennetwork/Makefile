
JMOL=~/jmol-13.0.12/Jmol.jar
PHONY:jmol
432_cornersharing.xyz: 
	./corner_triangles.py *.coord *.connect | awk '{ if(NF==4) print $$1 " " 2*$$2 " " 2*$$3 " " 2*$$4; else print}' > 432_cornersharing.xyz

jmol: 432_cornersharing.xyz
	$(JMOL) 432_cornersharing.xyz -s *.jmolscript

