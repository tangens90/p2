#ifndef __BST_HPP__
#define __BST_HPP__

class BST {
public:
    int data;
    BST *l, *r;

    BST(int n);
    void printInorder(BST*);
    BST *Search(BST*, int);
    BST *Insert(BST*, int);
    BST *Delete(BST*, int);
    BST *minNode(BST*);
};

#endif