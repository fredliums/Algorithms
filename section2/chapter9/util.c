#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void print(int *A, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int randomA(int *A, int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        A[i] = random() % 1000;

    return 0;
}
