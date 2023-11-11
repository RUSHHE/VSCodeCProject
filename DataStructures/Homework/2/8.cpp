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

void Merge(LinkList &LA, LinkList &LB)
{
    LinkList p = LA, r1 = LA->next, r2 = LB->next; // p指针指向LA的头结点
    while (r1 && r2)
    {
        if (r1->data <= r2->data)
        {
            p->next = r1;
            p = r1;
            r1 = r1->next;
        }
        else
        {
            p->next = r2;
            p = r2;
            r2 = r2->next;
        }
    }
    if (r1 != NULL)
    {
        p->next = r1;
    }
    else
    {
        p->next = r2;
    }
    free(LB);
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
    LinkList LA, LB;
    CreateLinkList(LA);
    CreateLinkList(LB);
    Merge(LA, LB);
    DisplayList(LA);
    return 0;
}