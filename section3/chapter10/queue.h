#ifndef __queue_H__
#define __queue_H__

typedef struct queue
{
    int length;
    int size;
    int head;
    int tail;
    int *data;
} queue;

queue *queue_init(queue *s, int n);
int queue_enqueue(queue *s, int key);
int queue_dequeue(queue *s);
int queue_empty(queue *s);
void queue_print(queue s);

#endif
