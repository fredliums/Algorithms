#include <stdio.h>
#include <stdlib.h>

void print(float **e, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
            printf("%.2f ", e[i][j]);
        printf("\n");
    }
}

void printr(int **r, int n)
{
    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%2d ", r[i][j]);
        printf("\n");
    }
}

void showr(int **r, int i, int j)
{
    if (i > j)
        return;

    printf("%d ", r[i][j]);
    printf("left: ");
    showr(r, i, r[i][j] - 1);
    printf("right: ");
    showr(r, r[i][j] + 1, j);
}

float w2(float *p, float *q, int i, int j)
{
    float ret;

    if (j < i - 1)
        return 0;
    
    if (j == i - 1)
        return q[i - 1];

    ret = q[i - 1];
    for (int k = i; k <= j; k++)
        ret = ret + p[k] + q[k];

    return ret;
}

float w(float *p, float *q, int i, int j)
{
    if (j < i - 1)
        return 0;
    
    if (j == i - 1)
        return q[i - 1];

    return w(p, q, i, j - 1) + p[j] + q[j];

}

float recursive_obst(float *p, float *q, int i, int j)
{
    int r;
    float tmp, min = 9999;

    if (j == i - 1)
        return q[i - 1];

    for (r = i; r <= j; r++)
    {
        tmp = recursive_obst(p, q, i, r - 1) + recursive_obst(p, q, r + 1, j)
            + w(p, q, i, j);
        min = tmp < min ? tmp : min;
    }

    return min;
}

float memoizei_obst_aux(float *p, float *q, int i, int j, float **e)
{
    int r;
    float tmp, min = 9999;

    if (e[i][j] > 0)
        return e[i][j];

    if (j == i - 1)
        return q[i - 1];

    for (r = i; r <= j; r++)
    {
        tmp = recursive_obst(p, q, i, r - 1) + recursive_obst(p, q, r + 1, j)
            + w(p, q, i, j);
        min = tmp < min ? tmp : min;
    }

    e[i][j] = min;
    return min;

}

float memoizei_obst(float *p, float *q, int n)
{
    int k;
    float **e;

    e = (float**)malloc(n * sizeof(float*));
    for (k = 0; k < n; k++)
        e[k] = (float*)malloc(n * sizeof(float));

    for (k = 1; k < n; k++)
        e[k][k - 1] = q[k - 1];

    return memoizei_obst_aux(p, q, 1, n - 1, e);
}

float bottom_up_obst(float *p, float *q, int n)
{
    int i, j, k, l;
    float tmp, min;
    float **e, **w;
    int **r;

    e = (float**)malloc((n + 1) * sizeof(float*));
    w = (float**)malloc((n + 1) * sizeof(float*));
    r = (int**)malloc(n * sizeof(int*));
    for (k = 0; k < n; k++)
    {
        e[k] = (float*)malloc(n * sizeof(float));
        w[k] = (float*)malloc(n * sizeof(float));
        r[k] = (int*)malloc(n * sizeof(int));
    }
    e[k] = (float*)malloc(n * sizeof(float));
    w[k] = (float*)malloc(n * sizeof(float));

    for (k = 1; k < n + 1; k++)
    {
        e[k][k - 1] = q[k - 1];
        w[k][k - 1] = q[k - 1];
    }

    /* 
     * l is the length of e[i, j]
     * e.g. e[1, 1], l is 1
     * l = 1 -> n - 1
     * i = 1 -> n - l
     * j = i + l - 1
     * k = i > j
     */
    for (l = 1; l < n; l++)
    {
        for (i = 1; i <= n - l; i++)
        {
            j = i + l - 1;
            min = 99999;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (k = i; k <= j; k++)
            {
                tmp = e[i][k - 1] + e[k + 1][j] + w[i][j];
                if (tmp < min)
                {
                    min = tmp;
                    e[i][j] = min;
                    r[i][j] = k;
                }
            }
        }
    }

    print(e, 7, 6);
    printr(r, 6);
    printf("r is: ");
    showr(r, 1, 5);
    printf("\n");
    return e[1][n - 1];
}

int main()
{
    float ret = 0;

    float P[] = {0, 0.15, 0.10, 0.05, 0.10, 0.20}; 
    float Q[] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};

    printf("w(2, 5) - %f\n", w(P, Q, 2, 5));
    printf("w2(2, 5) - %f\n", w2(P, Q, 2, 5));

    printf("e(1, 5) - %f\n", recursive_obst(P, Q, 1, 5));
    printf("memoizei_obst - %f\n", memoizei_obst(P, Q, 6));
    printf("bottom_up_obst - %f\n", bottom_up_obst(P, Q, 6));

    return 0;
}
