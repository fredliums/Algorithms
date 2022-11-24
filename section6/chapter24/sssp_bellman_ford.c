#include <stdio.h>
#include "base.h"

static int weight(ENode *es, int u, int v);
void INITIALIZE_SINGLE_SOURCE(Graph *G, int s);
void RELAX(Graph *G, int u, int v);
int BELLMAN_FORD(Graph *G, int s);
void PRINT_PATH(Graph *G, int s, int v);

int main()
{
    Graph G;
    int s = 0;

    init_graph(&G);
    BELLMAN_FORD(&G, s);

    for(int i = 0; i < G.number; i++)
    {
        printf("Path from %d to %d: ", s, i);
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
        return;
    }
    else if (G->V[v].pi == NULL)
        printf("No path from %d to %d\n", s, v);
    else
    {
        PRINT_PATH(G, s, G->V[v].pi->id);
        printf("->%d", v);
    }
}

static int
weight(ENode *es, int u, int v)
{
    ENode *p;

    for (p = es[u].next; p != NULL; p = p->next)
    {
        if (p->id == v)
            return p->w;
    }

    return NODE_MAX_D;
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
