#include <stdio.h>
#include "base.h"

int
BELLMAN_FORD(Graph *G, int s)
{
    ENode *p = NULL;

    INITIALIZE_SINGLE_SOURCE(G, s);

    for (int i = 1; i < G->number; i++)
    {
        for (int j = 0; j < G->number; j++)
        {
            for(p = &(G->E[j]); p != NULL; p = p->next)
            {
                RELAX(G, j, p->id);
            }
        }
    }

    // Check ring
    for (int j = 0; j < G->number; j++)
    {
        for(p = &(G->E[j]); p != NULL; p = p->next)
        {
            if (G->V[p->id].d > G->V[j].d + p->w)
                return 0;
        }
    }

    return 1;
}
