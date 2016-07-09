#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

/* Class for tree of symbols and their binary codes. */
class Node
{
public:
    char ch = NULL;
    int count;
    Node *left, *right;

    Node() {
        left = NULL;
        right = NULL;
    }

    Node(Node *son_l, Node *son_r) {
        left = son_l;
        right = son_r;
        count = son_l->count + son_r->count;
    }
};

#endif // NODE_H
