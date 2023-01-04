#include "base.h"

int main()
{
    int A[10] = {2, 5, 6, 2, 1, 7, 9, 0, 6, 7};

    merge_sort(A, 10);
    print(A, 10);

    return 0;
}


