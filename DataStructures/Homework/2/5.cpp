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
    LinkList p = L, r;
    printf("\n Please input the elem(end with 0):\n");
    scanf("%d", &node);
    while (node != 0)
    {
        r = (LinkList)malloc(sizeof(LNode));
        if (!r)
        {
            return ERROR;
        }
        r->data = node;
        r->next = NULL;
        p->next = r;
        p = r;
        scanf("%d", &node);
    }
    return OK;
}

Status Insert_x(LinkList &L, ElemType x)
{
    LinkList p = L, r;
    r = (LinkList)malloc(sizeof(LNode));
    if (!r)
    {
        return ERROR;
    }
    r->data = x;
    if (L == NULL)
    {
        L = r;
        r->next = NULL;
        return OK;
    }
    while (p->next && x >= p->next->data)
    {
        p = p->next;
    }
    r->next = p->next;
    p->next = r;
    return OK;
}

void DisplayList(LinkList L)
{
    LinkList r = L->next;
    while (r)
    {
        printf("%4d", r->data);
        r = r->next;
    }
    printf("\n");
}

int main()
{
    LinkList L;
    CreateLinkList(L);
    Insert_x(L, 3);
    DisplayList(L);
    return 0;
}