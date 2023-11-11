#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -2
#define MAXQSIZE 100
typedef int Status;
typedef int QElemType;

typedef struct
{
    QElemType *base;
    int rear;
    int length;
} CyQueue;

Status InitQueue(CyQueue &Q)
{
    Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
    if (!Q.base)
    {
        exit(OVERFLOW);
    }
    Q.rear = 0;
    Q.length = 0;
    return OK;
}

Status EnQueue(CyQueue &Q, QElemType e)
{
    if (Q.length == MAXQSIZE)
    {
        printf("The Queue is OVERFLOW!\n");
        return ERROR;
    }
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    Q.length++;
    return OK;
}

Status DeQueue(CyQueue &Q, QElemType &e)
{
    if (Q.length == 0)
    {
        printf("The Queue is NULL!\n");
        return ERROR;
    }
    e = Q.base[(Q.rear - Q.length + MAXQSIZE) % MAXQSIZE];
    Q.length--;
    return OK;
}

int main()
{
    CyQueue Q;
    InitQueue(Q);
    for (int i = 2; i < 7; i++)
    {
        EnQueue(Q, i);
    }
    QElemType e;
    DeQueue(Q, e);
    DeQueue(Q, e);
    DeQueue(Q, e);
    EnQueue(Q, 1);
    EnQueue(Q, 114);
    EnQueue(Q, 514);
    EnQueue(Q, 1919);
    while (Q.length)
    {
        DeQueue(Q, e);
        printf("%d ", e);
    }
    return 0;
}