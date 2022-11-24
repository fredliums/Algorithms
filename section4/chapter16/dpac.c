#include <stdio.h>
#include <stdlib.h>

void print (int **c, int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%2d ", c[i][j]);
        printf("\n");
    }
}

void printa(int **act, int i, int j)
{
    if (i >= j)
        return;
    
    printf("%d ", act[i][j]);
    printa(act, i, act[i][j]);
}

int rcs(int *s, int *f, int i, int j)
{
    int index, k, tmp, max = 0;

    if (i >= j)
        return 0;

    for (k = i + 1; k < j; k++)
    {
        if (s[k] >= f[i] && f[k] <= s[j])
        {
            tmp = 1 + rcs(s, f, i, k) + rcs(s, f, k, j);
            if (tmp > max)
            {
                max = tmp;
                index = k;
            }
        }
    }

    if (max > 0)
        printf("max of [%d, %2d]-%d index-%d\n", i, j, max, index);

    return max;
}

int lcs(int *s, int *f, int n)
{
    int i, j, k, tmp;
    int **c, **act;

    c = (int**)malloc((n + 1) * sizeof(int*));
    act = (int**)malloc((n + 1) * sizeof(int*));
    for (k = 0; k < n + 1; k++)
    {
        c[k] = (int*)malloc((n + 1) * sizeof(int));
        act[k] = (int*)malloc((n + 1) * sizeof(int));
    }

    for (j = 1; j <= n; j++)
    {
        for (i = 0; i < j; i++)
        {
            for (k = i + 1; k < j; k++)
            {
                if (f[i] <= s[k] && f[k] <= s[j])
                {
                    tmp = c[i][k] + c[k][j] + 1;
                    if (tmp > c[i][j])
                    {
                        c[i][j] = tmp;
                        act[i][j] = k;
                    }
                }
            }
        }
    }

    printf("c:\n");
    print(c, n + 1);
    printf("act:\n");
    print(act, n + 1);
    printf("activities: ");
    printa(act, 0, n);
    printf("\n");

    return c[0][n + 1];
}

int main()
{
    int ret;

    int s[] = {0, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12, 99};
    int f[] = {0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16, 99};

    ret = lcs(s, f, 12);
    printf("ret-%d\n", ret);
    
    ret = rcs(s, f, 0, 12);
    printf("ret-%d\n", ret);
    /*
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 13; j++)
            printf("%d ", r[i][j]);
        printf("\n");
    }
    */

    return 0;
}
