#include <stdio.h>
#include "stack.h"

int main()
{
    stack s;

    stack_init(&s, 10);

    stack_push(&s, 3);
    stack_push(&s, 6);
    stack_push(&s, 9);
    stack_print(s);
    printf("Pop %d\n", stack_pop(&s));
    stack_print(s);

    return 0;
}
