#ifndef __LINK_DISJOINT_SET_H__
#define __LINK_DISJOINT_SET_H__

struct _Node;

typedef struct _Set {
    struct _Node *head;
    struct _Node *tail;
    int length;
} Set;

typedef struct _Node {
    Set *set;
    void *data;
    struct _Node *next;
} Node;

Set* MAKE_SET(Node *u);
Set* FIND_SET(Node *u);
Set* UNION(Node *u, Node *v);

#endif
