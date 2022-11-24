#ifndef __TREE_DISJOINT_SET_H__
#define __TREE_DISJOINT_SET_H__

typedef struct _Node {
    struct _Node *p;
    int rank;
    void *data;
} Node;

Node* MAKE_SET(Node *u);
Node* FIND_SET(Node *u);
Node* UNION(Node *u, Node *v);

#endif
