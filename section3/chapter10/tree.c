#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

tree *tree_init(tree *s, int n)
{
    int i, flag;

    node *p, *pp, *new;

    if (!s || n < 1)
        return NULL;

    s->root = (node*)malloc(sizeof(node));
    s->length = n;

    s->root->p = NULL;
    s->root->sibling = NULL;
    s->root->key = 0;
    printf("Data of root: ");
    scanf("%d", &s->root->data);

    p = (node*)malloc(sizeof(node));
    printf("Left child of root: ");
    scanf("%d", &p->data);
    p->p = s->root;
    s->root->left = p;
    p->key = 1;

    pp = s->root;

    for (i = 2; i < n; i++)
    {
        new = (node*)malloc(sizeof(node));
        new->key = i;
        printf("Data of %d: ", new->key);
        scanf("%d", &new->data);
        printf("sibling of [%d](1/0): ", p->key);
        scanf("%d", &flag);

        if (flag == 1)
        {
            p->sibling = new;
            new->p = p->p;
            p = new;
        }
        else
        {
            p->sibling = NULL;
            p = pp->left;
            while(pp)
            {
                while(p)
                {
                    printf("child of [%d](1/0): ", p->key);
                    scanf("%d", &flag);
                    if (flag == 1)
                        break;
                    p->left = NULL;
                    p = p->sibling;
                }
                pp = pp->sibling;
            }
            p->left = new;
            new->p = p;
        }    
    }

    p->left = NULL;
    p->sibling = NULL;
}

int tree_insert(tree *s, int key, node *p)
{}

int tree_delete(tree *s, int key)
{}

int tree_list(tree s)
{}
