#include <stdio.h>
typedef int ElemType;

void BubbleSort(ElemType A[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        bool flag = false;
        for (int j = n - 1; j > i; j--)
        {
            if (A[j - 1] > A[j])
            {
                int temp = A[j - 1];
                A[j - 1] = A[j];
                A[j] = temp;
                flag = true;
            }
        }
        if (flag == false)
        {
            return;
        }
    }
}

int main()
{
    ElemType A[] = {1, 3, 2, 5, 4, 7, 6, 8, 9, 10};
    int n = sizeof(A) / sizeof(A[0]);
    BubbleSort(A, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
}