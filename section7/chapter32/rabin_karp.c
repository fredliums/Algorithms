#include <stdio.h>

int rabin_karp_matcher(char *T, int Tn, char *P, int Pn, int d, int q);
static int str(char c);
static int len(char *s);

int main()
{
    int index;
    int lens1, lens2;

    char s1[128];
    char s2[128];

    printf("Input string: ");
    scanf("%s", s1);
    printf("Input string: ");
    scanf("%s", s2);

    lens1 = len(s1);
    lens2 = len(s2);
    index = rabin_karp_matcher(s1, lens1, s2, lens2, 128, 13);
    printf("Last matched index: %d\n", index);

    return 0;
}

int rabin_karp_matcher(char *T, int Tn, char *P, int Pn, int d, int q)
{
    int i;
    int h = 1, last = -1;
    int p = 0, t = 0;
    char *u, *v;

    if (!T || !P)
        return -1;

    if (Tn < Pn)
        return -2;

    // Calculate h
    for (i = 1; i < Pn; i++)
        h = (h * d) % q;

    // Calculate p and t0
    for (i = 0; i < Pn; i++)
    {
        /* Tips: p = X0X1X2X3 % Y equals to
         * p = 0
         * for i = 0 to 2:
         *   p = (10 * p + X[i]) % Y
         */
        p = (d * p + str(P[i])) % q;
        t = (d * t + str(T[i])) % q;
    }

    for (i = 0; i <= Tn - Pn; i++)
    {
        if (p == t)
        {
            // Check if T[i..i+Pn] = P
            for (u = &T[i], v = P; *u != '\0' && *v != '\0'; u++, v++)
            {
                if (*u != *v)
                    break;
            }
            
            if (*v == '\0')
            {
                printf("Matched and index start with %d\n", i);
                last = i;
            }
        }

        // Calculate t[i]
        if (i < Tn - Pn)
        {
            t = (d * (t - str(T[i]) * h) + str(T[i + Pn]) + q) % q;
            // t maybe minus, so plus q
            if (t < 0)
                t += q;
        }
    }

    return last;
}


static int str(char c)
{
    return (int)c;
}

static int len(char *s)
{
    int count = 0;
    char *p = s;

    while(*p++ != '\0')
        count++;

    return count;
}
