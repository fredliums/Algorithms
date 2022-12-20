#include <stdio.h>

int naive_matcher(char *T, char *P);
int matcher(char *T, int Tn, char *P, int Tp);

int main()
{
    int index;

    char s1[128];
    char s2[128];

    printf("Input string: ");
    scanf("%s", s1);
    printf("Input string: ");
    scanf("%s", s2);

    index = naive_matcher(s1, s2);
    printf("Matched index: %d\n", index);

    return 0;
}

int naive_matcher(char *T, char *P)
{
    int i = 0;
    char *p, *q;

    if (!T || !P)
        return -1;

    while(T[i] != '\0')
    {
        for (p = &T[i], q = P; *p != '\0' && *q != '\0'; p++, q++)
        {
            if (*p != *q)
                break;
        }

        if (*q == '\0')
            return i;

        i++;
    }

    return -1;
}

int matcher(char *T, int Tn, char *P, int Tp)
{
    char *p, *q;

    if (!T || !P)
        return -1;

    if (Tp > Tn)
        return -2;

    for (int i = 0; i < Tn - Tp; i++)
    {
        for (p = &T[i], q = P; *p != '\0' && *q != '\0'; p++, q++)
        {
            if (*p != *q)
                break;
        }

        if (*q == '\0')
            return i;
    }

    return -1;
}
