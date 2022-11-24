#include <stdio.h>
#include <stdlib.h>
#include "heap/heap.h"

#define NV 9
#define NE 14

typedef struct _GNode {
    int key;
    int id;
    char name;
    struct _GNode *pi;
} GNode; 

typedef struct _Graph {
    GNode V[NV];
    int (*E)[NV];
} Graph;

typedef struct _Edge {
    GNode *u;
    GNode *v;
    int w;
} Edge;

int E[NV][NV] = {
    {0, 4, 0, 0, 0, 0, 0, 8, 0},
    {4, 0, 8, 0, 0, 0, 0, 11, 0},
    {0, 8, 0, 7, 0, 4, 0, 0, 2},
    {0, 0, 7, 0, 9, 14, 0, 0, 0},
    {0, 0, 0, 9, 0, 10, 0, 0, 0},
    {0, 0, 4, 14, 10, 0, 2, 0, 0},
    {0, 0, 0, 0, 0, 2, 0, 1, 6},
    {8, 11, 0, 0, 0, 0, 1, 0, 7},
    {0, 0, 2, 0, 0, 0, 6, 7, 0}
};

Edge A[NV - 1];
GNode *V[NV];

Graph* init_graph(Graph *G);
GNode** init_queue(Graph *G, GNode *Q[NV]);
Heap* init_heap(GNode *Q[NV], Heap *H);
void MST_Prim(Graph *G, int r);

int main()
{
    Graph G;

    init_graph(&G);
    MST_Prim(&G, 0);

    for (int i = 1; i < NV; i++)
    {
        A[i - 1].u = V[i]->pi;
        A[i - 1].v = V[i];
        A[i - 1].w = V[i]->key;
    }

    return 0;
}

void MST_Prim(Graph *G, int r)
{
    GNode *u, *v;
    GNode *Q[NV];
    Heap H;
    int w, count = 0;

    init_queue(G, Q);
    init_heap(Q, &H);

    G->V[r].key = 0;

    min_heapify(&H, 0);
    while(heap_length(&H) > 0)
    {
        u = (GNode *)pop_min(&H);
        V[count++] = u;
        for (int i = 0; i < heap_length(&H); i++)
        {
            v = (GNode*)H.data[i];
            w = G->E[u->id][v->id];

            if (w > 0 && w < v->key)
            {
                v->pi = u;
                v->key = w;
            }
        }
        build_min_heap(&H, heap_length(&H));
    }
}

GNode** init_queue(Graph *G, GNode *Q[NV])
{
    for (int i = 0; i < NV; i++)
        Q[i] = &G->V[i];

    return Q;
}

Heap* init_heap(GNode *Q[NV], Heap *H)
{
    H->size = NV;
    H->length = NV;
    H->data = (Item**)Q;

    return H;
}

Graph* init_graph(Graph *G)
{
    for (int i = 0; i < NV; i++)
    {
        G->V[i].key = HEAP_MAX_KEY;
        G->V[i].id = i;
        G->V[i].name = 'a' + i;
        G->V[i].pi = NULL;
    }
    G->E = E;

    return G;
}
