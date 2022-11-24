#include "tree_disjoint_set.h"

TNode* MAKE_SET(TNode *u)
{
    u->p = u;
    u->rank = 0;
}

TNode* FIND_SET(TNode *u)
{
    if (u != u->p)
        u->p = FIND_SET(u->p);

    return u->p;
}

static TNode* LINK(TNode *root1, TNode *root2)
{
    if (root1->rank > root2->rank)
        root2->p = root1;
    else
    {
        root1->p = root2;
        if (root1->rank == root2->rank)
            root2->rank += 1;
    }
}

TNode* UNION(TNode *u, TNode *v)
{
    TNode *r1 = FIND_SET(u);
    TNode *r2 = FIND_SET(v);
    
    if (r1 != r2)
        LINK(r1, r2);
}
