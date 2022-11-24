#include <stdio.h>

void print(int *A, int n);

int merge(int *A, int p, int q, int r)
{
    int i, j, k;
    int nL = q - p + 1;
    int nR = r - q;
    int L[nL], R[nR];

    if (A == NULL)
        return -1;

    for (i = 0; i < nL; i++)
        L[i] = A[p + i];

    for (j = 0; j < nR; j++)
        R[j] = A[q + j + 1];

    i = 0;
    j = 0;
    k = p;

    while(i < nL && j < nR)
        A[k++] = L[i] <= R[j] ? L[i++] : R[j++];

    while (i < nL)
        A[k++] = L[i++];

    while(j < nR)
        A[k++] = R[j++];

    return 0;
}

void print(int *A, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int sort(int *A, int p, int r)
{
    if (A == NULL)
        return -1;

    if (p < r)
    {
        int q = (p + r) / 2;
        sort(A, p, q);
        sort(A, q + 1, r);
        merge(A, p, q, r);
    }

    return 0;
}

int main()
{
//    int A[] = {1, 3, 5, 6, 7, 9, 2, 4, 6, 8, 10};
//    print(A, 11);
//    merge(A, 0, 5, 10);
//    print(A, 11);
    int A[] = {5, 2, 4, 7, 1, 3, 2, 6};
    print(A, 8);
    sort(A, 0, 7);
    print(A, 8);

    return 0;
}
