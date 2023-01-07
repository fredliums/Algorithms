#include <stdlib.h>
#include <time.h>
#include "base.h"

static int partion(int *A, int p, int r);
static void sort(int *A, int p, int r);
void quick_sort_b(int *A, int p, int r);

int quick_sort(int *A, int n)
{
    quick_sort_b(A, 0, n - 1);
    //sort(A, 0, n - 1);
}

static void sort(int *A, int p, int r)
{
    int pivot;

    if (p >= r)
        return;

    pivot = partion(A, p, r);
    sort(A, p, pivot - 1);
    sort(A, pivot + 1, r);
}

static int partion(int *A, int p, int r)
{
    int i, j;
    int x, pivot;

    srandom(time(NULL));
    pivot = (random() % (r - p + 1)) + p;
    x = A[pivot];

    swap(&A[pivot], &A[r]);
    for (i = p, j = p; j < r; j++)
    {
        if (A[j] < x)
        {
            if (i != j)
            {
                swap(&A[i], &A[j]);
            }
            i++;
        }
    }

    swap(&A[i], &A[r]);

    return i;
}

void quick_sort_b(int *A, int p, int r)
{
    int i = p, j = p;
    int pivot;

    if (p >= r)
        return;

    /* Generate pivot randomly */
    srandom(time(NULL));
    pivot = random() % (r - p) + p;
    if (pivot != r)
        swap(&A[pivot], &A[r]);

    /* 
     * Partition first
     * |----i|-----j|---pending----|r|
     */
    while(j < r)
    {
        if (A[j] < A[r])
        {
            if (i < j)
                swap(&A[i], &A[j]);
            i++;
        }
        j++;
    }

    /* Set the pivot to right place */
    swap(&A[i], &A[r]);
    
    /* Recursive sort p to i */
    quick_sort_b(A, p, i - 1);

    /* Recursive sort i to r */
    quick_sort_b(A, i + 1, r);
}


