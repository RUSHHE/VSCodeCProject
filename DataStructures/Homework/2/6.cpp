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

void reverse(LinkList &L)
{
    LinkList p = L->next, r;
    L->next = NULL;
    while (p)
    {
        r = p;//r为上一轮的位置
        p = p->next;//p为下一轮的位置
        r->next = L->next;//L的下一位地址赋值给r的下一位
        L->next = r;//空节点L的下一位插入r
    }
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
    LinkList L;
    CreateLinkList(L);
    reverse(L);
    DisplayList(L);
    return 0;
}