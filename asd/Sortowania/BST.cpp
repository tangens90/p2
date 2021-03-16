#include "BST.hpp"
#include <iostream>

BST::BST(int n) {
    data = n;
    l = NULL, r = NULL;
}

void BST::printInorder(BST *root) {
    if(root == NULL)
        return;

    printInorder(root->l);
    std::cout << root->data << " ";
    printInorder(root->r);
}

BST *BST::Search(BST *root, int n) {
    if (root == NULL || root->data == n)
        return root;

    if (root->data < n)
        return Search(root->r, data);
    else
        return Search(root->l, data);
}

BST *BST::Insert(BST *root, int n) {

    if (root == NULL)
        return new BST(n);

    if (n > root->data)
        root->r = Insert(root->r, n);
    else
        root->l = Insert(root->l, n);

    return root;
}

BST *BST::Delete(BST *root, int n) {

    if (root == NULL)
        return root;

    if (n < root->data)
        root->l = Delete(root->l, n);
    else if (n > root->data)
        root->r = Delete(root->r, n);
    else {
        if (root->l == NULL) {
            BST *k = root->r;
            delete root;
            return k;
        }

        else if (root->l == NULL) {
            BST *k = root->l;
            delete root;
            return k;
        }

        else {
            BST *w = minNode(root->r);
            root->data = w->data;
            root->r = Delete(root->r, w->data);
        }
    }

    return root;
}

BST *BST::minNode(BST *node) {
    BST *k = node;
    while (k && k->l != NULL)
        k = k->l;

    return k;
}