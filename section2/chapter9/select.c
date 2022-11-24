#include <stdio.h>
#include "util.h"

void exchange(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int *A, int p, int r)
{
    int i, j, pivot;

    pivot = A[r];

    i = 0;
    j = 0;

    while (j < r)
    {
        if (A[j] < pivot)
            exchange(&A[i++], &A[j]);
        j++;
    }

    exchange(&A[i], &A[r]);

    return i;
}

int select(int *A, int p, int r, int i)
{
    int k, pivot;

    if (i > (r - p + 1))
        return -1;

    if (p == r)
        return A[p];

    pivot = partition(A, p, r);
    k = pivot - p + 1;

    if (i == k)
        return A[pivot];

    if (i > k)
        return select(A, pivot + 1, r, i - k);
    else 
        return select(A, p, pivot - 1, i);

    return 0;
}


int main()
{
    int A[20];

    randomA(A, 20);
    print(A, 20);
    partition(A, 0, 19);
    print(A, 20);
    printf(" i[%d] -- %d\n", 7, select(A, 0, 19, 7));

    return 0;
}
