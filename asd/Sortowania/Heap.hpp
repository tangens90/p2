#ifndef __HEAPSORT_HPP__
#define __HEAPSORT_HPP__

class Heap {
public:
    int *arr;
    int n;

    void heapify(int size, int i);
    void buildHeap();
    void print();
};

#endif