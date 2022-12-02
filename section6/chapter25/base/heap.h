#ifndef __HEAP_H__
#define __HEAP_H__

//index start from 0
#define PARENT(i)   ((i - 1) >> 1)
#define LEFT(i)     ((i << 1) + 1)
#define RIGHT(i)    (LEFT(i) + 1)

#define HEAP_MAX_KEY 999

typedef struct _Item {
    int d;
    void *padding;
} Item;

typedef struct _Heap {
    int length;
    int size; // max length of data
    Item *(*data);
} Heap;

Item* pop_min(Heap *H);
void min_heapify(Heap *H, int i);
void build_min_heap(Heap *H, int n);
int heap_length(Heap *H);

#endif
