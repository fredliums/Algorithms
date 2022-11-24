#include <stdio.h>

int select_sort(int *A, int n)
{
    int i, j, max;

    for (i = 0; i < n; i++)
    {
        max = i;
        for (j = i + 1; j < n; j++)
        {
            if(A[j] > A[max])
                max = j;
        }

        if (max != i)
        {
            A[max] = A[max] + A[i];
            A[i] = A[max] - A[i];
            A[max] = A[max] - A[i];
        }
    }

    return 0;
}

void print(int *A, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main()
{
    int A[] = {3, 2, 1, 7, 3, 4, 9, 8};

    print(A, 8);
    select_sort(A, 8);
    print(A, 8);

    return 0;
}
