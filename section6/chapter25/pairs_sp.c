#include <stdio.h>
#include "matrix/matrix.h"

Matrix* EXTEND_SHORTEST_PATHS(Matrix *L, Matrix *W, Matrix *N);
Matrix* SLOW_ALL_PAIRS_SHORTEST_PATHS(Matrix *W);
Matrix* FASTER_ALL_PAIRS_SHORTEST_PATHS(Matrix *W);
static int min(int a, int b);
static void init(Matrix *L);
static void print_path(int i, int j);
static void print_paths(Matrix *N);

int X[5][5] = {
    {0, 3, 8, 999, -4},
    {999, 0, 999, 1, 7},
    {999, 4, 0, 999, 999},
    {2, 999, -5, 0, 999},
    {999, 999, 999, 6, 0}
};

Matrix *PI;

int main()
{
    Matrix W;
    Matrix *L, *N;

    init(&W);
    PI = new_matrix(W.rows, W.cols);
    L = SLOW_ALL_PAIRS_SHORTEST_PATHS(&W);

    printf("Weights of shortest paths:\n");
    print(L);
    printf("Shortest paths:\n");
    print(PI);
    printf("Paths:\n");
    print_paths(L);

    set_matrix(PI, -1);
    N = FASTER_ALL_PAIRS_SHORTEST_PATHS(&W);

    printf("Weights of shortest paths:\n");
    print(N);

    /* This doesn't work
    printf("Shortest paths:\n");
    print(PI);

    printf("Paths:\n");
    print_paths(N);
    */

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

static void
print_path(int i, int j)
{
    if (i == j)
        printf("%d", i);
    else if (PI->data[i][j] == -1)
    {
        printf("No path from %d to %d", i, j);
    }
    else
    {
        print_path(i, PI->data[i][j]);
        printf("->%d", j);
    }
}


static void
print_paths(Matrix *N)
{
    for(int i = 0; i < PI->rows; i++)
    {
        for(int j = 0; j < PI->cols; j++)
        {
            printf("%d -> %d [%2d]: ", i, j, N->data[i][j]);
            print_path(i, j);
            printf("\n");
        }
    }
}

/*
 * L -- L(m)
 * W -- Original weight graph
 * N -- L(m + 1)Init equal to L every time
 */

Matrix*
EXTEND_SHORTEST_PATHS(Matrix *L, Matrix *W, Matrix *N)
{
    int m, m_index;

    for (int i = 0; i < L->rows; i++)
    {
        for (int j = 0; j < L->cols; j++)
        {
            m_index = -1;
            for (int k = 0; k < L->cols; k++)
            {
                m = L->data[i][k] + W->data[k][j]; 
                if (m < N->data[i][j])
                {
                    m_index = k;
                    N->data[i][j] = m;
                }
            }
 
            // Save precursor index for L[i, j]
            if (m_index != -1)
                PI->data[i][j] = m_index;
            /* Think about why need this.
             * This means i close to j and is the shortest path i -> j
             */
            else if (N->data[i][j] == W->data[i][j])
                PI->data[i][j] = i;
        }
    }

    return N;
}

Matrix*
FASTER_ALL_PAIRS_SHORTEST_PATHS(Matrix *W)
{
    int m = 1;
    Matrix *L, *N;

    L = new_matrix(W->rows, W->cols);
    N = new_matrix(W->rows, W->cols);
    copy_matrix(L, W);
    copy_matrix(N, W);

    while (m < W->rows - 1)
    {
        N = EXTEND_SHORTEST_PATHS(L, L, N);
        L = N;
        m *= 2;;
    }

    return N;
}

Matrix*
SLOW_ALL_PAIRS_SHORTEST_PATHS(Matrix *W)
{
    Matrix *L, *N;

    L = new_matrix(W->rows, W->cols);
    N = new_matrix(W->rows, W->cols);
    copy_matrix(L, W);
    copy_matrix(N, W);

    for (int i = 2; i < W->rows; i++)
    {
        N = EXTEND_SHORTEST_PATHS(L, W, N);
        L = N;
    }

    return N;
}


static int
min(int a, int b)
{
    int min = a < b ? a : b;

    if (min < (MATRIX_MAX_W >> 1))
        return min;

    return MATRIX_MAX_W;
}
