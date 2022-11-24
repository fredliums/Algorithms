#include <stdio.h>
#include <string.h>

int act[10];

int recursive_activity_selector(int *s, int *f, int k, int n)
{
    int m;
    static int c = 0;

    m = k + 1;
    while(m <= n && s[m] < f[k])
        m++;

    if (m <= n)
    {
        act[c++] = m;
        return 1 + recursive_activity_selector(s, f, m, n);
    }
    else
        return 0;
}

int greedy_activity_selector(int *s, int *f, int n)
{
    int m, k = 0;
    int result = 0;
    static int count = 0;

    for(m = k + 1; m <= n; m++)
    {
        if(s[m] >= f[k])
        {
            act[count++] = m;
            result++;
            k = m;
        }
    }

    return result;
}

int las(int *s, int *f, int n)
{
    int m, k = n;
    int result = 1;
    static int count = 1;

    act[0] = 11;
    for (m = k - 1; m > 0; m--)
    {
        if (f[m] <= s[k])
        {
            act[count++] = m;
            result++;
            k = m;
        }
    }

    return result;
}

int main()
{
    int ret;

    int s[] = {0, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
    int f[] = {0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};

    ret = recursive_activity_selector(s, f, 0, 11);
    printf("ret-%d\n", ret);

    for (int i = 0; i < ret; i++)
        printf("%d ", act[i]);
    printf("\n");

    ret = greedy_activity_selector(s, f, 11);
    printf("ret-%d\n", ret);

    for (int i = 0; i < ret; i++)
        printf("%d ", act[i]);
    printf("\n");

    ret = las(s, f, 11);
    printf("ret-%d\n", ret);

    for (int i = 0; i < ret; i++)
        printf("%d ", act[i]);
    printf("\n");

    return 0;
}
