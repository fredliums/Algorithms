#include "base.h"

#define PARENT(i)   (i >> 1)
#define LEFT(i)     (i << 1)
#define RIGHT(i)    (LEFT(i) + 1)

static void MAX_HEAPIFY(int *A, int n, int i)
{
    int l, r, largest = i;

    l = LEFT(i);
    if (l <= n && A[l] > A[i])
        largest = l;

    r = RIGHT(i);
    if (r <= n && A[r] > A[largest])
        largest = r;

    if (largest != i)
    {
        swap(&A[i], &A[largest]);
        MAX_HEAPIFY(A, n, largest);
    }
}

static void BUILD_MAX_HEAP(int *A, int n)
{
    for (int i = n / 2; i > 0; i--)
        MAX_HEAPIFY(A, n, i);
}

int heap_sort(int *A, int n)
{
    BUILD_MAX_HEAP(A, n);
    while (n > 1)
    {
        swap(&A[1], &A[n]);
        MAX_HEAPIFY(A, --n, 1);
    }
}

