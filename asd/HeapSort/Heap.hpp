#ifndef __HEAPSORT_HPP__
#define __HEAPSORT_HPP__

class Heap {
public:
    int *arr;
    int n;

    Heap();
    ~Heap();
    void print();
    void test();
    void sort();
    void heapify(int size, int i);
    void buildHeap();
};

#endif