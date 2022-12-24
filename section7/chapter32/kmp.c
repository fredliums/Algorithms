#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_NUMS 128

int KMP_MATCHER(char *T, int n, char *P, int m);
int* COMPUTE_PREFIX_FUNCTION(char *P, int m);

int main()
{
    int index;
    int ls1, ls2;

    char s1[CHAR_NUMS];
    char s2[CHAR_NUMS];

    printf("Input string: ");
    scanf("%s", s1);
    printf("Input string: ");
    scanf("%s", s2);

    ls1 = strlen(s1);
    ls2 = strlen(s2);

    int *p = COMPUTE_PREFIX_FUNCTION(s2, ls2);
    index = KMP_MATCHER(s1, ls1, s2, ls2);
    printf("Last matched index: %d\n", index);

    return 0;
}

/*
 * Compare T with P:
 *  from left to right
 *  re-match from q = PI[q]
 */
int KMP_MATCHER(char *T, int n, char *P, int m)
{
    int i, *PI;
    int last = -1;
    int q = 0;

    PI = COMPUTE_PREFIX_FUNCTION(P, m);

    for (i = 0; i < n; i++)
    {
        // PI[0] must be 0, means re-match from P[0]
        while(q > 0 && T[i] != P[q])
            q = PI[q];

        if (T[i] == P[q])
            q = q + 1;

        if (q == m)
        {
            printf("Matched and index start with %d\n", i - m + 1);
            last = i - m + 1;
            // Matched and re-match, q must 0 here
            q = PI[q];
        }

    }

    return last;
}

/*
 * Compare P with P itself:
 *  from left to right
 *  and keep the max prefix from right: k = PI[k]
 */
int* COMPUTE_PREFIX_FUNCTION(char *P, int m)
{
    int q, *PI;
    int k = 0;

    PI = (int*)malloc(m * sizeof(int));
    PI[0] = 0;

    for(q = 1; q < m; q++)
    {
        while(k > 0 && P[k] != P[q])
            k = PI[k];

        if (P[k] == P[q])
            k = k + 1;

        PI[q] = k;
    }

    return PI;
}
