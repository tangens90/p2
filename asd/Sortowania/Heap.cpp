#include <iostream>
#include "Heap.hpp"

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

void Heap::print() {
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";

    std::cout << std::endl;
}