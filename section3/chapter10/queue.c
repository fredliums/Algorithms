#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

queue* queue_init(queue *s, int n)
{
    if (!s || n < 1)
        return NULL;

    s->data = (int*)malloc((n + 1) * sizeof(int));
    s->length = 0;
    s->size = n;
    s->head = 0;
    s->tail = 0;

    return s;
}

int queue_enqueue(queue *s, int key)
{
    if (s->length >= s->size)
    {
        printf("Overflow!\n");
        return -1;
    }

    (s->data)[s->tail] = key;
    s->length++;

    s->tail++;
    if (s->tail == s->size)
        s->tail = 0;

    return 0;
}

int queue_dequeue(queue *s)
{
    int data;

    if (s->length == 0)
    {
        printf("Underflow!\n");
        return -1;
    }

    data = (s->data)[s->head];
    s->length--;

    s->head++;
    if (s->head == s->size)
        s->head = 0;

    return data;
}

int queue_empty(queue *s)
{
    return (s->length <= 0);
}

void queue_print(queue s)
{
    int i = s.head;

    if (s.length == 0)
    {
        printf("Empty queue!\n");
        return;
    }

    do {
        printf("%d ", (s.data)[i]);
        i = (i + 1) % s.size;
    } while(i != s.tail);
    printf("\n");
}
