#include <stdio.h>
#include <stdlib.h>

void print(int rows, int cols, int A[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }
}

void array_alloc(int ***C, int rows, int cols)
{
    *C = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < cols; i++)
        (*C)[i] = (int*)malloc(cols * sizeof(int));
}

void pprint(int rows, int cols, int **A)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }
}

int matrix_mul(int n, int A[n][n], int B[n][n], int ***C)
{
    int i, j, k;

    array_alloc(C, n, n);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            int c = 0;
            for (k = 0; k < n; k++)
            {
                c += c + A[i][k] * B[k][j];
            }
            (*C)[i][j] = c;
        }
    }

    return 0;
}

int recursive_mul(int n, int **A, int **B)
{
    int **C;

    if (n == 1)
        C[0][0] = A[0][0] * B[0][0];

    return 0;
}

int main()
{
    int A[2][2] = { 
        {1, 2},
        {3, 4}
    };
    int B[2][2] = {
        {4, 3},
        {2, 1}
    };
    int **C = NULL;

    print(2, 2, A);
    print(2, 2, B);
    matrix_mul(2, A, B, &C);
    pprint(2, 2, C);

    if(C)
        free(C);

    return 0;
}
