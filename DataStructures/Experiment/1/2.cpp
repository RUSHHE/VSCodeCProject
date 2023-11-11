#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -2
typedef int ElemType;
typedef int Status;
typedef struct
{
    ElemType * elem;
    int length;
    int listsize;
} SqList;

Status SqList_Create(SqList &L, int n)
{
    L.elem = (ElemType *)malloc((n + 1) * sizeof(ElemType));
    if (!L.elem)
    {
        return ERROR;
    }
    for (int i = 1; i <= n; i++)
    {
        L.elem[i] = 1;
    }
    L.length = n;
    L.listsize = n + 1;
    return OK;
}

Status Card_Games(SqList &L)
{
    for (int i = 2; i < L.length; i++)
    {
        for (int j = i; j < L.length; j++)
        {
            if (j % i == 0)
            {
                if (L.elem[j] == 1)
                {
                    L.elem[j] = 0;
                }
                else
                {
                    L.elem[j] = 1;
                }
            }
        }
    }
    return OK;
}

void showFrontCard(SqList L)
{
    printf("正面向上的纸牌分别是：\n");
    int numbers = 0;
    for (int i = 1; i < L.length; i++)
    {
        if (L.elem[i] == 1)
        {
            printf("%d\t", i);
            numbers++;
        }
    }
    printf("\n");
    printf("正面向上的纸牌总数数%d", numbers);
}

int main()
{
    SqList L;
    printf("请输入纸牌的张数：");
    int n;
    scanf("%d", &n);
    SqList_Create(L, n);
    Card_Games(L);
    showFrontCard(L);
    return 0;
}