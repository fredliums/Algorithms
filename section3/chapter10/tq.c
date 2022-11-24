#include <stdio.h>
#include "queue.h"

int main()
{
    queue q;

    queue_init(&q, 10);

    queue_enqueue(&q, 3);
    for (int i = 0; i < 12; i++)
    {
        queue_enqueue(&q, i);
        queue_print(q);
    }
    for (int i = 0; i < 12; i++)
    {
        printf("dequeue %d\n", queue_dequeue(&q));
        queue_print(q);
    }

    return 0;
}
