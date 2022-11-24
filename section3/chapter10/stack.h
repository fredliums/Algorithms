#ifndef __STACK_H__
#define __STACK_H__

typedef struct stack
{
    int length;
    int size;
    int *data;
} stack;

stack *stack_init(stack *s, int n);
int stack_push(stack *s, int key);
int stack_pop(stack *s);
int stack_empty(stack *s);
void stack_print(stack s);

#endif
