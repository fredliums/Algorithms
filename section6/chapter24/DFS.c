#include "base.h"

void dfs(Graph *G);
void dfs_visit(Graph *G, Node *u);

static int count;
extern Node** sorted;

void dfs(Graph *G)
{
    count = G->number;
    for (int i = 0; i < G->number; i++)
    {
        if (G->V[i].color == 0)
            dfs_visit(G, &G->V[i]);
    }
}

void dfs_visit(Graph *G, Node *u)
{
    Node *v;

    u->color = 1;
    for (int i = 0; i < G->number; i++)
    {
        if (weight(G->E, u->id, i) < NODE_MAX_D)
        {
            v = &G->V[i];
            if (v->color == 0)
            {
                dfs_visit(G, v);
            }
        }
    }
    u->color = 2;
    sorted[--count] = u;
}

