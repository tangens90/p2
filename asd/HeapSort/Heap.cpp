#include "Heap.hpp"
#include <iostream>
#include <cstdlib>

Heap::Heap() {
    n = rand() % 15 + 1;

    arr = new int[n];

    for (int i = 0; i < n; i++)
        arr[i] = rand() % 1000 + 1;
}

Heap::~Heap() {
    delete[] arr;
}

void Heap::print() {
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";

    std::cout << std::endl;
}

void Heap::test() {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            std::cout << "Elementy nie są posortowane." << std::endl;
            return;
        }
    }

    std::cout << "Elementy są posortowane." << std::endl;
}

void Heap::sort() {
    buildHeap();

    for (int i = n - 1; i > 0; i--) {
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;

        heapify(i, 0);
    }
}

void Heap::heapify(int size, int i) {
    int greatest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < size && arr[l] > arr[greatest])
        greatest = l;

    if (r < size && arr[r] > arr[greatest])
        greatest = r;

    if (greatest != i) {
        int tmp = arr[greatest];
        arr[greatest] = arr[i];
        arr[i] = tmp;

        heapify(size, greatest);
    }
}

void Heap::buildHeap(){
    for (int i = n/2; i >= 0; i--) {
        heapify(n, i);
    }
}