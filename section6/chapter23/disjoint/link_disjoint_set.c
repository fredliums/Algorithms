#include <stdlib.h>
#include "link_disjoint_set.h"

Set* 
MAKE_SET(LNode *u)
{
    if (u->set != NULL)
        return u->set;

    Set *set = (Set*)malloc(sizeof(Set));
    set->head = u;
    set->tail = u;
    set->length = 1;
    u->set = set;

    return set;
}

Set*
FIND_SET(LNode *u)
{
    return u->set;
}

Set*
UNION(LNode *u, LNode *v)
{
    Set *front, *back;

    if (FIND_SET(u) == FIND_SET(v))
        return u->set;

    if (FIND_SET(u) == NULL)
        return v->set;

    if (FIND_SET(v) == NULL)
        return u->set;

    if (u->set->length >= v->set->length)
    {
        front = u->set;
        back = v->set;
    }
    else
    {
        front = v->set;
        back = u->set;
    }

    /* Joint */
    front->tail->next = back->head;
    front->tail = back->tail;
    front->length += back->length;

    for (LNode *p = back->head; p != NULL; p = p->next)
        p->set = front;
    free(back);

    return front;
}
