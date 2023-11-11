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

Status Insert(SqList &L, int n)
{
    int i;
    for (i = 0; i < L.listsize; i++)
    {
        if (n < L.elem[i])
        {
            break;
        }
    }
    if (L.length >= L.listsize)
    {
        return OVERFLOW;
    }
    L.length++;
    for (int j = L.length - 1; j >= i - 1; j--)
    {
        L.elem[j] = L.elem[j - 1];
    }
    L.elem[i] = n;
    return OK;
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
    Insert(L, 4);
    SqList_Output(L);
    return 0;
}