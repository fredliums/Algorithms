#include "base.h"

int select_sort(int *A, int n)
{
    int i, j, min;

    for (i = 0; i < n; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (A[j] < A[min])
                min = j;
        }
        swap(&A[i], &A[min]);
    }

    return 0;
}
