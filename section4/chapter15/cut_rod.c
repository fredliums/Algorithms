#include <stdio.h>
#include <stdlib.h>

void print(int *p, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", p[i]);
    printf("\n");
}

static int max(int a, int b)
{
    return a > b ? a : b;
}

int cut_rod(int *p, int n)
{
    int q = -1;

    if (n == 0)
        return 0;

    for (int i = 1; i <= n; i++)
    {
        q = max(q, p[i - 1] + cut_rod(p, n - i));    
    }
    
    return q;
}

int cut_rod_aux(int *p, int n, int *r)
{
    int q = -1;

    if (r[n] >= 0)
        return r[n];

    if (n == 0)
        return 0;

    for (int i = 1; i <= n; i++)
    {
        q = max(q, p[i - 1] + cut_rod_aux(p, n - i, r));
    }

    r[n] = q;

    print(r, 11);

    return q;
}

int cut_rod_b(int *p, int size, int n)
{
    int *r;

    r = (int*)malloc(size * sizeof(int));

    for(int i = 0; i < size; i++)
        r[i] = -1;

    return cut_rod_aux(p, n, r);
}

int cut_rod_best(int *p, int size, int n)
{
    int *r, *s;
    int i, j, tmp, max;

    r = (int*)malloc((size + 1) * sizeof(int));
    s = (int*)malloc((size + 1) * sizeof(int));

    r[0] = 0;

    for (i = 1; i <= n; i++)
    {
        max = -1;
        for (j = 0; j < i; j++)
        {
            tmp = p[j] + r[i - j - 1];
            max = tmp > max ? tmp : max;
            s[i] = j;
        }
        r[i] = max;

        print(r, size + 1);
    }

    print(s, size + 1);
    
    return r[n];
}

int main()
{
    int p[] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

    int rst;

    rst = cut_rod(p, 10);
    printf("maximum for %d is %d\n", 10, rst);

    rst = cut_rod_b(p, 11, 10);
    printf("maximum for %d is %d\n", 10, rst);

    rst = cut_rod_best(p, 10, 7);
    printf("maximum for %d is %d\n", 7, rst);

    return 0;
}
