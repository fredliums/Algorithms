#ifndef __HEAP_H__
#define __HEAP_H__

#define PARENT(i)   (i >> 1)
#define LEFT(i)     (i << 1)
#define RIGHT(i)    ((i << 1) + 1)

typedef struct Heap {
    int length;
    int size; // max length of data
    int *data;
} Heap;

void print(int *A, int n);
void print_h(Heap H);

#endif
