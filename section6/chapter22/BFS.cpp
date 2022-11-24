#include <queue>
#include <cstdio>
using namespace std;

typedef struct _node {
    int id;
    int color;
    int depth;
    struct _node *p;
} node;

int E[5][5] = {
    {0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 0, 1},
    {1, 1, 0, 1, 0}
};

queue<node*> q;
node V[5];
node *s;

void init();
int bfs();
void print();

int main()
{
    init();
    bfs();
    print();

    return 0;
}

void init()
{
    for (int i = 0; i < 5; i++)
    {
        V[i].id = i;
        V[i].color = 0;
        V[i].depth = 0;
        V[i].p = NULL;
    }

    s = &V[0];
    s->color = 1;
    s->depth = 0;
    s->p = NULL;

    q.push(s);
}

int bfs()
{
    int id;
    node *u, *v;

    while(!q.empty()) {
        u = q.front();
        q.pop();
        id = u->id;
        for (int i = 0; i < 5; i++)
        {
           if (E[id][i] == 1)
           {
               v = &V[i];
               if (v->color == 0)
               {
                   printf("Found node %d\n", i);
                   v->color = 1;
                   v->depth = u->depth + 1;
                   v->p = u;
                   q.push(v);
               }
           }
        }
        u->color = 2;
    }

    return 0;
}

void print()
{
    for (int i = 0; i < 5; i++)
    {
        printf("node-%d color-%d depth-%d ", V[i].id, V[i].color, V[i].depth);
        if (V[i].p)
            printf("p-%d", V[i].p->id);
        else
            printf("p-NULL");
        printf("\n");
    }
}
