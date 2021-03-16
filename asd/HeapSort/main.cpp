#include <iostream>
#include "Heap.hpp"

int main() {
    srand(time(NULL));

    Heap hs = Heap();

   	hs.print();
    
    hs.sort();

    hs.print();

    hs.test();

    return 0;
}