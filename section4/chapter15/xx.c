#include <stdio.h>
#include <stdlib.h>

int lcs(char *A, char *B, int m, int n)
{
    int i, j;
    int ai, bi, count;
    int maxai, maxbi, max = 0;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (A[i] == B[j])
            {
                count = 0;
                ai = i;
                bi = j;
                while(ai < m && bi < n && A[ai] == B[bi])
                {
                    count++;
                    ai++;
                    bi++;
                }
                if (count > max)
                {
                    max = count;
                    maxai = i;
                    maxbi = j;
                }
            }
        }
    }

    printf("ai-%d bi-%d max-%d\n", maxai, maxbi, max);

    return max;
}

void print(int **c, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%2d ", c[i][j]);
        printf("\n");
    }
}

int bottom_up_lcs(char *A, char *B, int m, int n)
{
    int i, j, maxai, maxbi;

    int **c;

    c = (int**)malloc((m + 1) * sizeof(int*));
    for (i = 0; i < m + 1; i++)
        c[i] = (int*)malloc((n + 1) * sizeof(int));

    for (i = 0; i <= m; i++)
        c[i][0] = 0;

    for (j = 0; j <= n; j++)
        c[0][j] = 0;

    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (A[i - 1] == B[j - 1])
            {
                c[i][j] = 1 + c[i - 1][j - 1];
                maxai = i;
                maxbi = j;
            }
            else
            {
                if (c[i - 1][j - 1] > c[i][j - 1])
                    c[i][j] = c[i - 1][j - 1];
                else
                    c[i][j] = c[i][j - 1];
            }
        }
    }

    printf("maxai-%d maxbi-%d\n", maxai, maxbi);
    print(c, m + 1, n + 1);

    return c[m][n];
}

int main()
{
    char A[] = "1234dsdf123";
    char B[] = "123ddf123";

    printf("A: %s\n", A);
    printf("B: %s\n", B);
    lcs(A, B, 11, 9);
    bottom_up_lcs(A, B, 11, 9);

    return 0;
}
