#include <stdio.h>

void hanoi(int n, char A, char B, char C)
{
    static int count = 1;

    if (n == 1)
    {
        printf("[%d]Move %c to %c\n", count++, A, C);
        return;
    }
    hanoi(n - 1, A, C, B);
    printf("[%d]Move %c to %c\n", count++, A, C);
    hanoi(n - 1, B, A, C);
}


int main()
{
    int n;

    printf("Number of disks: ");
    scanf("%d", &n);
    hanoi(n, 'A', 'B', 'C');

    return 0;
}
