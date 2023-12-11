#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -2
#define MAXQSIZE 100
typedef int Status;
typedef int QElemType;
typedef int LinkQElemType;

typedef struct
{
    QElemType *base;
    int front;
    int rear;
    int flag; // 在此题中不会溢出
} SqQueue;

typedef struct QNode
{
    LinkQElemType data; // 数据域
    struct QNode *next; // 指针域
} QNode, *QueuePtr;

// 循环链队列的结构
typedef struct
{
    QueuePtr rear; // 队尾指针
} LinkQueue;

Status InitSqQueue(SqQueue &Q)
{
    Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
    if (!Q.base)
    {
        exit(OVERFLOW);
    }
    Q.front = Q.rear = 0;
    return OK;
}

Status EnSqQueue(SqQueue &Q, QElemType e)
{
    if (Q.front == Q.rear && Q.flag == 1)
    {
        printf("The Queue is OVERFLOW!\n");
        return ERROR;
    }
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    Q.flag = 1;
    return OK;
}

Status DeSqQueue(SqQueue &Q, QElemType &e)
{
    if (Q.front == Q.rear && Q.flag == 0)
    {
        printf("The Queue is NULL!\n");
        return ERROR;
    }
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
    Q.flag = 0;
    return OK;
}

int SqQueueLength(SqQueue Q)
{
    if (Q.front == Q.rear && Q.flag == 1)
    {
        return MAXQSIZE;
    }
    else
    {
        return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
    }
}

void DisplaySqQueue(SqQueue Q)
{
    for (int i = Q.front; i != Q.rear; i = (i + 1) % MAXQSIZE)
    {
        printf("%d ", Q.base[i]);
    }
    printf("\n");
}

Status InitQueue(LinkQueue &Q)
{
    Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if (!Q.rear)
    {
        return OVERFLOW;
    }
    Q.rear->next = Q.rear; // 头结点的next指向自己
    return OK;
}

Status DisplayLinkQueue(LinkQueue Q)
{
    QueuePtr p;
    p = Q.rear->next->next; // 从头结点的下一个结点开始遍历
    while (p != Q.rear->next)
    { // 当没有回到头结点时
        printf("%d ", p->data);
        p = p->next; // 指针后移
    }
    printf("\n");
    return OK;
}

Status EnLinkQueue(LinkQueue &Q, LinkQElemType e)
{
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof(QNode));
    if (!p)
    {
        return ERROR;
    }
    p->data = e;
    p->next = Q.rear->next; // 新结点的next指向头结点
    Q.rear->next = p;       // 尾节点接上新结点
    Q.rear = p;             // 队尾指针指向新结点
    return OK;
}

Status DeLinkQueue(LinkQueue &Q, LinkQElemType &e)
{
    QueuePtr p;
    if (Q.rear == Q.rear->next)
    { // 如果队列为空
        return ERROR;
    }
    p = Q.rear->next->next;       // p指向头结点的下一个结点，即队首元素
    e = p->data;                  // 保存队首元素的值
    Q.rear->next->next = p->next; // 头结点的next指向队首元素的下一个结点
    free(p);
    return OK;
}

int QueueLength(LinkQueue Q)
{
    QueuePtr p = Q.rear->next->next;
    int length = 0;
    while (p != Q.rear)
    {
        length++;
        p = p->next;
    }
    return length;
}

int main()
{
    SqQueue Q;
    InitSqQueue(Q);
    printf("输入的队列队列长度n:");
    int n;
    scanf("%d", &n);
    printf("请输入各元素值");
    for (int i = 0; i < n; i++)
    {
        QElemType e;
        scanf("%d", &e);
        EnSqQueue(Q, e);
    }
    DisplaySqQueue(Q);
    printf("请输入入队值");
    QElemType e;
    scanf("%d", &e);
    EnSqQueue(Q, e);
    DisplaySqQueue(Q);
    QElemType temp1;
    DeSqQueue(Q, temp1);
    printf("%d出队\n", temp1);
    DisplaySqQueue(Q);

    LinkQueue Q1;
    InitQueue(Q1);
    printf("输入的队列队列长度n:");
    int n1;
    scanf("%d", &n1);
    printf("请输入各元素值");
    for (int i = 0; i < n1; i++)
    {
        LinkQElemType e;
        scanf("%d", &e);
        EnLinkQueue(Q1, e);
    }
    DisplayLinkQueue(Q1);
    printf("请输入入队值");
    LinkQElemType e1;
    scanf("%d", &e1);
    EnLinkQueue(Q1, e1);
    DisplayLinkQueue(Q1);
    LinkQElemType e2;
    DeLinkQueue(Q1, e2);
    printf("%d出队\n", e2);
    DisplayLinkQueue(Q1);
    return 0;
}