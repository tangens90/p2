#include <iostream>
#include "Sortowania.hpp"
#include "Heap.hpp"
#include "BST.hpp"
#include "AVL.hpp"

using std::cout;
using std::endl;

int main() {
    srand(time(NULL));

    AVL *avl = NULL;
    avl = avl->Insert(avl,10);
    avl = avl->Insert(avl,50);
    avl = avl->Insert(avl,80);
    avl = avl->Delete(avl,50);
    avl->printInorder(avl);
    cout << endl;

    BST bst = NULL;
    BST* root = NULL;
    root = bst.Insert(root,20);
    bst.Insert(root,30);
    bst.Insert(root,50);
    bst.printInorder(root);
    std::cout << std::endl;
    bst.Delete(root,30);
    bst.printInorder(root);
    std::cout << std::endl;

    int size = 16;
    Sortowania arr = Sortowania(size);
    Sortowania arr2 = Sortowania(size);
    Sortowania arr3 = Sortowania(size);
    Heap k1 = Heap();

    // heapSort
    k1.arr = arr.arr;
    k1.n = arr.n;
    k1.print();
    arr.print();
    arr.heapSort(k1);
    k1.print();
    arr.test();

    // insertionSort
    arr2.print();
    arr2.insertionSort();
    arr2.print();
    arr2.test();

    // mergeSort
    arr3.print();
    arr3.mergeSort(0,arr3.n-1);
    arr3.print();
    arr3.test();
}
