#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define MAXSIZE 80

typedef int KeyType;
typedef int InfoType;
typedef struct
{
    KeyType key;
    // InfoType info; // 我也不知道有什么用
} RecdType;

//芝士顺序表
typedef struct
{
    RecdType r[MAXSIZE];
    int length;
} SqList;

typedef struct
{
    int compareTimes;
    int moveTimes;
} PfComparism;

SqList Origin;
SqList A;

PfComparism insert = {0, 0};
PfComparism bubble = {0, 0};
PfComparism select = {0, 0};
PfComparism shell = {0, 0};
PfComparism quick = {0, 0};
PfComparism merge = {0, 0};

void insertSort(SqList &L)
{
    for (int i = 0; i < L.length; i++)
    {
        insert.compareTimes++;
        if (L.r[i].key < L.r[i - 1].key)
        {
            int temp = L.r[i].key;
            insert.moveTimes++;
            int j;
            for (j = i - 1; j >= 0; j--)
            {
                insert.compareTimes++;
                if (L.r[j].key > temp)
                {
                    L.r[j + 1] = L.r[j];
                    insert.moveTimes++;   
                }
            }
            L.r[j + 1].key = temp;
            insert.moveTimes++;
        }
    }
}

void bubbleSort(SqList &L)
{
    for (int i = 0; i < L.length - 1; i++)
    {
        bool flag = FALSE;
        for (int j = L.length - 1; j > i; j--)
        {
            bubble.compareTimes++;
            if (L.r[j - 1].key > L.r[j].key)
            {
                int temp = L.r[j - 1].key;
                bubble.moveTimes++;
                L.r[j - 1].key = L.r[j].key;
                bubble.moveTimes++;
                L.r[j].key = temp;
                bubble.moveTimes++;
                flag = TRUE;
            }
        }
        if (flag == FALSE)
        {
            return;
        }
    }
}

void selectSort(SqList &L)
{
    for (int i = 0; i < L.length - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < L.length; j++)
        {
            select.compareTimes++;
            if (L.r[j].key < L.r[minIndex].key)
            {
                minIndex = j;
            }
        }
        if (minIndex != i) // 没有更小的就不用交换了
        {
            int temp = L.r[i].key;
            select.moveTimes++;
            L.r[i].key = L.r[minIndex].key;
            select.moveTimes++;
            L.r[minIndex].key = temp;
            select.moveTimes++;
        }
    }
}

void shellSort(SqList &L)
{
    for (int gap = L.length / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < L.length; i++)
        {
            int temp = L.r[i].key;
            shell.moveTimes++;
            for (int j = i; j >= gap; j -= gap)
            {
                shell.compareTimes++;
                if (L.r[j - gap].key > temp)
                {
                    int tmp = L.r[j].key;
                    L.r[j].key = L.r[j - gap].key;
                    L.r[j - gap].key = tmp;
                    shell.moveTimes += 3;
                }
            }
        }
    }
}

//快排的分区（划分）操作
int Partition(SqList &L, int low, int high)
{
    KeyType pivot = L.r[low].key;
    quick.moveTimes++;
    while (low < high)
    {
        quick.compareTimes++;
        while (low < high && L.r[high].key >= pivot)
        {
            --high;
        }
        L.r[low].key = L.r[high].key;
        quick.moveTimes++;
        quick.compareTimes++;
        while (low < high && L.r[low].key <= pivot)
        {
            ++low;
        }
    }
    L.r[low].key = pivot;
    quick.moveTimes++;
    return low;
}

void quickSort(SqList &L, int low, int high)
{
    if (low < high)
    {
        int pivotpos = Partition(L, low, high);
        quickSort(L, low, pivotpos - 1);
        quickSort(L, pivotpos + 1, high);
    }
}

