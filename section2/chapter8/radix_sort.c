#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void print(int *A, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void radix_sort(int *A, int *B, int n, int d)
{
    int i, j, k, l;
    int T[10] = { 0 };

    for(i = 0; i < d; i++)
    {
        memset(T, 0, 10 * sizeof(int));
        for (j = 0; j < n; j++)
        {
            /* 245(1) => 4 = 245 / 10**1 % 10 */
            l = (A[j] / (int)pow(10, i)) % 10;
            T[l]++;
        }

        for (k = 1; k < 10; k++)
            T[k] = T[k] + T[k - 1];

        for (k = n - 1; k >= 0; k--)
        {
            l = A[k] / (int)pow(10, i) % 10;
            B[T[l] - 1] = A[k];
            T[l]--;
        }

        printf("Iterate %d: \n", i);
        print(B, n);

        /* !!! Must copy B to A */
        memcpy(A, B, n * sizeof(int));
    }
}

int main()
{
    int A[5] = {123, 322, 452, 123, 234};
    int B[5];

    radix_sort(A, B, 5, 3);
    print(B, 5);

    int C[30];
    int D[30];

    srandom(time(NULL));

    for (int i = 0; i < 30; i++)
        C[i] = random() % 1000;

    print(C, 30);
    radix_sort(C, D, 30, 3);
    print(D, 30);

    return 0;
}
