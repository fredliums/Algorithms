#include <stdio.h>
#include "matrix/matrix.h"

Matrix* FLOYD_WARSHALL(Matrix *W);
static void init(Matrix *L);

int X[5][5] = {
    {0, 3, 8, 999, -4},
    {999, 0, 999, 1, 7},
    {999, 4, 0, 999, 999},
    {2, 999, -5, 0, 999},
    {999, 999, 999, 6, 0}
};

int main()
{
    Matrix W;
    Matrix *L;

    init(&W);
    L = FLOYD_WARSHALL(&W);
    print(L);

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

Matrix*
FLOYD_WARSHALL(Matrix *W)
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
                min = D->data[i][k] + D->data[k][j];
                if (min < D->data[i][j])
                {
                    DK->data[i][j] = min;
                }
            }
        }
        D = DK;
    }

    free_matrix(P);

    return D;
}

