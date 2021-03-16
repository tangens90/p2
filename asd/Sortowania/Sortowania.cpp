#include <iostream>
#include "Sortowania.hpp"
#include "Heap.hpp"

Sortowania::Sortowania(int n) {
    arr = new int[n];
    this->n = n;

    for (int i = 0; i < n; i++)
        arr[i] = rand() % 1000 + 1;
}

Sortowania::~Sortowania() {
    delete[] arr;
}

void Sortowania::insertionSort() {
    for (int j = 1; j < n; j++) {

        int element = arr[j];
        int i = j - 1;

        while (i >= 0 && arr[i] > element) {
            arr[i + 1] = arr[i];
            i--;
        }

        arr[i + 1] = element;
    }
}

void Sortowania::merge(int p, int q, int r) {
    int n1 = q - p + 1; 
    int n2 = r - q;
    
    int *left = new int[n1];
    int *right = new int[n2];

    for (int i = 0; i < n1; i++)
        left[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        right[j] = arr[q + 1 + j];

    int i1 = 0, i2 = 0;
    int k = p;

    while (i1 < n1 && i2 < n2) {
        if (left[i1] <= right[i2]) {
            arr[k] = left[i1];
            i1++;
        }
        else {
            arr[k] = right[i2];
            i2++;
        }
        k++;
    }

    while (i1 < n1) {
        arr[k] = left[i1];
        i1++;
        k++;
    }

    while (i2 < n2) {
        arr[k] = right[i2];
        i2++;
        k++;
    }
}

void Sortowania::mergeSort(int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;

        Sortowania::mergeSort(p, q);
        Sortowania::mergeSort(q + 1, r);

        Sortowania::merge(p, q, r);
    }
}

void Sortowania::heapSort(Heap h) {
    h.buildHeap();

    for (int i = n - 1; i > 0; i--) {
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;

        h.heapify(i, 0);
    }
}

void Sortowania::print() {
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";

    std::cout << std::endl;
}

void Sortowania::test() {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            std::cout << "Elementy nie są posortowane." << std::endl;
            return;
        }
    }

    std::cout << "Elementy są posortowane." << std::endl;
}