#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -2
#define MAXQSIZE 6
typedef int Status;
typedef int QElemType;

typedef struct
{
    QElemType *base;
    int front;
    int rear;
    int flag;
} SqQueue;

Status InitQueue(SqQueue &Q)
{
    Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
    if (!Q.base)
    {
        exit(OVERFLOW);
    }
    Q.front = Q.rear = 0;
    return OK;
}

Status EnQueue(SqQueue &Q, QElemType e)
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

Status DeQueue(SqQueue &Q, QElemType &e)
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

int main()
{
    SqQueue Q;
    InitQueue(Q);
    for (int i = 2; i < 7; i++)
    {
        EnQueue(Q, i);
    }
    QElemType e;
    while (SqQueueLength(Q) != 0)
    {
        DeQueue(Q, e);
        printf("%d", e);
    }
    return 0;
}