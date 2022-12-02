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
    int w;
    struct _ENode *next;
} ENode;

typedef struct _Graph {
    int number;
    Node *V;
    ENode *E;
} Graph;

Graph* init_graph(Graph *G, char *path);
int weight(Graph *G, int u, int v);
void INITIALIZE_SINGLE_SOURCE(Graph *G, int s);
void RELAX(Graph *G, int u, int v);
void PRINT_PATH(Graph *G, int s, int v);
void PRINT_EDGES(Graph *G);

int BELLMAN_FORD(Graph *G, int s);
void DIJKSTRA(Graph *G, int s);

#endif
