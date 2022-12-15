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
    int u, v, c;

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
        G->E[i].f = 0;
        G->E[i].c = 0;
        G->E[i].next = NULL;
    }

    while (getline(&line, &len, stream) != -1)
    {
        sscanf(line, "%d %d %d\n", &u, &v, &c);
        p = &G->E[u];
        while (p->next != NULL)
            p = p->next;
        x = (ENode*)malloc(sizeof(ENode));
        x->id = v;
        x->c = 0;
        x->c = c;
        x->next = NULL;
        p -> next = x;
    }

    free(line);

    return G;
}

Graph* new_graph(Graph *G)
{
    int i;
    ENode *pG, *pD, *x;
    Graph *D;
    
    D = (Graph*)malloc(sizeof(Graph));

    D->number = G->number;
    D->V = (Node*)malloc(D->number * sizeof(Node));
    memcpy(&D->V, &G->V, D->number * sizeof(Node));

    D->E = (ENode*)malloc(D->number * sizeof(ENode));
    for (i = 0; i < D->number; i++)
    {
        D->E[i].id = i;
        D->E[i].f = 0;
        D->E[i].c = 0;
        D->E[i].next = NULL;
    }

    for (i = 0; i < D->number; i++)
    {
        pD = &D->E[i];
        for (pG = G->E[i].next; pG != NULL; pG = pG->next)
        {
            x = (ENode*)malloc(sizeof(ENode));
            memcpy(x, pG, sizeof(ENode));
            pD->next = x;
            pD = x;
        }
    }

    return D;
}

int weight(ENode *es, int u, int v)
{
    ENode *p;

    for (p = es[u].next; p != NULL; p = p->next)
    {
        if (p->id == v)
            return p->c;
    }

    return -1;
}

ENode* get_edge(Graph *G, int u, int v, int create)
{
    ENode *last, *p = NULL;

    for (p = G->E[u].next; p != NULL; p = p->next)
    {
        last = p;
        if (p->id = v)
            return p;
    }

    if (create)
    {
        ENode *x = (ENode*)malloc(sizeof(ENode));
        x->id = v;
        x->next = NULL;
        last->next = x;

        // Trying to set (u,v).f = (v, u).f
        for (p = G->E[v].next; p != NULL; p = p->next)
        {
            if (p->id = u)
                break;
        }
        if (p != NULL)
        {
            x->f = p->f;
        }
        p = x;
    }

    return p;
}
