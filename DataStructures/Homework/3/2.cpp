#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -2
typedef int Status;
typedef int SElemType;

typedef struct
{
    SElemType *base1, *base2;
    SElemType *top1, *top2;
} BDStacktype;

Status InitBDStack(BDStacktype &tws, int n)
{
    tws.base1 = (SElemType *)malloc(sizeof(SElemType));
    if (!tws.base1)
    {
        printf("内存不足，无法初始化\n");
        return ERROR;
    }
    tws.base2 = tws.base1 + n - 1;
    tws.top1 = tws.base1;
    tws.top2 = tws.base2;
    return OK;
}

Status Push(BDStacktype &tws, int i, SElemType e)
{
    if (tws.top1 == tws.top2)
    {
        return ERROR;
    }
    if (i == 1)
    {
        *(tws.top1++) = e;
    }
    else if (i == 2)
    {
        *(tws.top2--) = e;
    }
    else
    {
        return ERROR;
    }
    return OK;
}

Status Pop(BDStacktype &tws, int i, SElemType &e)
{
    if (i == 1)
    {
        if (tws.top1 == tws.base1)
        {
            return ERROR;
        }
        e = *(--tws.top1);
    }
    else if (i == 2)
    {
        if (tws.top2 == tws.base2)
        {
            return ERROR;
        }
        e = *(++tws.top2);
    }
    else
    {
        return ERROR;
    }
    return OK;
}

int main()
{
    BDStacktype tws;
    InitBDStack(tws, 10);
    Push(tws, 1, 114);
    Push(tws, 1, 514);
    Push(tws, 2, 1919);
    Push(tws, 2, 810);
    SElemType e;
    while (tws.top1 != tws.base1 && tws.base2 != tws.top2)
    {
        Pop(tws, 1, e);
        printf("%d ", e);
        Pop(tws, 2, e);
        printf("%d ", e);
    }
    
    return 0;
}