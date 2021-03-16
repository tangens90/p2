CC := g++
CFLAGS := -pedantic -Wall -std=c++11

.PHONY: all clean

all: main.x

main.x: main.o Heap.o Sortowania.o BST.o AVL.o
	$(CC) $^ -o $@

main.o: main.cpp
	$(CC) $^ -c $< $(CFLAGS)

Heap.o: Heap.cpp Heap.hpp
	$(CC) $^ -c $< $(CFLAGS)	

Sortowania.o: Sortowania.cpp Sortowania.hpp
	$(CC) $^ -c $< $(CFLAGS)	
 
BST.o: BST.cpp BST.hpp
	$(CC) $^ -c $< $(CFLAGS)

AVL.o: AVL.cpp AVL.hpp
	$(CC) $^ -c $< $(CFLAGS)

clean:
	$(RM) $(wildcard *.[ox])
	$(RM) $(wildcard *.gch)

