#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrix
{
    int rows;
    int cols;
} matrix;

void print(int **p, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", p[i][j]);
        printf("\n");
    }
}

void print_parens(int **s, int i, int j)
{
    if (i == j)
        printf("A%d", i);

    else
    {
        printf("(");
        print_parens(s, i, s[i][j]);
        print_parens(s, s[i][j] + 1, j);
        printf(")");
    }
}

int recursion_matrix(matrix *p, int i, int j)
{
    int k, tmp, min = 999999;

    if (i == j)
        return 0;

    for (k = i; k < j; k++)
    {
        tmp = recursion_matrix(p, i, k) + recursion_matrix(p, k + 1, j)
            + p[i].rows * p[k + 1].rows * p[j].cols;
        min = tmp < min ? tmp : min;
    }

    return min;
}

int memoized_matrix_aux(matrix *p, int i, int j, int **m)
{
    int k, tmp, min;

    if (m[i][j] > 0)
        return m[i][j];

    if (i == j)
        return 0;

    min = 999999;
    for (k = i; k < j; k++)
    {
        tmp = memoized_matrix_aux(p, i, k, m) + memoized_matrix_aux(p, k + 1, j, m)
            + p[i].rows * p[k].cols * p[j].cols;
        min = tmp < min ? tmp : min;
    }
    m[i][j] = min;

    return min;
}

int memoized_matrix(matrix *p, int n)
{
    int **m;

    m = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        m[i] = (int*)malloc(n * sizeof(int));
        m[i][i] = 0;
    }

    int ret = memoized_matrix_aux(p, 0, n - 1, m);
    print(m, 6);

    return ret;
}

int bottom_up_matrix(matrix *p, int n)
{
    int i, j, k, l;
    int tmp, min;
    int **m, **s;

    m = (int**)malloc(n * sizeof(int*));
    s = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        m[i] = (int*)malloc(n * sizeof(int));
        s[i] = (int*)malloc(n * sizeof(int));
        m[i][i] = 0;
    }

    /* Correct Steps:
     * 1. First for calc m[i, i + l], that means l is step length
     * 2. Second for iterate i = 0 -> n-l, that means start point with different step
     *    length, 0->5 with SL 1, 0-4 with SL 2
     * 3. Last for check i <= k < j, j = i + l
     */

    for (l = 1; l < n; l++)
    {
        for (i = 0; i < n - l; i++)
        {
            j = i + l;
            min = 99999;
            for (k = i; k < j; k++)
            {
                tmp = m[i][k] + m[k + 1][j]
                    + p[i].rows * p[k + 1].rows * p[j].cols;
                if (tmp < min)
                {
                    min = tmp;
                    m[i][j] = min;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("Price m[%d][%d]:\n", n, n);
    print(m, n);

    printf("Slip points s[%d][%d]:\n", n, n);
    print(s, n);

    printf("Optimal parens is: ");
    print_parens(s, 0, 5);
    printf("\n");

    return m[0][n - 1];
}

int main()
{
    int rst;

    matrix p[6];

    FILE *fp = fopen("./input.txt", "r");
    for (int i = 0; i < 6; i++)
        fscanf(fp, "%d,%d", &p[i].rows, &p[i].cols);
    fclose(fp);

    rst = recursion_matrix(p, 1, 4);
    printf("rst of <1, 4> is %d\n", rst);

    rst = memoized_matrix(p, 6);
    printf("rst of <0, 5> is %d\n", rst);

    rst = bottom_up_matrix(p, 6);
    printf("rst is %d\n", rst);

    return 0;
}
