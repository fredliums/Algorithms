#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

stack* stack_init(stack *s, int n)
{
    if (!s || n < 1)
        return NULL;

    s->data = (int*)malloc(n * sizeof(int));
    s->length = 0;
    s->size = n;

    return s;
}

int stack_push(stack *s, int key)
{
    if (s->length >= s->size)
        return -1;

    /* Index counting from 0 */
    (s->data)[s->length++] = key;

    return 0;
}

int stack_pop(stack *s)
{
    if (s->length == 0)
        return -1;

    return (s->data)[--s->length];
}

int stack_empty(stack *s)
{
    return (s->length <= 0);
}

void stack_print(stack s)
{
    if (s.length == 0)
    {
        printf("Empty stack!\n");
        return;
    }

    for (int i = 0; i < s.length; i++)
        printf("%d ", (s.data)[i]);
    printf("\n");
}
