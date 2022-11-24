#include <stdio.h>
#include "util.h"

int test(int *A, int n, int i)
{
    int k, min, max;
    int mk = 0, xk = 0;

    min = A[0];
    max = A[0];

    for (k = 1; k < n; k++)
    {
        if (A[k] >= max)
        {
            xk++;
        }
        if (A[k] <= min)
        {
            mk++;
        }

        printf("A[k]-%d min-%d mk-%d max-%d xk-%d\n",
                A[k], min, mk, max, xk);
    }

    return 0;
}

int main()
{
    int A[10];

    randomA(A, 10);
    print(A, 10);
    test(A, 10, 4);

    return 0;
}
