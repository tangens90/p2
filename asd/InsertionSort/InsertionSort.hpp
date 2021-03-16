#ifndef __INSERTIONSORT_HPP__
#define __INSERTIONSORT_HPP__


class InsertionSort {

private:
    int *arr;
    int n;

public:
    InsertionSort();
    ~InsertionSort();
    void print();
    void test();
    void sort();
};

#endif