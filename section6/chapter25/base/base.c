#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"

Graph* init_graph(Graph *G, char *path)
{
    char *line = NULL;
    size_t len = 0;
    FILE *stream;
    int i, number;
    ENode *p, *x;
    int u, v, w;

    stream = fopen(path, "r");

    // Init nodes
    getline(&line, &len, stream);
    sscanf(line, "%d", &number);
    G->number = number;
    G->V = (Node*)malloc(sizeof(Node) * number);
    getline(&line, &len, stream);
    for (char *p = line, i = 0; i < number; i++, p += 2)
    {
        G->V[i].id = i;
        G->V[i].name = *p;
        G->V[i].color = 0;
    }

    // Init edges
    G->E = (ENode*)malloc(sizeof(ENode) * number);
    for (i = 0; i < number; i++)
    {
        G->E[i].id = i;
        G->E[i].w = 0;
        G->E[i].next = NULL;
    }

    while (getline(&line, &len, stream) != -1)
    {
        sscanf(line, "%d %d %d\n", &u, &v, &w);
        p = &G->E[u];
        while (p->next != NULL)
            p = p->next;
        x = (ENode*)malloc(sizeof(ENode));
        x->id = v;
        x->w = w;
        x->next = NULL;
        p -> next = x;
    }

    free(line);

    return G;
}

int weight(Graph *G, int u, int v)
{
    ENode *p;

    for (p = G->E[u].next; p != NULL; p = p->next)
    {
        if (p->id == v)
            return p->w;
    }

    return NODE_MAX_D;
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

    w = weight(G, u, v);
    if (G->V[v].d > G->V[u].d + w)
    {
        G->V[v].d = G->V[u].d + w;
        G->V[v].pi = &G->V[u];
    }
}

void PRINT_EDGES(Graph *G)
{
    ENode *p;

    for (int i = 0; i < G->number; i++)
    {
        for (p = G->E[i].next; p != NULL; p = p->next) 
        {
            printf("%d->%d=%d\n", i, p->id, p->w);
        }
    }
}
