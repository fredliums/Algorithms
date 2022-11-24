#include <stdio.h>
#include <stdlib.h>

/*
 * Longest simple path in a directed acyclic graph 
 */

void init(int n, int ***pG)
{
    *pG = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        (*pG)[i] = (int*)malloc(n * sizeof(int));

    int **G= *pG;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            G[i][j] = -1;

    G[0][1] = -1;
    G[0][2] = 1;
    G[1][2] = 1;
    G[2][3] = 1;
    G[2][4] = 3;
    G[3][4] = 1;
}

void print(int n, int **G)
{
    for (int i = 0; i < n;i++)
    {
        for(int j = 0; j < n; j++)
            printf("%2d ", G[i][j]);
        printf("\n");
    }
}

/*
 * i - start node
 * j - stop node
 * n - total of node
 */

int lspdag(int **G, int i, int j, int n)
{
    int m, tmp, max = -999;

    if (i == j)
        return 0;

    for (m = 0; m < n; m++)
    {
        if (G[i][m] > 0)
        {
            tmp = G[i][m] + lspdag(G, m, j, n);
            max = tmp > max ? tmp : max;
        }
    }

    return max;
}

int memoized_lspdag_aux(int **G, int i, int j, int n, int *c)
{
    int m, tmp, max = -999;

    if (c[i] > 0)
        return c[i];

    if (i == j)
        return 0;

    for (m = 0; m < n; m++)
    {
        if (G[i][m] > 0)
        {
            tmp = G[i][m] + memoized_lspdag_aux(G, m, j, n, c);
            max = tmp > max ? tmp : max;
        }
    }

    c[i] = max;
    return max;

}

int memoized_lspdag(int **G, int i, int j, int n)
{
    int ret, *c;

    c  = (int*)malloc(n * sizeof(int));
    c[n - 1] = 0;

    ret = memoized_lspdag_aux(G, i, j, n, c);


    for (int k = 0; k < n; k++)
        printf("%d ", c[k]);
    printf("\n");

    return ret;
}

int bottom_up_lspdag(int **G, int i, int j, int n)
{
    int l, t, k, *c;

    c  = (int*)malloc(n * sizeof(int));
    c[n - 1] = 0;

    for (l = 1; l < n; l++)
    {
        t = n - l;
        for (k = 0; k < n; k++)
        {
            if (G[k][j] > 0)
            {

            }
        }
    }
}

int main()
{
    int ret;
    int **G;

    init(5, &G);
    print(5, G);
    ret = lspdag(G, 0, 4, 5);
    printf("ret-%d\n", ret);
    ret = memoized_lspdag(G, 0, 4, 5);
    printf("ret-%d\n", ret);

    return 0;
}
