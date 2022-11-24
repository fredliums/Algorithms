#include <stdio.h>
#include "heap.h"

void min_heapify(int *A, int n, int i)
{
    int l, r, least;

    least = i;

    l = LEFT(i);
    if (l <= n && A[l] < A[i])
        least = l;

    r = RIGHT(i);
    if (r <= n && A[r] < A[least])
        least = r;

    if (least != i)
    {
        int tmp = A[i];
        A[i] = A[least];
        A[least] = tmp;
        min_heapify(A, n, least);
    }
}

int build_min_heap(int *A, int n)
{
    if (!A)
        return -1;

    for(int i = n / 2; i > 0; i--)
        min_heapify(A, n, i);

    return 0;
}

void min_heap_sort(int *A, int n)
{
    int tmp;

    build_min_heap(A, n);
    while (n > 1)
    {
        tmp = A[n];
        A[n] = A[1];
        A[1] = tmp;
        min_heapify(A, --n, 1);
    }
}

int main()
{
    int A[] = {0, 1, 10, 3, 4, 7, 8, 9, 6, 14, 16};
    int A2[] = {0, 1, 10, 3, 4, 7, 8, 9, 2, 14, 16};
    int B[] = {0, 16, 10, 8, 4, 7, 3, 9, 2, 1, 14};
    int B2[] = {0, 16, 10, 8, 4, 7, 3, 9, 2, 1, 14};

    printf("Original array(Partial heapify):\n");
    print(A, 10);
    min_heapify(A, 10, 2);
    printf("Minimum heapify:\n");
    print(A, 10);
    min_heap_sort(A2, 10);
    printf("Minimum heap sort:\n");
    print(A2, 10);

    printf("\n\n");

    printf("Original array(Out of order):\n");
    print(B, 10);
    build_min_heap(B, 10);
    printf("Minimum heap:\n");
    print(B, 10);
    min_heap_sort(B2, 10);
    printf("Minimum heap sort:\n");
    print(B2, 10);

    return 0;
}
