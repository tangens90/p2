CC := g++
CFLAGS := -pedantic -Wall -std=c++11

.PHONY: all clean

all: main.x

main.x: main.o mergesort.o
	$(CC) $^ -o $@

main.o: main.cpp
	$(CC) $^ -c $< $(CFLAGS)

mergesort.o: mergesort.cpp mergesort.hpp
	$(CC) $^ -c $< $(CFLAGS)	
 
clean:
	$(RM) $(wildcard *.[ox])
	$(RM) $(wildcard *.gch)

