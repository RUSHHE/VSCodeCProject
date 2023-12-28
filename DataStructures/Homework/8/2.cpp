#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef int KeyType;
typedef struct
{
    KeyType key;
} ElemType; // 记录类型

typedef struct
{
    ElemType *elem; // 0号存储单元闲置
    int length;
} SSTable; // 顺序表类型

// int Search_Seq(SSTable ST, KeyType key)
// {
//     int i;
//     ST.elem[ST.length].key = key;
//     for (i = 0; ST.elem[i].key != key; i++);
//     return i;
// }

// void CreateSSTable(SSTable &ST, int n)
// {
//     ST.elem = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));
//     ST.length = n;
//     for (int i = 0; i < n; i++)
//     {
//         scanf("%d", &ST.elem[i].key);
//     }
// }

void CreateSSTable(SSTable &ST, int n)
{
    ST.elem = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));
    ST.length = n;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &ST.elem[i].key);
    }
}

// void PrintSSTable(SSTable ST)
// {
//     for (int i = 0; i < ST.length; i++)
//     {
//         printf("%d ", ST.elem[i].key);
//     }
//     printf("\n");
// }

void PrintSSTable(SSTable ST)
{
    for (int i = 1; i <= ST.length; i++)
    {
        printf("%d ", ST.elem[i].key);
    }
    printf("\n");
}

void Search_Bin(SSTable ST, KeyType key)
{
    int  low, hign, mid;
    low = 1;
    hign = ST.length;
    while (low <= hign)
    {
        mid = (low + hign) / 2;
        if (ST.elem[mid].key == key)
        {
            printf("%d", mid);
            return;
        }
        else if (ST.elem[mid].key < key)
        {
            low = mid + 1;
        }
        else
        {
            hign = mid - 1;
        }
    }
    printf("查找失败");
}

int main()
{
    SSTable ST;
    int n;
    scanf("%d", &n);
    CreateSSTable(ST, n);
    PrintSSTable(ST);
    int key;
    scanf("%d", &key);
    Search_Bin(ST, key);
    return 0;
}