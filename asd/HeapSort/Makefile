CC := g++
CFLAGS := -pedantic -Wall -std=c++11

.PHONY: all clean

all: main.x

main.x: main.o Heap.o
	$(CC) $^ -o $@

main.o: main.cpp
	$(CC) $^ -c $< $(CFLAGS)

Heap.o: Heap.cpp Heap.hpp
	$(CC) $^ -c $< $(CFLAGS)	
 
clean:
	$(RM) $(wildcard *.[ox])
	$(RM) $(wildcard *.gch)

