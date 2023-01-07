#include "base.h"

int main()
{
    int A[10] = {2, 5, 6, 2, 1, 7, 9, 0, 6, 7};

    shell_sort_b(A, 10);
    print(A, 10);

    /*
    int B[11] = {0, 2, 5, 6, 2, 1, 7, 9, 0, 6, 7};
    heap_sort(B, 10);
    print(B, 11);
    */

    return 0;
}


