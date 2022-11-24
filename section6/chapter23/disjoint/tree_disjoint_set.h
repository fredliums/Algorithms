#ifndef __TREE_DISJOINT_SET_H__
#define __TREE_DISJOINT_SET_H__

typedef struct _TNode {
    struct _TNode *p;
    int rank;
    void *data;
} TNode;

TNode* MAKE_SET(TNode *u);
TNode* FIND_SET(TNode *u);
TNode* UNION(TNode *u, TNode *v);

#endif
