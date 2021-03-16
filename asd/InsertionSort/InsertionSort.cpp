#include <iostream>
#include <cstdlib>
#include "InsertionSort.hpp"

InsertionSort::InsertionSort() {
    n = rand() % 15 + 1;

    arr = new int[n];

    for (int i = 0; i < n; i++)
        arr[i] = rand() % 1000 + 1;
}

InsertionSort::~InsertionSort() {
    delete[] arr;
}

void InsertionSort::print() {
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";

    std::cout << std::endl;
}

void InsertionSort::test() {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            std::cout << "Elementy nie są posortowane." << std::endl;
            return;
        }
    }

    std::cout << "Elementy są posortowane." << std::endl;
}

void InsertionSort::sort() {
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



