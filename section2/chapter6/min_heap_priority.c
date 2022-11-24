#include <stdio.h>
#include "heap.h"

int get_min(Heap H);
int pop_min(Heap *H);
int decrease_priority(Heap *H, int i, int key);
int insert(Heap *H, int key);

/* better version */
int change_priority(Heap *H, int i, int key);
int insert_b(Heap *H, int key);

static void min_heapify(Heap *H, int i);

#define MAX_KEY 999

int get_min(Heap H)
{
    return H.data[1];
}

int pop_min(Heap *H)
{
    int min;
    int *data;

    if (!H || H->length < 1)
        return -1;

    data = H->data;
    min = data[1];

    data[1] = data[H->length];
    H->length--;
    min_heapify(H, 1);

    return min;
}

int decrease_priority(Heap *H, int i, int key)
{
    int p, tmp;
    int *data = H->data;

    if (data[i] < key || i > H->length)
        return -1;
    
    data[i] = key;

    p = PARENT(i);

    while(p >= 1 && data[p] > data[i])
    {
        tmp = data[p];
        data[p] = data[i];
        data[i] = tmp;
        i = p;
        p = PARENT(p);
    }

    return 0;
}

int insert(Heap *H, int key)
{
    if ((H->length + 1) > H->size)
    {
        printf("Heap overflow!\n");
        return -1;
    }

    H->length++;

    (H->data)[H->length] = MAX_KEY;

    decrease_priority(H, H->length, key);

    return 0;
}

int change_priority(Heap *H, int i, int key)
{
    int p, tmp;
    int *data = H->data;

    if (i > H->length)
        return -1;
    
    if (data[i] < key)
    {
        data[i] = key;

        p = PARENT(i);

        while(p >= 1 && data[p] > data[i])
        {
            tmp = data[p];
            data[p] = data[i];
            data[i] = tmp;
            i = p;
            p = PARENT(p);
        }
    }

    if (data[i] > key)
    {
        min_heapify(H, i);
    }

    return 0;
}

int insert_b(Heap *H, int key)
{
    return 0;
}

static void min_heapify(Heap *H, int i)
{
    int l, r, min;
    int tmp, *data;

    if (!H)
        return;

    data = H->data;
    min = i;

    l = LEFT(i);
    if (l <= H->length && data[l] < data[min])
        min = l;

    r = RIGHT(i);
    if (r <= H->length && data[r] < data[min])
        min = r;

    if (min != i)
    {
        tmp = data[min];
        data[min] = data[i];
        data[i] = tmp;
        min_heapify(H, min);
    }
}

int main()
{
    int A[] = {0, 1, 10, 3, 4, 7, 8, 9, 6, 14, 16};
    Heap h;

    h.data = A;
    h.length = sizeof(A) / sizeof(int) - 1;
    h.size = h.length;

    printf("Original array(Partial heapify):\n");
    print_h(h);
    min_heapify(&h, 2);
    printf("Minimum heapify:\n");
    print_h(h);
    printf("Decrease ker of %d to %d\n", 5, 2);
    decrease_priority(&h, 5, 2);
    print_h(h);
    for (int i = 1; i <= 3; i++)
    {
        printf("Pop min %d\n", get_min(h));
        pop_min(&h);
        print_h(h);
    }
    for(int i = 3; i >= 0; i--)
    {
        printf("Insert key %d\n", i * i);
        insert(&h, i * i);
        print_h(h);
    }

    return 0;
}
