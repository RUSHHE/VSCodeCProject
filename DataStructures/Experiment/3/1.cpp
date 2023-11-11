#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -2
#define STACK_INIT_SIZE 80
#define STACKINCREMENT 10
typedef char ElemType;
typedef int Status;
typedef char SElemType;

typedef struct LNode
{
    ElemType data;//数据域
    struct LNode * next;//指针域
} LNode, *LinkList;

typedef struct
{
    SElemType * base;
    SElemType * top;
    int stacksize;
} SqStack;

Status CreateLinkList(LinkList &L, int n)
{
    ElemType node;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    LinkList r = L, p;
    getchar();//吸收\n
    printf("请输入单词(不含空格):");
    int i = 0;
    while (i != n)
    {
        p = (LinkList)malloc(sizeof(LNode));//每次创建一个节点p放置数据
        if (!p)
        {
            return ERROR;
        }
        scanf("%c", &node);
        p->data = node;//给新节点以数据
        p->next = NULL;//后置节点为空
        r->next = p;//使节点p接在r的后面
        r = p;//r指针后移到p位置
        i++;//计数器
    }
    return OK;
}

Status InitStack(SqStack &S)
{
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S.base)
    {
        printf("OVERFLOW");
        return ERROR;
    }
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status Push(SqStack &S, SElemType e)
{
    if (S.top - S.base >= S.stacksize)
    {
        S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!S.base)
        {
            printf("OVERFLOW");
            return ERROR;
        }
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}

Status Pop(SqStack &S, SElemType &e)
{
    if (S.base == S.top)
    {
        printf("The Stack is NULL!\n");
        return ERROR;
    }
    e = * --S.top;
    return OK;
}

Status JudgePalindrome(LinkList L)
{
    LinkList p = L->next;
    SqStack S;
    InitStack(S);
    //先入栈
    while (p)
    {
        Push(S, p->data);
        p = p->next;
    }
    p = L->next;//重置p的位置
    SElemType e;
    //遍历链表与出栈的数比较
    while (p)
    {
        Pop(S, e);
        if (e != p->data)
        {
            return ERROR;
        }
        p = p->next;
    }
    free(p);
    return OK;
}

void DisplayList(LinkList L)
{
    LinkList p = L->next;
    //遍历输出
    while (p)
    {
        printf("%c", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    LinkList L;
    int n;
    printf("请输入单词的长度n:");
    scanf("%d", &n);
    CreateLinkList(L, n);
    DisplayList(L);
    if (JudgePalindrome(L))
    {
        printf("此链表中的字符序列构成回文");
    }
    else
    {
        printf("此链表中的字符序列不构成回文");
    }
    return 0;
}