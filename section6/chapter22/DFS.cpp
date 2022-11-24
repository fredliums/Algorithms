#include <queue>
#include <cstdio>
using namespace std;

typedef struct _node {
    int id;
    int color;
    int depth;
    int finish;
    struct _node *p;
} node;

int E[5][5] = {
    {0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 0, 1},
    {1, 1, 0, 1, 0}
};

node V[5];
int time;

void init();
void dfs();
void dfs_visit(node *u);
void print();

int main()
{
    dfs();
    print();

    return 0;
}

void dfs()
{
    node *u;

    init();
    for (int i = 0; i < 5; i++)
    {
        if (V[i].color == 0)
            dfs_visit(&V[i]);
    }
}

void dfs_visit(node *u)
{
    node *v;

    printf("Found node %d\n", u->id);
    time += 1;
    u->depth = time;
    u->color = 1;
    for (int i = 0; i < 5; i++)
    {
        if (E[u->id][i] == 1)
        {
            v = &V[i];
            if (v->color == 0)
            {
                v->p = u;
                dfs_visit(v);
            }
        }
    }
    u->color = 2;
    time += 1;
    u->finish = time;
}

void init()
{
    time = 0;

    for (int i = 0; i < 5; i++)
    {
        V[i].id = i;
        V[i].color = 0;
        V[i].p = NULL;
    }
}

void print()
{
    for (int i = 0; i < 5; i++)
    {
        printf("node-%d color-%d depth-%d finish-%d ",
                V[i].id, V[i].color, V[i].depth, V[i].finish);
        if (V[i].p)
            printf("p-%d", V[i].p->id);
        else
            printf("p-NULL");
        printf("\n");
    }
}
