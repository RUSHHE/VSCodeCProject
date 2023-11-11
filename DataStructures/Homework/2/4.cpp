#include <stdio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define ERROR 0
#define OK 1
#define OVERFLOW -2
typedef int ElemType;
typedef int Status;

typedef struct LNode
{
    ElemType data;//数据域
    struct LNode *next;//指针域
} LNode, *LinkList;

Status InitList(LinkList &L)
{
    L = (LinkList)malloc(sizeof(LNode));
    if (!L)
    {
        return ERROR;
    }
    L->next = NULL;
    return OK;
}

Status CreateLinkList(LinkList &L)
{
    ElemType node;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    LinkList r = L, p;
    printf("\n Please input the elem(end with 0):\n");
    scanf("%d", &node);
    while (node != 0)
    {
        p = (LinkList)malloc(sizeof(LNode));
        if (!p)
        {
            return ERROR;
        }
        p->data = node;
        p->next = NULL;
        r->next = p;
        r = p;
        scanf("%d", &node);
    }
    return OK;
}

int Length(LinkList L)
{
    int j = 0;
    LinkList p = L->next;
    while (p)
    {
        p = p->next;
        j++;
    }
    return j;
}

int main()
{
    LinkList L;
    CreateLinkList(L);
    printf("%d", Length(L));
    return 0;
}