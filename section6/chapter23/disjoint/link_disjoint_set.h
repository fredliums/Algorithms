#ifndef __LINK_DISJOINT_SET_H__
#define __LINK_DISJOINT_SET_H__

struct _LNode;

typedef struct _Set {
    struct _LNode *head;
    struct _LNode *tail;
    int length;
} Set;

typedef struct _LNode {
    Set *set;
    void *data;
    struct _LNode *next;
} LNode;

Set* MAKE_SET(LNode *u);
Set* FIND_SET(LNode *u);
Set* UNION(LNode *u, LNode *v);

#endif
