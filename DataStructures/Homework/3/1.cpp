#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -2
typedef int ElemType;
typedef int Status;
typedef int SElemType;

typedef struct LNode
{
    ElemType data;//数据域
    struct LNode * next;//指针域
} LNode, *LinkList;

typedef struct SNode
{
    SElemType data;
    struct SNode * next;
}SNode, * LinkStack;

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

void DisplayList(LinkList L)
{
    LinkList p = L->next;
    while (p)
    {
        printf("%4d", p->data);
        p = p->next;
    }
    printf("\n");
}

Status InitStack(LinkStack &L)
{
    L = (LinkStack)malloc(sizeof(SNode));
    if (!L)
    {
        return ERROR;
    }
    L->next = NULL;
    return OK;
}

Status Push(LinkStack &S, SElemType e)
{
    LinkStack p = (LinkStack)malloc(sizeof(SNode));
    if (!p)
    {
        return ERROR;
    }
    p->data = e;
    p->next = S;
    S = p;
    return OK;
}

Status Pop(LinkStack &S, SElemType &e)
{
    if (S == NULL)
    {
        printf("The Stack is NULL!\n");
        return ERROR;
    }
    LinkStack p = S;
    e = p->data;
    S = p->next;
    free(p);
    return OK;
}

Status Reverse(LinkList &L)
{
    LinkList p = L->next;
    LinkStack S;
    InitStack(S);
    while (p)
    {
        Push(S, p->data);
        p = p->next;
    }
    p = L->next;
    SElemType e;
    while (p)
    {
        Pop(S, e);
        p->data = e;
        p = p->next;
    }
    free(p);
    free(S);
    return OK;
}

int main()
{
    LinkList L;
    CreateLinkList(L);
    Reverse(L);
    DisplayList(L);
    return 0;
}