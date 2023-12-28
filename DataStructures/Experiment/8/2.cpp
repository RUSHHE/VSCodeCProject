#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef int Status;
typedef int KeyType;
typedef int InfoType;
typedef struct
{
    KeyType key;
    InfoType otherinfo;
} RecdType;
typedef struct
{
    RecdType *elem;
    int length;
} SSTable;

Status CreateSSTable(SSTable &ST, int n)
{
    ST.elem = (RecdType *)malloc(MAXSIZE * sizeof(RecdType));
    if (!ST.elem)
    {
        return OVERFLOW;
    }
    ST.length = n;
    for (int i = 0; i < ST.length; i++)
    {
        scanf("%d", &ST.elem[i].key);
    }
    return OK;
}

int SeqSearch(SSTable ST, KeyType key)
{
    for (int i = 0; i < ST.length; i++)
    {
        if (ST.elem[i].key == key)
        {
            return i;
        }
    }
    return -1;
}

int Bin_Search(SSTable ST, KeyType key)
{
    int low = 0, high = ST.length - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (ST.elem[mid].key == key)
        {
            return mid;
        }
        else if (ST.elem[mid].key < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

void BubbleSort(SSTable &ST)
{
    for (int i = 0; i < ST.length - 1; i++)
    {
        for (int j = ST.length - 1; j > i; j--)
        {
            if (ST.elem[j].key < ST.elem[j - 1].key)
            {
                KeyType temp = ST.elem[j].key;
                ST.elem[j].key = ST.elem[j - 1].key;
                ST.elem[j - 1].key = temp;
            }
        }
    }
}

void PrintSSTable(SSTable ST)
{
    for (int i = 0; i < ST.length; i++)
    {
        printf("%d ", ST.elem[i].key);
    }
    printf("\n");
}

void CopySSTable(SSTable &ST1, SSTable ST2)
{
    ST1.length = ST2.length;
    ST1.elem = (RecdType *)malloc(MAXSIZE * sizeof(RecdType));
    for (int i = 0; i < ST1.length; i++)
    {
        ST1.elem[i].key = ST2.elem[i].key;
    }
}

int CanFinish(SSTable ST, int t, int speed)
{
    int time = 0;
    for (int i = 0; i < ST.length; i++)
    {
        time = time + (ST.elem[i].key - 1) / speed + 1;
    }
    if (time <= t)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int MinEatingSpeed(SSTable ST, int t)
{
    if (CanFinish(ST, t, 10))
    {
        if (ST.length == 1)
        {
            return ceil(((double)ST.elem[0].key) / 2); // 修复一堆速度不对
        }
        int low = 1, high = 10;
        int mid = 0;
        while (low < high)
        {
            mid = (low + high) / 2;
            if (!CanFinish(ST, t, mid))
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return low;
    }
    return -1;
}

int main()
{
    SSTable ST;
    int n;
    printf("要给吗喽多少堆香蕉?");
    scanf("%d", &n);
    printf("输入各堆香蕉的数量");
    CreateSSTable(ST, n);
    int t;
    printf("管理员会在多久后回来?");
    scanf("%d", &t);
    int rtn = MinEatingSpeed(ST, t);
    if (rtn == -1)
    {
        printf("猴子吃不完");
    }
    else
    {
        printf("速度为%d", rtn);
    }
    return 0;
}