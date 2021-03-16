#include <iostream>
#include "mergesort.hpp"

int main() {
    srand(time(NULL));
    
    MergeSort ms = MergeSort();

    ms.print();

    ms.sort(0, ms.n - 1);

    ms.print();

    ms.test();

    return 0;
}