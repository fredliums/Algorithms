#include <stdio.h>

void print(int *A, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int cross_subarray(int *A, int low, int mid, int high)
{
    int i, j;
    int sum, left_sum, right_sum;
    int max_left, max_right;

    if (A == NULL)
        return -1;

    if (low > mid || mid >= high)
        return -1;

    left_sum = 0;
    sum = 0;
    for (i = mid; i >= low; i--)
    {
        sum += A[i];
        if (sum > left_sum)
        {
            left_sum = sum;
            max_left = i;
        }
    }

    right_sum = 0;
    sum = 0;
    for (j = mid + 1; j <= high; j++)
    {
        sum += A[j];
        if (sum > right_sum)
        {
            right_sum = sum;
            max_right = j;
        }
    }

    /*
    printf("Max-left [%d]%d max-right [%d]%d max = %d\n", max_left,
            left_sum, max_right, right_sum, left_sum + right_sum);
    */

    return left_sum + right_sum;
}

int max_subarray(int *A, int low, int high)
{
    int sum;

    if (A == NULL)
        return -1;

    if (low == high)
        sum = A[low];
    
    if (low < high)
    {
        int mid = (low + high) / 2;
        int sum1 = max_subarray(A, low, mid);
        int sum2 = max_subarray(A, mid + 1, high);
        int sum3 = cross_subarray(A, low, mid, high);
        sum = (sum1 > sum2 && sum1 > sum3) ? sum1 :
            (sum2 > sum3 ? sum2 : sum3); 
    }

    return sum;
}

int main()
{
    int sum;
    /*
    int A[] = {8, -2, 3, -3, 5, 7, -3, 2};
    print(A, 8);
    sum = cross_subarray(A, 0, 3, 7);
    */
    int A[] = {3, -2, 3, -3, 5, 7, -3, 2};
    print(A, 8);
    sum = max_subarray(A, 0, 7);
    printf("sum - %d\n", sum);

    return 0;
}
