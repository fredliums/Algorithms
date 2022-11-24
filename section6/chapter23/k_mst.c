#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "disjoint/link_disjoint_set.h"
#include "disjoint/tree_disjoint_set.h"

#define NV 9
#define NE 14

typedef struct _GNode {
    int id;
    char name;
//  LNode *node;
    TNode *node;
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
    {0, 0, 0, 0, 0, 0, 0, 1, 6},
    {8, 11, 0, 0, 0, 0, 1, 0, 7}
};

Graph* init_graph(Graph *G);
Edge* init_edge(Graph *G, Edge *edges);
Edge* sort_edge(Edge *edges, Edge *es[NE]);

static void exchange(Edge **a, Edge **b);
static void quick_sort(Edge *(*es), int p, int r);

int main()
{
    Graph G;
//  LNode V[NV] = { 0 };
    TNode V[NV] = { 0 };
    Edge edges[NE];
    Edge *A[NV - 1];
    Edge *es[NE];
    int i, countA = 0;

    init_graph(&G);
    init_edge(&G, edges);

    for(i = 0; i < NV; i++)
    {
        V[i].data = &G.V[i];
        G.V[i].node = &V[i];
        MAKE_SET(&V[i]);
    }

    sort_edge(edges, es);

    for (i = 0; i < NE; i++)
    {
//      LNode *nodeu = es[i]->u->node;
//      LNode *nodev = es[i]->v->node;
        TNode *nodeu = es[i]->u->node;
        TNode *nodev = es[i]->v->node;
        if (FIND_SET(nodeu) != FIND_SET(nodev))
        {
            A[countA++] = es[i];
            UNION(nodeu, nodev);
        }
    }

    return 0;
}

static void exchange(Edge **a, Edge **b)
{
    Edge *tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

static void quick_sort(Edge *(*es), int p, int r)
{
    int i = p, j = p;
    int pivot;

    if (p >= r)
        return;

    /* Generate pivot randomly */
    srandom(time(NULL));
    pivot = random() % (r - p) + p;
    if (pivot != r)
        exchange(&es[pivot], &es[r]);

    /* 
     * Partition first
     * |----i|-----j|---pending----|r|
     */
    while(j < r)
    {
        if (es[j]->w < es[r]->w)
        {
            if (i < j)
                exchange(&es[i], &es[j]);
            i++;
        }
        j++;
    }
    exchange(&es[i], &es[r]);
    
    /* Recursive sort p to i */
    quick_sort(es, p, i - 1);

    /* Recursive sort i to r */
    quick_sort(es, i + 1, r);
}

Graph* init_graph(Graph *G)
{
    for (int i = 0; i < NV; i++)
    {
        G->V[i].id = i;
        G->V[i].name = 'a' + i;
    }
    G->E = E;

    return G;
}

Edge* init_edge(Graph *G, Edge *edges)
{
    int count = 0;

    for (int i = 0; i < NV; i++)
    {
        for (int j = i + 1; j < NV; j++)
        {
            if (G->E[i][j] > 0)
            {
                printf("%d->%d-%d\t", i, j, G->E[i][j]);
                edges[count].u = &G->V[i];
                edges[count].v = &G->V[j];
                edges[count].w = G->E[i][j];
                count++;
            }
        }
        printf("\n");
    }
}

Edge* sort_edge(Edge *edges, Edge *es[NE])
{
    int i;

    for (i = 0; i < NE; i++)
        es[i] = &edges[i];

    quick_sort(es, 0, 13);

    return *es;
}
