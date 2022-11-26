#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include "heap/heap.h"

void INITIALIZE_SINGLE_SOURCE(Graph *G, int s);
void RELAX(Graph *G, int u, int v);
void DIJKSTRA(Graph *G, int s);
void PRINT_PATH(Graph *G, int s, int v);

static Heap* init_heap(Heap *H, Graph *G);

int main()
{
    Graph G;
    int s = 0;

    init_graph(&G, "./x3.txt");
    DIJKSTRA(&G, s);

    for(int i = 0; i < G.number; i++)
    {
        printf("Path from %d to %d: [length-%d]", s, i, G.V[i].d);
        PRINT_PATH(&G, s, i);
        printf("\n");
    }

    return 0;
}

void
PRINT_PATH(Graph *G, int s, int v)
{
    if (s == v)
    {
        printf("%d", s);
    }
    else if (G->V[v].pi == NULL)
    {
        printf("No path from %d to %d", s, v);
    }
    else
    {
        PRINT_PATH(G, s, G->V[v].pi->id);
        printf("->%d", v);
    }
}

void
INITIALIZE_SINGLE_SOURCE(Graph *G, int s)
{
    for(int i = 0; i < G->number; i++)
    {
        G->V[i].d = NODE_MAX_D;
        G->V[i].pi = NULL;
    }

    G->V[s].d = 0;
}

void
RELAX(Graph *G, int u, int v)
{
    int w;

    if (G->V[u].d == NODE_MAX_D)
        return;

    w = weight(G->E, u, v);
    if (G->V[v].d > G->V[u].d + w)
    {
        G->V[v].d = G->V[u].d + w;
        G->V[v].pi = &G->V[u];
    }
}

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
