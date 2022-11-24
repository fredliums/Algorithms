#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"

Graph* init_graph(Graph *G)
{
    char *line = NULL;
    size_t len = 0;
    FILE *stream;
    int i, number;
    char start;
    ENode *p, *x;
    int u, v, w;

    stream = fopen(PATH1, "r");

    // Init nodes
    getline(&line, &len, stream);
    sscanf(line, "%d %c", &number, &start);
    G->number = number;
    G->V = (Node*)malloc(sizeof(Node) * number);
    for (i = 0; i < number; i++)
    {
        G->V[i].id = i;
        G->V[i].name = start + i;
    }

    // Init edges
    G->E = (ENode*)malloc(sizeof(ENode) * number);
    for (i = 0; i < number; i++)
    {
        G->E[i].id = i;
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

