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
    ElemType * elem;
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

Status SqList_Insert(SqList &L, int i, ElemType e)
{
    if (i < 1 || i > L.length + 1)
    {
        return ERROR;
    }
    if (L.length >= L.listsize)
    {
        return OVERFLOW;
    }
    for (int j = L.length - 1; j >= i - 1; j--)
    {
        L.elem[j - 1] = L.elem[j];
    }
    L.elem[i - 1] = e;
    L.length++;
    return OK;
}

Status SqList_Delete(SqList &L, int i, ElemType &e)
{
    if (i < 1 || i > L.length)
    {
        return ERROR;
    }
    e = L.elem[i - 1];
    for (int j = i; j < L.length - 1; j++)
    {
        L.elem[j - 1] = L.elem[j];
    }
    L.length--;
    return OK;
}

int SqList_Search(SqList L, ElemType e)
{
    int i;
    for (i = 1; i < L.length && L.elem[i - 1] != e; i++)
    {

    }
    if (i <= L.length)
    {
        return i;
    }
    else
    {
        return 0;
    }
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
    SqList L; // 前四道题的顺序表
    int i, n;
    ElemType e;

    printf("请输入初始顺序表的长度：\n");
    scanf("%d", &n);
    
    printf("请依次输入表内的数据：\n");
    SqList_Create(L, n);
    
    printf("这是你创建的顺序表：\n");
    SqList_Output(L);

    printf("要在第几位插入数据？\n");
    scanf("%d", &i);

    printf("请输入你要插入的数据:\n");
    scanf("%d", &e);

    if (SqList_Insert(L, i, e) == 1)
    {
        SqList_Output(L);
    }
    else
    {
        printf("插入失败！\n");
    }

    printf("请输入要删除第几位元素\n");
    scanf("%d", &i);
    if (SqList_Delete(L, i, e) == 1)
    {
        SqList_Output(L);
        printf("%d\n", e);
    }
    else
    {
        printf("删除失败！\n");
    }

    printf("请输入要查找的数据\n");
    scanf("%d", &e);
    if (SqList_Search(L, e))
    {
        printf("查找成功，在第%d位置\n", SqList_Search(L, e));
    }
    else
    {
        printf("查找失败！\n");
    }

    //第五题创建顺序表并删除重复元素
    SqList A;
    printf("请输入长度m\n");
    int m;
    scanf("%d" ,&m);
    SqList_Create(A, m);
    int c = 0; // 原始数
    int d = 1; // 要排查的数
    while (d < A.length)
    {
        if (A.elem[c] == A.elem[d])
        {
            d++;
        }
        else
        {
            c++;
            A.elem[c] = A.elem[d];
            d++;
        }
    }
    A.length = c + 1;
    //输出删除重复元素的顺序表
    printf("这是你的顺序表");
    SqList_Output(A);

    return 0;
}