#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrix.h"

Matrix*
init_matrix(Matrix *L, int m, int n)
{
    L->rows = m;
    L->cols = n;
    
    L->data = (int**)malloc(m * sizeof(int*));
    for(int i = 0; i < m; i++)
    {
        L->data[i] = (int*)calloc(n, sizeof(int));
    }

    return L;
}

Matrix*
new_matrix(int m, int n)
{
    Matrix *L = (Matrix*)malloc(sizeof(Matrix));
    init_matrix(L, m, n);

    return L;
}

Matrix*
copy_matrix(Matrix *L, Matrix *N)
{
    L->rows = N->rows;
    L->cols = N->cols;

    if (L->data == NULL)
        L->data = (int**)malloc(L->rows * sizeof(int*));
    for(int i = 0; i < L->rows; i++)
    {
        if (L->data == NULL)
            L->data[i] = (int*)malloc(L->cols * sizeof(int));
        for (int j = 0; j < L->cols; j++)
        {
            L->data[i][j] = N->data[i][j]; 
        }
    }

    return L;

}


Matrix*
set_matrix(Matrix *L, int value)
{
    if (L == NULL)
        return NULL;

    for (int i = 0; i < L->rows; i++)
        for (int j = 0; j < L->cols; j++)
            L->data[i][j] = value;
}

void
print(const Matrix *L)
{
    for (int i = 0; i < L->rows; i++)
    {
        for(int j = 0; j < L->cols; j++)
            printf("%3d ", L->data[i][j]);
        printf("\n");
    }
}

void
print_path(Matrix *PI, int i, int j)
{
    if (i == j)
        printf("%d", i);
    else if (PI->data[i][j] == -1)
    {
        printf("No path from %d to %d", i, j);
    }
    else
    {
        print_path(PI, i, PI->data[i][j]);
        printf("->%d", j);
    }
}


void
print_paths(Matrix *N, Matrix *PI)
{
    for(int i = 0; i < PI->rows; i++)
    {
        for(int j = 0; j < PI->cols; j++)
        {
            printf("%d -> %d [%2d]: ", i, j, N->data[i][j]);
            print_path(PI, i, j);
            printf("\n");
        }
    }
}

void
free_matrix(Matrix *L)
{
    if (L == NULL)
        return;

    for (int i = 0; i < L->rows; i++)
        free(L->data[i]);

    free(L->data);
    free(L);
}

int
add(int a, int b)
{
    if (a == MATRIX_MAX_W || b == MATRIX_MAX_W)
        return MATRIX_MAX_W;

    return a + b;
}
