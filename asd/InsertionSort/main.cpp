#include <iostream>
#include "InsertionSort.hpp"

int main() {
    srand(time(NULL));
    
    InsertionSort is = InsertionSort();

    is.print();

    is.sort();

    is.print();

    is.test();

    return 0;
}