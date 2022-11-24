#include <stdio.h>
#include "heap.h"

int get_max(Heap *A);
int pop_max(Heap *A);
int increase_key(Heap *A, int i, int key);
int insert(Heap *A, int key);

void max_heapify(int *A, int n, int i)
{
    int l, r, largest, temp;

    largest = i;

    l = LEFT(i);
    if (l <= n && A[l] > A[largest])
        largest = l;

    r = RIGHT(i);
    if (r <= n && A[r] > A[largest])
        largest = r;

    if (largest != i)
    {
        temp = A[largest];
        A[largest] = A[i];
        A[i] = temp;
        max_heapify(A, n, largest);
    }
}

int build_max_heap(int *A, int n)
{
    if (!A)
        return -1;

    for (int i = n / 2; i > 0; i--)
    {
        max_heapify(A, n, i);
    }

    return 0;
}

void max_heap_sort(int *A, int n)
{
    build_max_heap(A, n);

    while(n > 1)
    {
        int tmp = A[n];
        A[n] = A[1];
        A[1] = tmp;
        max_heapify(A, --n, 1);
    }
}

int get_max(Heap *A)
{
    return 0;
}

int pop_max(Heap *A)
{
    return 0;
}

int increase_key(Heap *A, int i, int key)
{
    return 0;
}

int insert(Heap *A, int key)
{
    return 0;
}

int main()
{
    int A[] = {0, 16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
    int A2[] = {0, 16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
    int B[] = {0, 4, 2, 8, 16, 9, 7, 3, 2, 10, 14};
    int B2[] = {0, 4, 2, 8, 16, 9, 7, 3, 2, 10, 14};

    printf("Original array(Partial heapify):\n");
    print(A, 10);
    max_heapify(A, 10, 2);
    printf("Maximum heapify:\n");
    print(A, 10);
    max_heap_sort(A2, 10);
    printf("Maximum heap sort:\n");
    print(A2, 10);

    printf("\n\n");

    printf("Original array(Out of order):\n");
    print(B, 10);
    build_max_heap(B, 10);
    printf("Maximum heap:\n");
    print(B, 10);
    max_heap_sort(B2, 10);
    printf("Maximum heapify:\n");
    print(B2, 10);

    return 0;
}
