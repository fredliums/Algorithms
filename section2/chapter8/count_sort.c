#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(int *A, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void count_sort(int *A, int *B, int n, int max)
{
    int i, *C;
    
    C = (int*)malloc(max * sizeof(int));
    memset(C, 0, max * sizeof(int));

    for (i = 0; i < n; i++)
        C[A[i]] = C[A[i]] + 1;

    printf("Counting array:\n");
    print(C, max);

    for (i = 1; i <= max; i++)
        C[i] = C[i] + C[i - 1];

    printf("Less counting array:\n");
    print(C, max);

    for (i = n - 1; i >= 0; i--)
    {
        B[C[A[i]] - 1] = A[i];
        C[A[i]]--;
    }

    printf("Sorted array:\n");
    print(B, n);

    free(C);
}

int main()
{
    int A[10] = {1, 4, 5, 2, 3, 4, 2, 9, 12, 23};
    int B[10] = {};

    print(A, 10);
    count_sort(A, B, 10, 24);

    int C[5] = {3, 2, 2, 3, 4};
    int D[5] = {};

    print(C, 5);
    count_sort(C, D, 5, 10);

    return 0;
}
