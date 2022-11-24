#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define N 9

typedef struct _node {
    int id;
    string name;
    int color;
    int depth;
    int finish;
    struct _node *p;
} node;

int E[N][N] = {
    {0, 1, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0},
};

node V[N];
int count;
vector<node*> sorted;

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

string xxx[] = {"衬衣", "领带","夹克", "腰带","手表", "内裤", "裤子", "鞋", "袜子"};

void print_edge()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if (E[i][j] != 0)
                cout << V[i].name << "->" << V[j].name << endl;
        }
}

void dfs()
{
    node *u;

    init();
    print_edge();
    for (int i = 0; i < N; i++)
    {
        if (V[i].color == 0)
            dfs_visit(&V[i]);
    }
}

void init()
{
    count = 0;

    for (int i = 0; i < N; i++)
    {
        V[i].id = i;
        V[i].name = xxx[i];
        V[i].color = 0;
        V[i].p = NULL;
    }
}

void dfs_visit(node *u)
{
    node *v;

    printf("Found node %d\n", u->id);
    count += 1;
    u->depth = count;
    u->color = 1;
    for (int i = 0; i < N; i++)
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
    sorted.insert(sorted.begin(), u);
    count += 1;
    u->finish = count;
}

void print()
{
    for (int i = 0; i < N; i++)
    {
        printf("node-%d color-%d depth-%d finish-%d ",
                V[i].id, V[i].color, V[i].depth, V[i].finish);
        if (V[i].p)
            printf("p-%d", V[i].p->id);
        else
            printf("p-NULL");
        printf("\n");
    }

    for (auto it = sorted.begin(); it != sorted.end(); it++)
        cout << (*it)->name << "  ";
    cout << endl;
}
