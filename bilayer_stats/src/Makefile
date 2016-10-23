C++ = g++
OBJS = main.o vertex.o graph.o ringarea.o testcases.o tinyxml2.o aboav.o 
FLAGS = -ansi -pedantic -W -Wall -Wextra 
OPTS = -O3
#DEBUG = -g    
.PHONY: clean 

main.e: $(OBJS)
	$(C++) $(FLAGS) $(OPTS) $(DEBUG) $(OBJS) -o main.e 

%.o : %.cpp
	g++ -c $(FLAGS) $(OPTS) $(DEBUG) $<

clean:
	rm -rf *.e *.o

