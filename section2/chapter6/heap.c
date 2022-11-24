#include <stdio.h>
#include "heap.h"

void print(int *A, int n)
{
    for (int i = 1; i <= n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void print_h(Heap H)
{
    for (int i = 1; i <= H.length; i++)
        printf("%d ", H.data[i]);
    printf("\n");
}
