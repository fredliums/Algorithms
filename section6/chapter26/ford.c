#include <stdio.h>
#include <stdlib.h>
#include "base.h"

static int find_path(Graph *G, int *path, int start, int target);
static int min_weight(Graph *G, int *path, int len);
static int edge_in_edges(Graph *G, int u, int v);
Graph *ford(Graph *G, int s, int t);

int main()
{
    Graph G;

    init_graph(&G, "init.txt");
    ford(&G, 0, G.number - 1);

    return 0;
}

Graph *ford(Graph *G, int s, int t)
{
    Graph *Gf;
    ENode *p;
    int len, *path, min;
    int i, u, v;
    
    Gf = new_graph(G);
    path = (int*)malloc(Gf->number * sizeof(int));
    while((len = find_path(Gf, path, s, t)) > 0)
    {
        min = min_weight(Gf, path, len);
        for (i = 1; i < len; i++)
        {
            u = len - 1;
            v = u - 1;

            if (edge_in_edges(Gf, u, v))
            {
                p = get_edge(Gf, u, v, 0);
                p->f = p->f + min;
            }
            else
            {
                p = get_edge(Gf, v, u, 1);
                p->f = p->f - min;
            }
        }
    }

    return Gf;
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
                v->pi = u;
                dfs_visit(G, v);
            }
        }
    }
    u->color = 2;
}

/*
 * 1. If there exists a path from start to target, return the number of nodes,
 *    otherwise return -1
 * 2. The paths stored in path
 */
static int find_path(Graph *G, int *path, int start, int target)
{
    Node *node;
    int count = 0;

    dfs_visit(G, &G->V[start]);

    for(node = &G->V[target]; node != NULL; node = node->pi)
    {
        path[count++] = node->id;
        if (node->id == start)
            break;
    }

    // clear the nodes
    for (int i = 0; i < G->number; i++)
    {
        G->V[i].pi = NULL;
        G->V[i].color = 0;
    }

    if (node == NULL)
        return -1;
    else
        return count;
}

static int min_weight(Graph *G, int *path, int len)
{
    ENode *p;
    int min = NODE_MAX_D;
    int index = len - 1;

    for (int i = 1; i < len; i++)
    {
        int u = path[index];
        int v = path[index - 1];

        p = get_edge(G, u, v, 0);
        if (p->f < min)
            min = p->f;
    }

    return min;
}


static int edge_in_edges(Graph *G, int u, int v)
{
    ENode *p;

    for(p = G->E[u].next; p != NULL; p = p->next)
    {
        if (p->id = v)
            return 1;
    }

    return 0;
}
