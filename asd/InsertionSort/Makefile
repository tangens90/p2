CC := g++
CFLAGS := -pedantic -Wall -std=c++11

.PHONY: all clean

all: main.x

main.x: main.o InsertionSort.o
	$(CC) $^ -o $@

main.o: main.cpp
	$(CC) $^ -c $< $(CFLAGS)

InsertionSort.o: InsertionSort.cpp InsertionSort.hpp
	$(CC) $^ -c $< $(CFLAGS)	
 
clean:
	$(RM) $(wildcard *.[ox])
	$(RM) $(wildcard *.gch)

