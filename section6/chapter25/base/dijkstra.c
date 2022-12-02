#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include "heap.h"

static Heap* init_heap(Heap *H, Graph *G);

void
DIJKSTRA(Graph *G, int s)
{
    Heap H;
    Node *u;
    ENode *p;

    INITIALIZE_SINGLE_SOURCE(G, s);
    init_heap(&H, G);

    while(heap_length(&H) > 0)
    {
        u = (Node*)pop_min(&H);
        
        for(p = &(G->E[u->id]); p != NULL; p = p->next)
        {
            RELAX(G, u->id, p->id);
        }
        build_min_heap(&H, 0);
    }
}

static Heap*
init_heap(Heap *H, Graph *G)
{
    Node** V = (Node**)calloc(G->number, sizeof(Node*));
    for (int i = 0; i < G->number; i++)
        V[i] = &G->V[i];

    H->size = G->number;
    H->length = G->number;
    H->data = (Item**)V;

    return H;
}
