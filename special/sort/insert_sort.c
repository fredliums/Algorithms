#include "base.h"

int insert_sort(int *A, int n)
{
    int i, j, key;

    for (j = 1; j < n; j++)
    {
        key = A[j];
        i = j - 1;
        while(i >= 0 && A[i] > key)
        {
            A[i + 1] = A[i];
            i--;
        }
        A[i + 1] = key;
    }

    return 0;
}
