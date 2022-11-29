#include <stdio.h>
#include "matrix/matrix.h"

Matrix* FLOYD_WARSHALL(Matrix *W, Matrix *PI);
static void init(Matrix *L);
static void init_pi(Matrix *L, Matrix *W);

int X[5][5] = {
    {0, 3, 8, 999, -4},
    {999, 0, 999, 1, 7},
    {999, 4, 0, 999, 999},
    {2, 999, -5, 0, 999},
    {999, 999, 999, 6, 0}
};


int main()
{
    Matrix W, PI;
    Matrix *L;

    init(&W);
    init_pi(&PI, &W);
    L = FLOYD_WARSHALL(&W, &PI);
    printf("Weight matrix:\n");
    print(L);
    printf("Shortest paths matrix:\n");
    print(&PI);
    printf("Shortest paths:\n");
    print_paths(L, &PI);

    free_matrix(L);

    return 0;
}

static void
init(Matrix *L)
{
    init_matrix(L, 5, 5);

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            L->data[i][j] = X[i][j];
}


/*
 * PI[i][j] = i if W[i][j] < MAX and i != j
 */
static void
init_pi(Matrix *PI, Matrix *W)
{
    init_matrix(PI, W->rows, W->cols);

    for (int i = 0; i < W->rows; i++)
    {
        for (int j = 0; j < W->cols; j++)
        {
            if (i == j || W->data[i][j] == MATRIX_MAX_W)
                PI->data[i][j] = -1;
            else
                PI->data[i][j] = i;
        }
    }
}

Matrix*
FLOYD_WARSHALL(Matrix *W, Matrix *PI)
{
    int min;
    Matrix *D, *DK, *P;

    D = new_matrix(W->rows, W->cols);
    DK = new_matrix(W->rows, W->cols);

    // Keep D for release
    P = D;

    // D[0] = W
    copy_matrix(D, W);
    // D[K] = D[0]
    copy_matrix(DK, W);

    for(int k = 0; k < W->cols; k++)
    {
        for (int i = 0; i < W->rows; i++)
        {
            for (int j = 0; j < W->cols; j++)
            {
                min = add(D->data[i][k], D->data[k][j]);
                if (min < D->data[i][j])
                {
                    DK->data[i][j] = min;
                    PI->data[i][j] = PI->data[k][j];
                }
            }
        }
        D = DK;
    }

    free_matrix(P);

    return D;
}

