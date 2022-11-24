#ifndef __TREE_H__
#define __TREE_H__

typedef struct node 
{
    struct node *p;
    struct node *left;
    struct node *sibling;
    int key;
    int data;
} node;

typedef struct tree
{
    node *root;
    int length;
} tree;

tree *tree_init(tree *s, int n);
int tree_insert(tree *s, int key, node *p);
int tree_delete(tree *s, int key);
int tree_list(tree s);

#endif
