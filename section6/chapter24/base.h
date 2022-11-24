#ifndef __BASE_H__
#define __BASE_h__

#define NODE_MAX_D  999
#define PATH1   "./x1.txt"

typedef struct _Node {
    int id;
    char name;
    int d;
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

Graph* init_graph(Graph *G);

#endif
