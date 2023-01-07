#include "base.h"

int shell_sort(int *A, int n)
{
    int i, j, gap;

    /* Gap n/2 -> 1 */
    for (gap = n / 2; gap > 0; gap /= 2)
    {
        /* Total gap groups */
        for (i = 0; i < gap; i++)
        {
            /* Insert sort for each group */
            for (j = i + gap; j < n; j += gap)
            {
                if (A[j] < A[j - gap])
                {
                    int x = A[j];
                    int k = j - gap;

                    while(k >=0 && A[k] > x)
                    {
                        A[k + gap] = A[k];
                        k -= gap;
                    }
                    A[k + gap] = x;
                }
            }
        }
    }
}

int shell_sort_b(int *A, int n)
{
    int i, j, gap, key;

    for (gap = n / 2; gap > 0; gap /= 2)
    {
        for (j = gap; j < n; j++)
        {
            if (A[j] < A[j - gap])
            {
                key = A[j];
                i = j - gap;
                while(i >= 0 && A[i] > key)
                {
                    A[i + gap] = A[i];
                    i -= gap;
                }
                A[i + gap] = key;
            }
        }
    }
}
