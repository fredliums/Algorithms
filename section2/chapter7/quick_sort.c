#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print(int *A, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}


void exchange(int *a, int *b)
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int *A, int p, int q)
{
    int small, big;
    int pivot;

    pivot = A[q];
    small = p;
    big = p;

    while (big < q)
    {
        if(A[big] < pivot)
        {
            if (small < big)
                exchange(&A[small], &A[big]);
            small++;
        }
        big++;
    }

    exchange(&A[small], &A[q]);

    return small;
}

void quick_sort(int *A, int p, int r)
{
    int pivot;
    
    if (p < r)
    {
        pivot = partition(A, p, r);
        quick_sort(A, p, pivot - 1);
        quick_sort(A, pivot + 1, r);
    }
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
        exchange(&A[pivot], &A[r]);

    /* 
     * Partition first
     * |----i|-----j|---pending----|r|
     */
    while(j < r)
    {
        if (A[j] < A[r])
        {
            if (i < j)
                exchange(&A[i], &A[j]);
            i++;
        }
        j++;
    }
    exchange(&A[i], &A[r]);
    
    /* Recursive sort p to i */
    quick_sort_b(A, p, i - 1);

    /* Recursive sort i to r */
    quick_sort_b(A, i + 1, r);
}

int main()
{
    int A1[] = {1, 2, 5, 7, 3, 9, 8, 6};
    int A2[] = {1, 2, 5, 7, 3, 9, 8, 6};
    int A3[] = {1, 2, 5, 7, 3, 9, 8, 6, 6, 2, 3, 6};

    print(A1, 8);
    partition(A1, 0, 7);
    print(A1, 8);

    printf("\n");

    print(A2, 8);
    quick_sort(A2, 0, 7);
    print(A2, 8);

    printf("\n");

    print(A3, 12);
    quick_sort_b(A3, 0, 11);
    print(A3, 12);

    return 0;
}