void Merge(SqList &L, int low, int mid, int high)
{
    int i, j, k;
    //复制辅助数组
    for (k = 0; k < L.length; k++)
    {
        A.r[k].key = L.r[k].key;
        merge.moveTimes++;
    }
    A.length = L.length;
    for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++)
    {
        merge.compareTimes++;
        if (A.r[i].key <= A.r[j].key)
        {
            L.r[k].key = A.r[i++].key;
            i++;
            merge.moveTimes++;
        }
        else
        {
            L.r[k].key = A.r[j++].key;
            merge.moveTimes++;
        }
    }
    while (i <= mid)
    {
        L.r[k++].key = A.r[i++].key;
        merge.moveTimes++;
    }
    while (j <= high)
    {
        L.r[k++].key = A.r[j++].key;
        merge.moveTimes++;
    }
}

void mergeSort(SqList &L, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(L, low, mid);
        mergeSort(L, mid + 1, high);
        Merge(L, low, mid, high);
    }
}

void showSqList(SqList L)
{
    for (int i = 0; i < L.length; i++)
    {
        printf("%d ", L.r[i].key);
    }
    printf("\n");
}

void copySqList(SqList A, SqList &B)
{
    for (int i = 0; i < A.length; i++)
    {
        B.r[i].key = A.r[i].key;
    }
    B.length = A.length;
}

int main()
{
    SqList L;
    printf("请输入元素个数:");
    scanf("%d", &Origin.length);
    printf("请输入元素:(以空格分隔)\n");
    for (int i = 0; i < Origin.length; i++)
    {
        scanf("%d", &Origin.r[i].key);
    }
    while (true)
    {
        printf("===============\n");
        printf("1.直接插入排序\n");
        printf("2.冒泡排序\n");
        printf("3.简单选择排序\n");
        printf("4.希尔排序\n");
        printf("5.快速排序\n");
        printf("6.归并排序\n");
        printf("7.重置线性表\n");
        printf("0.退出\n");
        printf("===============\n");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            copySqList(Origin, L);
            printf("排序前:");
            showSqList(L);
            insertSort(L);
            printf("排序后:");
            showSqList(L);
            printf("比较次数:%d\n移动次数:%d\n", insert.compareTimes, insert.moveTimes);
            break;
        case 2:
            copySqList(Origin, L);
            printf("排序前:");
            showSqList(L);
            bubbleSort(L);
            printf("排序后:");
            showSqList(L);
            printf("比较次数:%d\n移动次数:%d\n", bubble.compareTimes, bubble.moveTimes);
            break;
        case 3:
            copySqList(Origin, L);
            printf("排序前:");
            showSqList(L);
            selectSort(L);
            printf("排序后:");
            showSqList(L);
            printf("比较次数:%d\n移动次数:%d\n", select.compareTimes, select.moveTimes);
            break;
        case 4:
            copySqList(Origin, L);
            printf("排序前:");
            showSqList(L);
            shellSort(L);
            printf("排序后:");
            showSqList(L);
            printf("比较次数:%d\n移动次数:%d\n", shell.compareTimes, shell.moveTimes);
            break;
        case 5:
            copySqList(Origin, L);
            printf("排序前:");
            showSqList(L);
            quickSort(L, 0, L.length - 1);
            printf("排序后:");
            showSqList(L);
            printf("比较次数:%d\n移动次数:%d\n", quick.compareTimes, quick.moveTimes);
            break;
        case 6:
            copySqList(Origin, L);
            printf("排序前:");
            showSqList(L);
            mergeSort(L, 0, L.length - 1);
            printf("排序后:");
            showSqList(L);
            printf("比较次数:%d\n移动次数:%d\n", merge.compareTimes, merge.moveTimes);
            break;
        case 7:
            printf("请输入元素个数:");
            scanf("%d", &Origin.length);
            printf("请输入元素:(以空格分隔)\n");
            for (int i = 0; i < Origin.length; i++)
            {
                scanf("%d", &Origin.r[i].key);
            }
            break;
        case 0:
            return 0;
            break;
        }
    }
    return 0;
}