all: test
test: main.o centroidDecomp.o 
	g++  -Wall -std=c++0x main.o centroidDecomp.o -o test
main.o: main.cpp centroidDecomp.hpp
	g++  -Wall -std=c++0x -c main.cpp
centroidDecomp.o: centroidDecomp.cpp centroidDecomp.hpp
	g++  -Wall -std=c++0x -c centroidDecomp.cpp
clean:
	rm *.o test

	


