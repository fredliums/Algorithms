#include "base.h"

int bubble_sort(int *A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (A[i] > A[j])
            {
                swap(&A[i], &A[j]);
            }
        }
    }

    return 0;
}
