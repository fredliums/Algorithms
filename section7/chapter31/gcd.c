#include <stdio.h>
#include <stdlib.h>

typedef struct _Tuple
{
    int d;
    int x;
    int y;
} Tuple;

int gcd(int a, int b);
Tuple* extended_gcd(int a, int b);


int main()
{
    int a, b, c;
    Tuple *r;

    printf("Calculate greatest common divisor\n");
    printf("Input two numbers: ");
    scanf("%d %d", &a, &b);

    c = gcd(a, b);
    printf("GCD of %d and %d is %d\n", a, b, c);
    r = extended_gcd(a, b);
    printf("(%d, %d, %d) => GCD(%d, %d) = %d = %d * %d + %d * %d\n",
            r->d, r->x, r->y, a, b, r->d, r->x, a, r->y, b);

    return 0;
}


int gcd(int a, int b)
{
    if (b == 0)
        return a;

    return
        gcd(b, a % b);
}

Tuple* extended_gcd(int a, int b)
{
    Tuple *p, *q;

    q = (Tuple*)malloc(sizeof(Tuple)); 

    if (b == 0)
    {
        q->d = a;
        q->x = 1;
        q->y = 0;

        return q;
    }
    else
    {
        p = extended_gcd(b, a % b);
        q->d = p->d;
        q->x = p->y;
        q->y = p->x - (a / b) * p->y;
        free(p);

        return q;
    }
}
