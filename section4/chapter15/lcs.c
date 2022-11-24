#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int count = 0;

void printi(int **C, int i, int j)
{
    for (int r = 0; r < i; r++)
    {
        for(int c = 0; c < j; c++)
            printf("%2d ", C[r][c]);
        printf("\n");
    }
}

void printc(char **C, int i, int j)
{
    for (int r = 0; r < i; r++)
    {
        for(int c = 0; c < j; c++)
            if(!C[r][c])
                printf("%2c", '-');
            else
                printf("%2c", C[r][c]);
        printf("\n");
    }
}


/*
 * i - length of X
 * j - length of Y
 */
int recursion_lcs(char *X, char *Y, int i, int j)
{
    int xl, yl;

    if (i == 0 || j == 0)
        return 0;

    if (X[i] == Y[j])
        return 1 + recursion_lcs(X, Y, i - 1, j - 1);

    xl = recursion_lcs(X, Y, i - 1, j);
    yl = recursion_lcs(X, Y, i, j - 1);

    return xl > yl ? xl : yl;
}

int memoized_lcs_aux(char *X, char *Y, int i, int j, int **C)
{
    int xl, yl;

    if (C[i][j] > 0)
        return C[i][j];

    count++;

    if (i == 0 || j == 0)
        return 0;

    if (X[i] == Y[j])
    {
        xl = 1 + memoized_lcs_aux(X, Y, i - 1, j - 1, C);
        C[i][j] = xl;

        return xl;
    }

    xl = memoized_lcs_aux(X, Y, i - 1, j, C);
    yl = memoized_lcs_aux(X, Y, i, j - 1, C);

    C[i][j] = xl > yl ? xl : yl;

    return C[i][j];

}

int memoized_lcs(char *X, char *Y, int i, int j)
{
    int ret;

    int **C = (int**)malloc((i + 1) * sizeof(int*));
    for (int k = 0; k < j; k++)
    {
        C[k] = (int*)malloc((j + 1) * sizeof(int));
        for (int n = 0; n < j + 1; n++)
            C[k][n] = -1;
    }

    ret = memoized_lcs_aux(X, Y, i, j, C);

    printi(C, i + 1, j + 1);
    
    printf("count - %d\n", count);

    return ret;
}

void print_lcs(char *X, int **b, int i, int j)
{
    if (i == 0 || j == 0)
        return;

    if (b[i][j] == 1)
    {
        print_lcs(X, b, i - 1, j - 1);
        printf("%c", X[i]);
    }
    else if (b[i][j] == 2)
        print_lcs(X, b, i - 1, j);
    else
        print_lcs(X, b, i, j - 1);
}

int bottom_up_lcs(char *X, char *Y, int i, int j)
{
    int k, m, n;

    int **b = (int**)malloc((i + 1) * sizeof(int*));
    int **c = (int**)malloc((i + 1) * sizeof(int*));

    for (k = 0; k < j; k++)
    {
        b[k] = (int*)malloc((j + 1) * sizeof(int));
        c[k] = (int*)malloc((j + 1) * sizeof(int));
    }

    for (k = 0; k < i; k++)
        c[k][0] = 0;

    for (k = 0; k < j; k++)
        c[0][k] = 0;

    for (m = 1; m <= i; m++)
    {
        for (n = 1; n <= j; n++)
        {
            if (X[m] == Y[n])
            {
                c[m][n] = 1 + c[m - 1][n - 1];
                b[m][n] = 1; // 1 - means shoud go top-left
            }
            else if (c[m - 1][n] >= c[m][n - 1])
            {
                c[m][n] = c[m - 1][n];
                b[m][n] = 2; // 2- means should go up
            }
            else
            {
                c[m][n] = c[m][n - 1];
                b[m][n] = 3; // 3 - means should go left
            }
        }
    }

    printf("c: \n");
    printi(c, i + 1, j + 1);
    printf("b: \n");
    printi(b, i + 1, j + 1);


    /* Print LCS */
    printf("LCS(Reverse Order): ");
    m = i;
    n = j;
    while (m > 0 && n > 0)
    {
        if (b[m][n] == 1)
        {
            printf("%c", X[m]);
            m--;
            n--;
        }
        else if(b[m][n] == 2)
            m--;
        else
            n--;
    }
    printf("\n");


    printf("LCS(Positive order): ");
    print_lcs(X, b, i, j);
    printf("\n");

    return c[i][j];
}

int main()
{
    int rst;

    char *X = " ABCBDAB";
    char *Y = " BDCABACB";

    printf("X - %s\n", X);
    printf("Y - %s\n", Y);

    rst = recursion_lcs(X, Y, 7, 8);
    printf("rst - %d\n", rst);

    rst = memoized_lcs(X, Y, 7, 8);
    printf("rst - %d\n", rst);

    rst = bottom_up_lcs(X, Y, 7, 8);
    printf("rst - %d\n", rst);

    return 0;
}
