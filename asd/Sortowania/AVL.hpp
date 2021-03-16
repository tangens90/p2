#ifndef __AVL_HPP__
#define __AVL_HPP__
#include <iostream>

class AVL {
public:
    int data;
    int h;
    AVL *l, *r;

    void printInorder(AVL*);
    int height(AVL*);
    int calcBF(AVL*);
    AVL *NewNode(int);
    AVL *Insert(AVL*, int);
    AVL *Delete(AVL*, int);
    AVL *minNode(AVL*);
    AVL *rightrightRotation(AVL*);
    AVL *leftleftRotation(AVL*);
    AVL *leftrightRotation(AVL*);
    AVL *rightleftRotation(AVL*);
};


#endif