#include <stdio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define ERROR 0
#define OK 1
#define OVERFLOW -2
typedef int ElemType;
typedef int Status;

typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
} SqList;

Status SqList_Create(SqList &L, int n)
{
    L.elem = (ElemType * )malloc(LIST_INIT_SIZE * sizeof (ElemType));
    if (!L.elem)
    {
        return OVERFLOW;
    }
    L.listsize = LIST_INIT_SIZE;
    L.length = n;
    for (int i = 0; i < L.length; i++)
    {
        scanf("%d", &L.elem[i]);
    }
    return OK;
}

void DeleteSame(SqList &L)
{
    for (int i = 0; i < L.length - 1; i++)
    {
        for (int j = 0; j < L.length - 1 - i; j++)
        {
            if (L.elem[j] > L.elem[j + 1])
            {
                ElemType temp = L.elem[j];
                L.elem[j] = L.elem[j + 1];
                L.elem[j + 1] = temp;
            }   
        }
    }
    
    int i = 0; // 原始数
    int j = 1; // 要排查的数
    while (j < L.length)
    {
        if (L.elem[i] == L.elem[j])
        {
            j++;
        }
        else
        {
            i++;
            L.elem[i] = L.elem[j];
            j++;
        }
    }
    L.length = i + 1;
}

void SqList_Output(SqList L)
{
    for (int i = 0; i < L.length; i++)
    {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}

int main()
{
    SqList L;
    int n;
    scanf("%d", &n);
    SqList_Create(L, n);
    SqList_Output(L);
    DeleteSame(L);
    SqList_Output(L);
    return 0;
}