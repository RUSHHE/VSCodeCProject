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

int Search_Seq(SSTable ST, KeyType key)
{
    int i;
    ST.elem[ST.length].key = key;
    for (i = 0; ST.elem[i].key != key; i++);
    return i;
}

void CreateSSTable(SSTable &ST, int n)
{
    ST.elem = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));
    ST.length = n;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ST.elem[i].key);
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

int main()
{
    SSTable ST;
    int n;
    scanf("%d", &n);
    CreateSSTable(ST, n);
    PrintSSTable(ST);
    int key;
    scanf("%d", &key);
    int i = Search_Seq(ST, key);
    printf("%d", i);
    return 0;
}