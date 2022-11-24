#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int find_min_max(int *A, int n, int *min, int* max);
int find_min_max_b(int *A, int n, int *min, int* max);

void print(int *A, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int find_min_max(int *A, int n, int *min, int* max)
{

    int i, minimum, maximum;

    if (!A || !min || !max)
        return -1;

    minimum = A[0];
    maximum = A[0];


    for (i = 0; i < n; i++)
    {
        if (A[i] > maximum)
            maximum = A[i];
        if (A[i] < minimum)
            minimum = A[i];
    }

    *min = minimum;
    *max = maximum;

    return 0;
}

int find_min_max_b(int *A, int n, int *min, int* max)
{
    int i, minimum, maximum;

    if (!A || !min || !max)
        return -1;

    minimum = A[0];
    maximum = A[0];

    for (i = 1; i < n - 1; i = i + 2)
    {
        if (A[i] < A[i + 1])
        {
            if (A[i] < minimum)
                minimum = A[i];
            if (A[i + 1] > maximum)
                maximum = A[i + 1];
        }
        else
        {
            if (A[i + 1] < minimum)
                minimum = A[i + 1];
            if (A[i] > maximum)
                maximum = A[i];
        }
    }

    if (i < n)
    {
        if (A[i] < minimum)
            minimum = A[i];
        if (A[i] > maximum)
            maximum = A[i];
    }

    *min =  minimum;
    *max = maximum;

    return 0;
}

int main()
{
    int i, min, max;
    int A[20];

    srand(time(NULL));
    for (i = 0; i < 20; i++)
        A[i] = random() % 1000;
    print(A, 20);

    find_min_max(A, 20, &min, &max);
    printf("min-%d max-%d\n", min, max);

    find_min_max_b(A, 20, &min, &max);
    printf("min-%d max-%d\n", min, max);

    return 0;
}
