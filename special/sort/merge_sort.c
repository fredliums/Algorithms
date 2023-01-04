#include <stdlib.h>
#include "base.h"

static void merge(int *A, int p, int q, int r);
static void wmerge_sort(int *A, int start, int end);

int merge_sort(int *A, int n)
{
    wmerge_sort(A, 0, n - 1);

    return 0;
}

static void
merge(int *A, int p, int q, int r)
{
    int i, j, index;

    int *L = (int*)malloc((q - p + 1) * sizeof(int));
    int *R = (int*)malloc((r - q) * sizeof(int));

    /* A[p], A[p + 1], ..., A[q] */
    for (i = 0; i <= q - p; i++)
        L[i] = A[p + i];

    /* A[q + 1], A[q + 2], ..., A[r] */
    for (i = 0; i < r - q; i++)
        R[i] = A[q + i + 1];

    
    for (i = 0, j = 0, index = p; i <= q - p && j < r - q; index++)
    {
        if (L[i] <= R[j])
        {
            A[index] = L[i];
            i++;
        }
        else
        {
            A[index] = R[j];
            j++;
        }
    }

    while(i <= q - p)
        A[index++] = L[i++];

    while(j < r - q)
        A[index++] = R[j++];
}


static void
wmerge_sort(int *A, int start, int end)
{
    int pivot;

    if (start >= end)
        return;

    pivot = start + (end - start) / 2;

    wmerge_sort(A, start, pivot);
    wmerge_sort(A, pivot + 1, end);
    merge(A, start, pivot, end);
}
