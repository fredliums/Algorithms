#include <stdio.h>
#include <stdlib.h>

static int len(char *s);
static int check_suffix(char *P, int k, int q, char a);
int COMPUTE_TRANSITION_FUNCTION(char *P, int m);
int FINITE_AUTOMATION_MATCHER(char *T, int n, int m);

#define CHAR_NUMS 128

int (*delta)[CHAR_NUMS];

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

    ls1 = len(s1);
    ls2 = len(s2);

    COMPUTE_TRANSITION_FUNCTION(s2, ls2);
    index = FINITE_AUTOMATION_MATCHER(s1, ls1, ls2);
    printf("Last matched index: %d\n", index);

    return 0;
}

// Check if P[k] is subset of P[q]a
static int check_suffix(char *P, int k, int q, char a)
{
    int i, j;

    // Empty set is subset of any set
    if (k == 0)
        return 1;

    if (P[k - 1] != a)
        return 0;

    for (i = k - 2, j = q - 1; i >= 0; i--, j--)
    {
        if (P[i] != P[j])
            return 0;
    }

    return 1;
}

int FINITE_AUTOMATION_MATCHER(char *T, int n, int m)
{
    int i, q = 0, last = -1;

    for (i = 0; i < n; i++)
    {
        q = delta[q][T[i]];
        if (q == m)
        {
            printf("Matched and index start with %d\n", i - m + 1);
            last = i - m + 1;
        }
    }

    return last;
}

/*
 * i = 0 .. m
 * j = char set 0 .. 127
 */
int COMPUTE_TRANSITION_FUNCTION(char *P, int m)
{
    int i, j, k;

    if (!P || m <= 0)
        return -1;

    delta = (int(*)[128])calloc(m * CHAR_NUMS, sizeof(int));

    for (i = 0; i < m; i++)
    {
        if (m < CHAR_NUMS)
        {
            // Calculate T(i, P[a]), 0 < a < m
            for (j = 0; j < m; j++)
            {
                k = i + 1;
                while (!check_suffix(P, k, i, P[j]))
                {
                    k--;
                }
                delta[i][P[j]] = k;
            }
        }
        else
        {
            // Calculate T(i, a), 0 < a < CHAR_NUMS
            for (j = ' '; j < CHAR_NUMS; j++)
            {
                k = i + 1;
                while (!check_suffix(P, k, i, j))
                {
                    k--;
                }
                delta[i][j] = k;
            }
        }
    }

    return 0;
}

static int len(char *s)
{
    int count = 0;
    char *p = s;

    while(*p++ != '\0')
        count++;

    return count;
}
