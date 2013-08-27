C++ = g++
OBJS = main.o vertex.o graph.o ringarea.o testcases.o tinyxml2.o
FLAGS = -ansi -pedantic -W -Wall -Wextra   
.PHONY: clean 

main.e: $(OBJS)
	$(C++) $(FLAGS) $(OBJS) -o main.e 

%.o : %.cpp
	g++ -c $(FLAGS) $<

clean:
	rm -rf *.e *.o

