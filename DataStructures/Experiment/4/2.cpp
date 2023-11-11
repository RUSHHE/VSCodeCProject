#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0
typedef int ElemType;
typedef int Status;
typedef int SElemType;
typedef int QElemType;

typedef struct SNode
{
    SElemType data;
    struct SNode *next;
} SNode, *LinkStack;

typedef struct QNode
{
    QElemType data;     // 数据域
    struct QNode *next; // 指针域
} QNode, *QueuePtr;

// 循环链队列的结构
typedef struct
{
    QueuePtr front;
    QueuePtr rear; // 队尾指针
} LinkQueue;

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

int StackLength(LinkStack S)
{
    LinkStack p = S->next;
    int length = 0;
    while (p)
    {
        length++;
        p = p->next;
    }
    return length;
}

Status InitLinkQueue(LinkQueue &Q)
{
    Q.front = (QueuePtr)malloc(sizeof(QNode));
    if (!Q.front)
    {
        return OVERFLOW;
    }
    Q.rear = Q.front;
    return OK;
}

Status DisplayLinkQueue(LinkQueue Q)
{
    QueuePtr p;
    p = Q.front->next; // 从头结点的下一个结点开始遍历
    while (p != Q.rear)
    { // 当没有回到尾结点时
        printf("%d ", p->data);
        p = p->next; // 指针后移
    }
    printf("\n");
    return OK;
}

Status EnLinkQueue(LinkQueue &Q, QElemType e)
{
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof(QNode));
    if (!p)
    {
        return ERROR;
    }
    p->data = e;
    p->next = Q.front; // 新结点的next指向头结点
    Q.rear->next = p;  // 尾节点接上新结点
    Q.rear = p;        // 队尾指针指向新结点
    return OK;
}

Status DeLinkQueue(LinkQueue &Q, QElemType &e)
{
    QueuePtr p;
    if (Q.front == Q.rear)
    { // 如果队列为空
        return ERROR;
    }
    p = Q.front->next;       // p指向队首元素
    e = p->data;             // 保存队首元素的值
    Q.front->next = p->next; // 头结点的next指向队首元素的下一个结点
    free(p);
    return OK;
}

int LinkQueueLength(LinkQueue Q)
{
    QueuePtr p = Q.front;
    int length = 0;
    while (p->next != Q.front)
    {
        length++;
        p = p->next;
    }
    return length;
}

Status ReverseStack(LinkStack &S)
{
    SElemType k;
    int n = StackLength(S);
    if (n == 0)
    {
        return OK;
    }
    SElemType stack[n];
    for (int i = 0; i < n; i++)
    {
        Pop(S, stack[i]);
    }
    for (int i = 0; i < n; i++)
    {
        Push(S, stack[i]);
    }
    return OK;
}

Status GetTop(LinkStack S, SElemType &e)
{
    if (!S->next) // 如果栈空
    {
        printf("The Stack is NULL\n");
        return ERROR;
    }
    e = S->data; // 取栈顶元素的值并用e返回
    return OK;
}

int LoopJudge(LinkQueue Q, LinkStack S)
{
    int n, i;
    int count = 0;
    SElemType k;
    n = LinkQueueLength(Q);
    QueuePtr stu = Q.front->next;
    for (i = 0; i < n; i++)
    {
        GetTop(S, k);
        if (stu->data != k)
        {
            count++;
            stu = stu->next;
        }
    }
    if (count == n)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int CountStu(LinkQueue Q, LinkStack S)
{
    QElemType e;
    SElemType m, k;

    QueuePtr stu = Q.front->next;
    while (!LoopJudge(Q, S))
    {
        GetTop(S, k);
        DeLinkQueue(Q, e);
        if (e == k)
        {
            Pop(S, m);
        }
        else
        {
            EnLinkQueue(Q, e);
        }
    }
    if (LinkQueueLength(Q) == 0)
    {
        return 0;
    }
    else
    {
        return LinkQueueLength(Q);
    }        
}

int main()
{
    int n;
    scanf("%d", &n);
    printf("初始化学生队列\n");
    LinkQueue Q;
    InitLinkQueue(Q);
    for (int i = 0; i < n; i++)
    {
        QElemType e;
        scanf("%d", &e);
        EnLinkQueue(Q, e);
    }

    printf("初始化面包栈\n");
    LinkStack S;
    InitStack(S);
    for (int i = 0; i < n; i++)
    {
        SElemType e;
        scanf("%d", &e);
        Push(S, e);
    }
    ReverseStack(S);
    int m = CountStu(Q, S);
    if (m == 0)
    {
        printf("所有同学都吃到午餐\n");
    }
    else
    {
        printf("还有%d位同学没吃到午餐\n", m);
    }
    return 0;
}