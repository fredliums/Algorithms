#include <stdio.h>
#include <stdlib.h>
#include "base.h"

void INITIALIZE_SINGLE_SOURCE(Graph *G, int s);
void RELAX(Graph *G, int u, int v);
int DAG_SHORTEST_PATHS(Graph *G, int s);
void PRINT_PATH(Graph *G, int s, int v);

extern void dfs(Graph *G);

Node **sorted = NULL;

int main()
{
    Graph G;
    int s = 1;

    init_graph(&G, "./x2.txt");
    DAG_SHORTEST_PATHS(&G, s);

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
    static char buff[128];
    static char *p = buff;

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

int
DAG_SHORTEST_PATHS(Graph *G, int s)
{
    int id;
    ENode *p = NULL;

    sorted = (Node**)calloc(G->number, sizeof(Node*));
    
    dfs(G);

    INITIALIZE_SINGLE_SOURCE(G, s);

    for (int i = 0; i < G->number; i++)
    {
        // topo order index
        id = sorted[i]->id;
        for(p = &(G->E[id]); p != NULL; p = p->next)
        {
            RELAX(G, id, p->id);
        }
    }
}
