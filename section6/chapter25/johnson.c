#include <stdio.h>
#include <stdlib.h>
#include "base/base.h"
#include "matrix/matrix.h"

static Graph* new_gq(Graph *G);
static int set_weight(Graph *G, Graph *GQ, int u, int v);
Matrix* JHONSON(Graph *G);

int main()
{
    Graph G, *GQ;
    Matrix *D;
    int s = 0;

    init_graph(&G, "./x.txt");
    D = JHONSON(&G);
    printf("Shortest weights matrix:\n");
    print(D);

    return 0;
}

Matrix* JHONSON(Graph *G)
{
    int i, j, gi, gj;
    Graph *GQ;
    ENode *p;
    Matrix* D;

    D = new_matrix(G->number, G->number);
    // Generate a new graph
    GQ = new_gq(G);

    if (BELLMAN_FORD(GQ, 0) == 0)
    {
        printf("The input graph contains a negative-weight cycle\n");
        return NULL;
    }
    else
    {
        // Set new d for G computed by Bellman
        for (i = 0; i < G->number; i++)
            G->V[i].d = GQ->V[i + 1].d;

        // Compute the new edges
        for (i = 0; i < G->number; i++)
        {
            for (p = G->E[i].next; p != NULL; p = p->next)
                set_weight(G, GQ, i, p->id);
        }

        // Compute shortest path u->v
        for (i = 1; i < GQ->number; i++)
        {
            gi = i - 1;
            DIJKSTRA(GQ, i);
            for (j = 1; j < GQ->number; j++)
            {
                gj = j - 1;
                // D[u][v] = GQ[u][v] + h(v) - h(u)
                D->data[gi][gj] = GQ->V[j].d
                    + G->V[gj].d - G->V[gi].d;
            }

            // Print shortest weights and paths
            for(j = 1; j < GQ->number; j++)
            {
                printf("Path from %d to %d: [length-%d]",
                        i, j, D->data[i - 1][j - 1]);
                PRINT_PATH(GQ, i, j);
                printf("\n");
            }
        }
    }

    return D;
}

static int set_weight(Graph *G, Graph *GQ, int u, int v)
{
    ENode *p = GQ->E[u + 1].next;

    while (p->id != v + 1)
        p = p->next;

    // new weight: GQ[u][v] = G[u][v] + h(u) - h(v)
    p->w = weight(G, u, v) + GQ->V[u + 1].d - GQ->V[v + 1].d;

    return p->w;
}

static Graph* new_gq(Graph *G)
{
    int i;
    Graph *GQ;
    ENode *p, *q, *new;

    GQ = (Graph*)malloc(sizeof(Graph));

    GQ->number = G->number + 1;
    GQ->V = (Node*)malloc(GQ->number * sizeof(Node));

    GQ->V[0].d = 0;
    GQ->V[0].id = 0;
    GQ->V[0].name = '0';
    GQ->V[0].color = 0;
    GQ->V[0].pi = NULL;
    for (i = 1; i < GQ->number; i++)
    {
        GQ->V[i].d = G->V[i - 1].d;
        GQ->V[i].id = G->V[i - 1].id + 1;
        GQ->V[i].name = G->V[i - 1].name;
        GQ->V[i].color = G->V[i - 1].color;
        GQ->V[i].pi = G->V[i - 1].pi;
    }

    GQ->E = (ENode*)malloc(GQ->number * sizeof(ENode));

    GQ->E[0].id = 0;
    GQ->E[0].w = 0;
    q = &GQ->E[0];
    for (i = 1; i < GQ->number; i++)
    {
        new = (ENode*)malloc(sizeof(ENode));
        new->id = i;
        new->w = 0;
        new->next = NULL;
        q->next = new;
        q = new;
    }
    
    for (i = 1; i < GQ->number; i++)
    {
        GQ->E[i].id = i;
        GQ->E[i].w = 0;
        q = &GQ->E[i];
        for (p = G->E[i - 1].next; p != NULL; p = p->next)
        {
            new = (ENode*)malloc(sizeof(ENode));
            new->id = p->id + 1;
            new->w = p->w;
            new->next = NULL;
            q->next = new;
            q = new;
        }
    }

    return GQ;
}
