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

void Split(LinkList L, LinkList &LA, LinkList &LB)
{
    LinkList p = L, r1 = LA, r2 = LB;
    int i = 0;
    p = p->next;
    while (p)
    {
        if (i % 2 == 0)
        {
            r1->next = p;
            r1 = p;
        }
        else
        {
            r2->next = p;
            r2 = p;
        }
        p = p->next;
        i++;
    }
    r1->next = NULL;
    r2->next = NULL;
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

int main()
{
    LinkList L, LA, LB;
    CreateLinkList(L);
    InitList(LA);
    InitList(LB);
    Split(L, LA, LB);
    DisplayList(LA);
    DisplayList(LB);
    return 0;
}