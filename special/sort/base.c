#include <stdio.h>
#include "base.h"

void print(int *A, int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

