#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 100 // 栈初始分配空间的容量
#define STACKINCREMENT 10   // 栈增加分配空间的量
#define MAXQSIZE 20         // 队列最大存储容量
#define OK 1
#define TRUE 1
#define ERROR 0
#define FALSE 0
#define OVERFLOW -2
typedef int SElemType;
typedef int Status;
typedef struct
{
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;
typedef int QElemType;
typedef struct
{
    QElemType *base; // 队列存储空间基地址
    int front;       // 指示队首元素存储单元的位置（队首指针）
    int rear;        // 指示队尾元素存储单元的位置（队尾指针）
} SqQueue;

Status InitStack(SqStack &S)
// 创建一个空的顺序栈S
{
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType)); // 分配预定义大小的空间
    if (!S.base)                                                       // 如果存储空间分配失败
    {
        printf("OVERFLOW\n");
        return ERROR;
    }
    S.top = S.base;                // 置当前栈顶指针指向栈底位置
    S.stacksize = STACK_INIT_SIZE; // 置当前分配的存储空间容量为STACK_INIT_SIZE的值
    return OK;
}

Status Push(SqStack &S, SElemType e)
// 在顺序栈S中插入新的元素e，使其成为新的栈顶元素
{
    if (S.top - S.base >= S.stacksize) // 当前存储空间满，则扩充空间
    {
        S.base = (SElemType *)malloc((S.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!S.base) // 如果存储空间分配失败
        {
            printf("OVERFLOW\n");
            return ERROR;
        }
        S.top = S.base + S.stacksize;  // 栈顶指针重新指向当前栈顶元素的下一位置
        S.stacksize += STACKINCREMENT; // 修改增加空间后的存储空间容量
    }
    *(S.top)++ = e; // e进栈后，栈顶指针后移一位
    return OK;
}

Status Pop(SqStack &S, SElemType &e)
// 删除顺序栈S中的栈顶元素，并用e返回其值
{
    if (S.base == S.top) // 如果栈空
    {
        printf("The Stack is NULL\n");
        return ERROR;
    }
    e = *--S.top; // 删除栈顶元素并用e返回其值
    return OK;
}

Status GetTop(SqStack S, SElemType &e)
// 取顺序栈S栈顶元素，并用e返回其值
{
    if (S.base == S.top) // 如果栈空
    {
        printf("The Stack is NULL\n");
        return ERROR;
    }
    e = *(S.top - 1); // 取栈顶元素的值并用e返回
    return OK;
}

Status StackEmpty(SqStack S)
// 判断顺序栈S是否为空栈，如果为空栈，返回TRUE；否则返回FALSE
{
    if (S.base == S.top)
        return TRUE;
    else
        return FALSE;
}

Status DisplayStack(SqStack S)
// 输出顺序栈S中所有元素的值,顺序为从栈底到栈顶
{
    SElemType *p;
    if (S.base == S.top) // 如果栈空
    {
        printf("The Stack is NULL\n");
        return ERROR;
    }
    printf("栈底到栈顶:");
    for (p = S.base; p < S.top; p++)
        printf("%d  ", *p);
    printf("\n");
    return OK;
}

Status DestroyStack(SqStack &S)
// 将顺序栈S销毁
{
    free(S.base); // 释放已分配的存储空间
    S.base = NULL;
    S.top = NULL;
    S.stacksize = 0;
    return OK;
}

Status ClearStack(SqStack &S)
// 将顺序栈S清空为空栈
{
    if (S.base)
        S.top = S.base;
    return OK;
}

Status InitQueue(SqQueue &Q)
// 创建一个空的循环队列Q
{
    Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
    if (!Q.base)
        exit(OVERFLOW); // 如果空间分配失败
    Q.front = Q.rear = 0;
    return OK;
}

Status EnQueue(SqQueue &Q, QElemType e)
// 在循环队列Q中插入新的元素e，使其成为新的队尾元素
{
    if ((Q.rear + 1) % MAXQSIZE == Q.front)
        return ERROR;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    return OK;
}

Status DeQueue(SqQueue &Q, QElemType &e)
// 在循环队列Q中删除队首元素，并用e返回其值
{
    if (Q.rear == Q.front)
        return ERROR;
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
    return OK;
}

int QueueLength(SqQueue Q)
// 返回当前循环队列中数据元素的个数
{
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

void DestroyQueue(SqQueue &Q)
// 销毁循环队列Q
{
    if (Q.base)
        free(Q.base);
    Q.base = NULL;
    Q.front = Q.rear = 0;
}

void ClearQueue(SqQueue &Q)
// 清空循环队列Q
{
    Q.front = Q.rear = 0;
}

Status EmptyQueue(SqQueue Q)
// 判断循环队列是否为空，若空返回TRUE，否则返回FALSE
{
    if (Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}

void DisplayQueue(SqQueue Q)
// 从队首到队尾，依次输出循环队列中各数据元素的值
{
    int i;
    for (i = Q.front; i != Q.rear; i = (i + 1) % MAXQSIZE)
        printf("%3d", Q.base[i]);
    printf("\n");
}

Status FrontToRear(SqQueue &Q)
// 将队首元素移至队尾
{
    if (EmptyQueue(Q))
        return ERROR;
    Q.base[Q.rear] = Q.base[Q.front];
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    Q.front = (Q.front + 1) % MAXQSIZE;
    return OK;
}

Status InsertAtButtom(SqStack &S, SElemType k)
// 将出栈的元素插入栈底
{
    SElemType t;
    if (StackEmpty(S)) // 栈为空后将该元素插入栈底
    {
        Push(S, k);
        return OK;
    }
    Pop(S, t);
    InsertAtButtom(S, k); // 将栈中的元素递归出至栈为空
    Push(S, t);           // 将开始递归出的元素依次入栈
}

Status ReverseStack(SqStack &S)
// 栈逆置
{
    SElemType k;
    if (StackEmpty(S))
        return OK;
    Pop(S, k);
    ReverseStack(S);      // 将原栈中的元素递归出栈
    InsertAtButtom(S, k); // 将出栈的元素插入栈底
}

int LoopJudge(SqQueue Q, SqStack S)
// 循环结束条件判断
{
    int n, i;
    int count = 0;
    SElemType k;
    n = QueueLength(Q);
    int n1 = Q.front;
    for (i = 0; i < n; i++)
    {
        GetTop(S, k);
        if (Q.base[n1] != k)
        {
            count++;
            n1 = (n1 + 1) % MAXQSIZE;
        }
    }
    if (count == n)
        return TRUE;
    else
        return FALSE;
}

int CountStu(SqQueue Q, SqStack S)
{
    QElemType e;
    SElemType m, k;

    int i, j = 0;
    while (!LoopJudge(Q, S))
    {
        GetTop(S, k);
        if (Q.base[Q.front] == k)
        {
            DeQueue(Q, e);
            Pop(S, m);
        }
        else
            FrontToRear(Q);
    }
    if (EmptyQueue(Q))
        return 0;
    else
        return QueueLength(Q);
}

int main()
{
    SqQueue Q;
    SqStack S;
    QElemType e;
    SElemType k;
    int i, n, m;
    printf("输入学生数（面包数量相同）\n");
    scanf("%d", &n);
    printf("初始化学生队列\n");
    InitQueue(Q);
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &e);
        EnQueue(Q, e);
    }
    printf("初始化面包栈\n");
    InitStack(S);
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &k);
        Push(S, k);
    }
    ReverseStack(S);
    m = CountStu(Q, S);
    if (m == 0)
        printf("所有同学都吃到午餐\n");
    else
        printf("还有%d位同学没吃到午餐\n", m);
}