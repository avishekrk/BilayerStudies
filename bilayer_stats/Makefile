C++ = g++
FLAGS = -ansi -pedantic -W -Wall -Wextra -g
.PHONY: clean 

main.e: main.o vertex.o graph.o ringarea.o testcases.o  
	$(C++) $(FLAGS) main.o vertex.o graph.o ringarea.o testcases.o -o main.e 

%.o : %.cpp
	g++ -c $(FLAGS) $<

clean:
	rm -rf *.e *.o

