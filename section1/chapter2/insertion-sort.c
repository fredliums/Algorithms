#include <stdio.h>

int sort(int *A, int n)
{
    int i, j, key;

    if (A == NULL)
        return -1;

    for (j = 1; j < n; j++)
    {
        key = A[j];
        i = j - 1;

        while(i >= 0 && A[i] > key)
        {
            A[i + 1] = A[i];
            i = i -1;
        }
        A[i + 1] = key;
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
    int a[] = {5, 2, 4, 6, 1, 3};
    print(a, 6);
    sort(a, 6);
    print(a, 6);

    return 0;
}
