#include <stdio.h>
#include "heap.h"

int get_max(Heap H);
int pop_max(Heap *H);
int increase_priority(Heap *H, int i, int key);
int insert(Heap *H, int key);

static void max_heapify(Heap *H, int i);
static inline void exchange(int *a, int *b);

int get_max(Heap H)
{
    return H.data[1];
}

int pop_max(Heap *H)
{
    int max;
    int *data = H->data;

    if (H->length < 1)
        return -1;

    max = data[1];
    data[1] = data[H->length];

    H->length--;
    max_heapify(H, 1);

    return max;
}

int insert(Heap *H, int key)
{
    H->length++;

    if (H->length > H->size)
    {
        printf("Max size overflow!\n");
        H->length--;
        return -1;
    }

    H->data[H->length] = -1;
    increase_priority(H, H->length, key);

    return 0;
}

int increase_priority(Heap *H, int i, int key)
{
    int *data = H->data;

    if (data[i] > key)
        return -1;

    data[i] = key;
    
    int p = PARENT(i);
    while(p >= 1 && data[p] < key)
    {
        exchange(&data[p], &data[i]); 
        i = p;
        p = PARENT(i);
    }

    return 0;
}

static void max_heapify(Heap *H, int i)
{
    int l, r, largest, tmp;
    int *data = H->data;

    largest = i;

    l = LEFT(i);
    if (l <= H->length && data[l] > data[largest])
        largest = l;

    r = RIGHT(i);
    if (r <= H->length && data[r] > data[largest])
        largest = r;

    if (largest != i)
    {
        tmp = data[largest];
        data[largest] = data[i];
        data[i] = tmp;
        max_heapify(H, largest);
    }
}

static inline void exchange(int *a, int *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

int main()
{
    int A[] = {0, 16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
    Heap h;
    h.data = A;
    h.length = sizeof(A) / sizeof(int) - 1;
    h.size = h.length;

    printf("Original array(Partial heapify):\n");
    print_h(h);
    max_heapify(&h, 2);
    printf("Maximum heapify:\n");
    print_h(h);
    for (int i = 0; i < 4; i++)
    {
        printf("Get max - %d\n", get_max(h));
        printf("Pop max - %d\n", pop_max(&h));
        print_h(h);
    }

    printf("Increase the key of %d to %d\n", 3, 10);
    increase_priority(&h, 3, 10);
    print_h(h);

    for (int i = 2; i < 7; i++)
    {
        printf("Insert key - %d\n", i * i);
        insert(&h, i * i);
        print_h(h);
    }

    return 0;
}
