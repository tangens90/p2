#ifndef __MERGESORT_HPP__
#define __MERGESORT_HPP__

class MergeSort {

public:
    int *arr;
    int n;

    MergeSort();
    ~MergeSort();
    void print();
    void test();
    void merge(int p, int q, int r);
    void sort(int p, int r);
};

#endif