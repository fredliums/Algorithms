#include <queue>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

typedef struct _Node {
    int id;
    int color;
    char name;
    int depth;
    int finish;
    struct _Node *p;
} Node;

#define N 8

int E[N][N] = {
    {0, 1, 0, 0, 1, 0, 0, 0}, 
    {0, 0, 1, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 0},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0}
};

typedef struct _Graph {
    Node *V;
    int (*E)[N];
} Graph;

Node V[N];
int count;
vector<Node*> sorted; 
Graph G;

void init();
void dfs();
void dfs_visit(int E[N][N], Node *u);
void scc_visit(int ET[N][N], Node *u);
void print();
void scc();
void printe();

char name[] = {'c', 'g', 'f', 'h', 'd', 'b', 'a', 'e'};

int main()
{
    printe();
    dfs();
    scc();

    return 0;
}

void printe()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (E[i][j] == 1)
                cout << i << "->" << j << " ";
        }
        cout << endl;
    }


}

void dfs()
{
    Node *u;

    init();
    for (int i = 0; i < N; i++)
    {
        if (V[i].color == 0)
        {
            cout << "Component: " << endl;
            dfs_visit(E, &V[i]);
            cout << endl;
        }
    }
    for (auto it = sorted.begin(); it != sorted.end(); it++)
        cout << "[" << (*it)->id << "]" << (*it)->name << " ";
    cout << endl;
}

void dfs_visit(int E[N][N], Node *u)
{
    Node *v;

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
                dfs_visit(E, v);
            }
        }
    }
    u->color = 2;
    sorted.push_back(u);
    cout << "Node[" << u->id << "]-" << u->name << " ";
    count += 1;
    u->finish = count;
}

void scc()
{
    int ET[N][N] = { 0 };

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (E[i][j] == 1)
                ET[j][i] = 1;

    count = 0;
    for (auto it = sorted.begin(); it != sorted.end(); it++)
        (*it)->color = 0;

    for (auto it = sorted.rbegin(); it != sorted.rend(); it++)
    {
        if ((*it)->color == 0)
        {
            cout << "Strongly connected component: " << endl;
            scc_visit(ET, *it);
            cout << endl;
        }
    }
}

void scc_visit(int ET[N][N], Node *u)
{
    Node *v;

    count += 1;
    u->depth = count;
    u->color = 1;

    for (auto it = sorted.rbegin(); it != sorted.rend(); it++)
    {
        if (ET[u->id][(*it)->id] == 1)
        {
            v = *it;
            if (v->color == 0)
            {
                v->p = u;
                scc_visit(ET, v);
            }
        }
    }
    u->color = 2;
    cout << "Node[" << u->id << "]-" << u->name << " ";
    count += 1;
    u->finish = count;
}

void init()
{
    count = 0;

    for (int i = 0; i < N; i++)
    {
        V[i].id = i;
        V[i].color = 0;
        V[i].p = NULL;
        V[i].name = name[i];
    }
    G.V = V;
    G.E = E;
}

void print()
{
    for (int i = 0; i < N; i++)
    {
        printf("Node-[%d]%c color-%d depth-%d finish-%d ",
                V[i].id, V[i].name, V[i].color, V[i].depth, V[i].finish);
        if (V[i].p)
            printf("p-%d", V[i].p->id);
        else
            printf("p-NULL");
        printf("\n");
    }
}
