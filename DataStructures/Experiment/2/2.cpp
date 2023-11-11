#include <stdio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define ERROR 0
#define OK 1
#define OVERFLOW -2
typedef int ElemType;
typedef int Status;

typedef struct DuLNode
{
    ElemType data;//数据域
    struct DuLNode * prior;//前置指针域
    struct DuLNode * next;//后置指针域
} CDLNode, * CDLinkList;

//创建猴群表
Status CreateCDLinkList(CDLinkList &L, int n)
{
    CDLinkList r, p;
    L = r = (CDLinkList)malloc(sizeof(CDLNode));//初始化指针，创建节点
    L->data = 1;
    n--;
    int i = 2;
    while (n--)
    {
        p = (CDLinkList)malloc(sizeof(CDLNode));
        if (!p)
        {
            return ERROR;
        }
        p->data = i;//猴的编号
        r->next = p;//连接到表中
        p->prior = r;//标记前置节点
        r = p;//指针后移
        i++;
    }
    r->next = L;//最后一个节点连接到表头
    L->prior = r;//表头的前置与r相连
    return OK;
}

//顺时针
void Pking_m(CDLinkList &L, CDLinkList &start, int m, CDLinkList &p)
{
    CDLinkList q = start;
    int num = 1;//计数器
    //寻找第m位猴
    while (num != m)
    {
        q = q->next;
        num++;
    }
    printf("%2d号猴子出圈\n", q->data);
    p = q->next;//记录猴的位置
    q->prior->next = p;//将删除后的节点相连
    p->prior = q->prior;//前置节点相连
    //如果是表头的情况
    if (q == L)
    {
        L = q->next;
    }
    free(q);
}

//逆时针
void Pkill_k(CDLinkList &L, CDLinkList &start, int k, CDLinkList &p)
{
    CDLinkList q = start;
    int num = 1;//计数器
    //寻找第k位猴
    while (num != k)
    {
        q = q->prior;
        num++;
    }
    printf("%2d号猴子出圈\n", q->data);
    p = q->prior;//记录猴的位置
    p->next = q->next;//将删除后的节点相连
    q->next->prior = p;//前置节点相连
    //如果是表头的情况
    if (q == L)
    {
        L = q->next;
    }
}

//顺时针&&逆时针淘汰
void Pking_Double(CDLinkList &L, int length, int m, int k)
{
    CDLinkList p, start = L;//开始的位置
    while (length > 1)
    {
        //顺时针
        Pking_m(L, start, m, p);
        length--;
        if (length > 1)//长度大于1的情况
        {
            //逆时针
            start = p;
            Pkill_k(L, start, k, p);
            start = p;
            length--;
        }
    }
}

int main()
{
    int n, m, k;
    printf("请输入总猴子数:");
    scanf("%d", &n);
    printf("请输入顺时针报数到第几个要出圈:");
    scanf("%d", &m);
    printf("请输入逆时针报数到第几个要出圈:");
    scanf("%d", &k);
    CDLinkList Monkey;
    CreateCDLinkList(Monkey, n);//创建猴群
    Pking_Double(Monkey, n, m, k);//淘汰
    printf("最后当选猴王的是:%d号!\n", Monkey->data);
    return 0;
}