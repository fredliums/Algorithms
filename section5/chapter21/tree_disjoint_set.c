#include "tree_disjoint_set.h"

Node* MAKE_SET(Node *u)
{
    u->p = u;
    u->rank = 0;
}

Node* FIND_SET(Node *u)
{
    if (u != u->p)
        u->p = FIND_SET(u->p);

    return u->p;
}

static Node* LINK(Node *root1, Node *root2)
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

Node* UNION(Node *u, Node *v)
{
    Node *r1 = FIND_SET(u);
    Node *r2 = FIND_SET(v);
    
    if (r1 != r2)
        LINK(r1, r2);
}
