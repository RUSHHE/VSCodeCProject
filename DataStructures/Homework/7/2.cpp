#include <stdio.h>
#include <stdlib.h>
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

//尾插法
Status CreateList(LinkList &L, int n)
{
    ElemType node;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    LinkList r = L, p;
    printf("Please input the elem:\n");
    int i = 0;
    while (i != n)
    {
        p = (LinkList)malloc(sizeof(LNode));//每次创建一个节点p放置数据
        if (!p)
        {
            return ERROR;
        }
        scanf("%d", &node);
        p->data = node;//给新节点以数据
        p->next = NULL;//后置节点为空
        r->next = p;//使节点p接在r的后面
        r = p;//r指针后移到p位置
        i++;//计数器
    }
    return OK;
}

//插入
Status List_Insert(LinkList &L, int i, ElemType e)//单链表，第几位前插入，元素
{
    LinkList p = L, s;
    int j = 0;
    //找到插入到位置
    while (p && j < i - 1)
    {
        p = p->next;
        ++j;
    }
    //节点不存在、越界
    if (!p || j > i - 1)
    {
        return ERROR;
    }
    s = (LinkList)malloc(sizeof(LNode));
    s->data = e;//插入的元素
    s->next = p->next;//新节点插入
    p->next = s;//将新节点接在p之后
    return OK;
}

//删除
Status List_Delete(LinkList &L, int i, ElemType &e)
{
    LinkList p = L, q;
    int j = 0;
    //找到元素位置
    while (p->next && j < i - 1)
    {
        p = p->next;
        ++j;
    }
    //节点不存在、越界
    if (!p->next || j > i - 1)
    {
        return ERROR;
    }
    q = p->next;//记录删除元素（p的后继节点）
    p->next = q->next;//将删除元素的前后连接
    e = q->data;//记录删除的元素
    free(q);
    return OK;
}

void Merge(LinkList &LA, LinkList &LB)
{
    LinkList p = LA, r1 = LA->next, r2 = LB->next; // p指针指向LA的头结点
    while (r1 && r2)
    {
        if (r1->data <= r2->data)
        {
            p->next = r1;//连接节点到p之后
            p = r1;//p后移
            r1 = r1->next;//r1后移
        }
        else
        {
            p->next = r2;//连接节点到p之后
            p = r2;//p后移
            r2 = r2->next;//r2后移
        }
    }
    //将没连接完的表继续连接
    if (r1 != NULL)
    {
        p->next = r1;
    }
    else if (r2 != NULL)
    {
        p->next = r2;
    }
    free(LB);
}

//查询
Status LocateElem(LinkList L, int i, ElemType &e)
{
    LinkList p = L->next;
    int j = 1;
    //指针移动到指定位置
    while (p && j < i)
    {
        p = p->next;
        j++;
    }
    //节点不存在或者越界
    if (!p || j > i)
    {
        return ERROR;
    }
    //返回找到的元素
    e = p->data;
    return OK;
}

//打印表中所有元素
void DisplayList(LinkList L)
{
    LinkList p = L->next;
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int Length(LinkList L)
{
    LinkList p = L->next;
    int i = 0;
    while (p)
    {
        p = p->next;
        i++;
    }
    return i;
}

Status InsertSort(LinkList &L)
{
    if (L->next == NULL)
    {
        return OK;
    }
    LinkList p, q, pre;
    p = L->next->next; // 从第二个节点开始
    L->next->next = NULL; // 将原表设置成只有第一个元素
    while (p != NULL)
    {
        q = p->next; // q是下一个元素
        pre = L; // 用pre保存L
        while (pre->next!= NULL && pre->next->data < p->data)
        {
            pre = pre->next; // 前面已经有序,扫描到合适的位置
        }
        p->next = pre->next;
        pre->next = p;
        p = q;
    }
    return OK;
}

int main()
{
    LinkList L;
    CreateList(L, 9);
    DisplayList(L);
    InsertSort(L);
    DisplayList(L);
    return 0;
}