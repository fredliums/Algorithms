#include <stddef.h>
#include "heap.h"

int heap_length(Heap *H)
{
    return H->length;
}

Item* pop_min(Heap *H)
{
    Item *min, *(*data);
    int last = H->length - 1;

    if (!H || H->length < 1)
        return NULL;

    data = H->data;
    min = data[0];

    data[0] = data[last];
    data[last] = NULL;
    H->length--;
    min_heapify(H, 0);

    return min;
}

void min_heapify(Heap *H, int i)
{
    int l, r, min;
    Item *tmp, *(*data);

    if (!H)
        return;

    data = H->data;
    min = i;

    l = LEFT(i);
    if (l < H->length && data[l]->key < data[min]->key)
        min = l;

    r = RIGHT(i);
    if (r < H->length && data[r]->key < data[min]->key)
        min = r;

    if (min != i)
    {
        tmp = data[min];
        data[min] = data[i];
        data[i] = tmp;
        min_heapify(H, min);
    }
}

void build_min_heap(Heap *H, int n)
{
    if (!H)
        return;

    int begin = (heap_length(H) - 1) / 2;

    for (int i = begin; i >= 0; i--)
    {
        min_heapify(H, i);
    }
}
