#ifndef __BASE_H__
#define __BASE_h__

#define NODE_MAX_D  999

typedef struct _Node {
    int d;
    int id;
    char name;
    int color;
    struct _Node *pi;
} Node;

typedef struct _ENode {
    int id;
    int f;
    int c;
    struct _ENode *next;
} ENode;

typedef struct _Graph {
    int number;
    Node *V;
    ENode *E;
} Graph;

Graph* init_graph(Graph *G, char *path);
Graph* new_graph(Graph *G);
int weight(ENode *es, int u, int v);
ENode* get_edge(Graph *G, int u, int v, int create);

#endif
