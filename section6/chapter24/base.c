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

int weight(ENode *es, int u, int v)
{
    ENode *p;

    for (p = es[u].next; p != NULL; p = p->next)
    {
        if (p->id == v)
            return p->w;
    }

    return NODE_MAX_D;
}


