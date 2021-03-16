#ifndef __SORTOWANIA_HPP__
#define __SORTOWANIA_HPP__
#include "Heap.hpp"

class Sortowania {
public:
    int *arr;
    int n;

    Sortowania(int n);
    ~Sortowania();
    void insertionSort();
    void merge(int p, int q, int r);
    void mergeSort(int p, int r);
    void heapSort(Heap h);
    void print();
    void test();
};

#endif