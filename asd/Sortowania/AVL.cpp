#include "AVL.hpp"
#include <iostream>

using std::cout;

void AVL::printInorder(AVL* w) {
    if(w == NULL)
        return;
    printInorder(w->l);
    cout << w->data << " ";
    printInorder(w->r);
}

int AVL::height(AVL* w) {
    if(w == NULL)
        return -1;

    return w->h;
}

int AVL::calcBF(AVL* w) {
  if (w == NULL)
      return 0;
  return height(w->l) - height(w->r);
}

AVL* AVL::NewNode(int n) {
    AVL* w = new AVL();
    w->data = n;
    w->l = NULL, w->r = NULL;
    w->h = 1;
    return w;
}

AVL* AVL::Insert(AVL* w, int n) {
    if (w == NULL) {
        return(NewNode(n));
    }

    if (n < w->data)
        w->l = Insert(w->l, n);
    else if (n > w->data)
        w->r = Insert(w->r, n);
    else
        return w;

    if (height(w->l) > height(w->r))
        w->h = 1 + height(w->l);
    else
        w->h = 1 + height(w->r);

    int bf = calcBF(w);

    if (bf > 1 && n < w->l->data)
        return rightrightRotation(w);
    if (bf < -1 && n > w->r->data)
        return leftleftRotation(w);
    if (bf > 1 && n > w->l->data) {
        w->l = leftleftRotation(w->l);
        return rightrightRotation(w);
    }
    if (bf < -1 && n < w->r->data) {
        w->r = rightrightRotation(w->r);
        return leftleftRotation(w);
    }

    return w;
}

AVL* AVL::Delete(AVL* w, int n) {
    if (w == NULL)
        return w;
    if (n < w->data)
        w->l = Delete(w->l, n);
    else if (n > w->data)
        w->r = Delete(w->r, n);
    else {
        // zero lub jedno dziecko
        if ((w->l == NULL) || (w->r == NULL)) { 
            AVL *node;
            if (w->l)
                node = w->l;
            else
                node = w->r;

            if (node == NULL) {
                node = w;
                w = NULL;
            }
            else
                *w = *node;
            delete node;
        }

        else {
            AVL* node1 = minNode(w->r);
            w->data = node1->data;
            w->r = Delete(w->r, node1->data);
        }
    }

    if (w == NULL)
        return w;

    if (height(w->l) > height(w->r))
        w->h = 1 + height(w->l);
    else
        w->h = 1 + height(w->r);

    int b = calcBF(w);

    if (b > 1 && calcBF(w->l) >= 0)
        return rightrightRotation(w);
    if (b > 1 && calcBF(w->l) < 0){
        w->l = leftleftRotation(w->l);
        return rightrightRotation(w);
    }
    if (b < -1 && calcBF(w->r) <= 0)
        return leftleftRotation(w);
    if (b < -1 && calcBF(w->r) > 0) {
        w->r = rightrightRotation(w->r);
        return leftleftRotation(w);
    }

    return w;
}

AVL* AVL::minNode(AVL* w) {
    AVL* n = w;
    while (n->l != NULL)
        n = n->l;
    return n;
}

AVL* AVL::rightrightRotation(AVL* w) {
    AVL* w1 = w->l;
    AVL* w2 = w1->r;

    w1->r = w;
    w->l = w2;

    if (height(w->l) > height(w->r))
        w->h = height(w->l) + 1;
    else
        w->h = height(w->r) + 1;

    if (height(w1->l) > height(w1->r))
        w1->h = height(w1->l) + 1;
    else
        w1->h = height(w1->r) + 1;

    return w1;
}

AVL* AVL::leftleftRotation(AVL* w) {
    AVL* w1 = w->r;
    AVL* w2 = w1->l;

    w1->l = w;
    w->r = w2;

    if (height(w->l) > height(w->r))
        w->h = height(w->l) + 1;
    else
        w->h = height(w->r) + 1;

    if (height(w1->l) > height(w1->r))
        w1->h = height(w1->l) + 1;
    else
        w1->h = height(w1->r) + 1;

    return w1;
}

AVL* AVL::leftrightRotation(AVL* w) {
    AVL* w1;
    w1 = w->l;
    w->l = rightrightRotation(w1);
    return leftleftRotation(w);
}

AVL* AVL::rightleftRotation(AVL* w) {
    AVL* w1;
    w1 = w->r;
    w->r = leftleftRotation(w1);
    return rightrightRotation(w);
}