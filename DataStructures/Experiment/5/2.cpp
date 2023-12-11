#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -2
#define MAXSTRLEN 255
#define TRUE 1
#define FALSE 0
#define TElemType char
typedef int Status;
typedef struct BiTNode
{                                    // 结点结构
    TElemType data;                  // 数据域
    int layer;
    struct BiTNode *lchild, *rchild; // 左孩子域和右孩子域
} BiTNode, *BiTree;

typedef BiTree QElemType;

typedef struct QNode
{
    QElemType data;     // 数据域
    struct QNode *next; // 指针域
} QNode, *QueuePtr;

typedef struct
{
    QueuePtr front;
    QueuePtr rear; // 队尾指针
} LinkQueue;

Status CreateBiTree(BiTree &T)
{
    char ch;
    scanf("%c", &ch);
    if (ch == '#')
    {
        T = NULL;
    }
    else
    {
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return OK;
}

void PreRootTraverse(BiTree T)
{
    if (T != NULL)
    {
        printf("%c", T->data);
        PreRootTraverse(T->lchild);
        PreRootTraverse(T->rchild);
    }
}

void InRootTraverse(BiTree T)
{
    if (T != NULL)
    {
        InRootTraverse(T->lchild);
        printf("%c", T->data);
        InRootTraverse(T->rchild);
    }
}

void PostRootTraverse(BiTree T)
{
    if (T != NULL)
    {
        PostRootTraverse(T->lchild);
        PostRootTraverse(T->rchild);
        printf("%c", T->data);
    }
}

int Depth(BiTree T)
{
    int depthLeft, depthRight, depthval;
    if (T != NULL)
    {
        depthLeft = Depth(T->lchild);
        depthRight = Depth(T->rchild);
        depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
    }
    else
    {
        depthval = 0;
    }
    return depthval;
}

BiTree SearchNode(BiTree T, char x)
{
    if (T != NULL)
    {
        if (T->data == x)
        {
            return T;
        }
        else
        {
            return (SearchNode(T->lchild, x) != NULL ? SearchNode(T->lchild, x) : SearchNode(T->rchild, x));
        }
    }
    return NULL;
}

BiTree PICreateBiTree(char PreOrder[], char InOrder[], int PreIndex, int InIndex, int count)
{
    BiTree T;
    if (count > 0)
    {
        char r = PreOrder[PreIndex];
        int i = 0;
        while (i < count)
        {
            if (r == InOrder[i + InIndex])
            {
                break;
            }
            i++;
        }
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data = r;
        T->lchild = PICreateBiTree(PreOrder, InOrder, PreIndex + 1, InIndex, i);
        T->rchild = PICreateBiTree(PreOrder, InOrder, PreIndex + i + 1, InIndex + i + 1, count - i - 1);
    }
    else
    {
        T = NULL;
    }
    return T;
}

Status CopyTree(BiTree T1, BiTree &T2)
{
    if (T1 != NULL)
    {
        T2 = (BiTree)malloc(sizeof(BiTNode));
        if (!T2)
        {
            return ERROR;
        }
        T2->data = T1->data;
        CopyTree(T1->lchild, T2->lchild);
        CopyTree(T1->rchild, T2->rchild);
    }
    else
    {
        T2 = NULL;
    }
    return OK;
}

Status MirrorTree(BiTree &T)
{
    if (T == NULL)
    {
        return ERROR;
    }
    BiTree temp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = temp;
    MirrorTree(T->lchild);
    MirrorTree(T->rchild);
    return OK;
}

int CompareBiTree(BiTree T1, BiTree T2)
{
    if (T1 == NULL && T2 == NULL)
    {
        return 1;
    }
    if (T1 == NULL || T2 == NULL)
    {
        return 0;
    }
    return T1->data == T2->data && CompareBiTree(T1->lchild, T2->lchild) && CompareBiTree(T1->rchild, T2->rchild);
}

void CountLeafNode(BiTree T, int &num)
{
    if (T != NULL)
    {
        if (T->lchild == NULL && T->rchild == NULL)
        {
            num++;
        }
        CountLeafNode(T->lchild, num);
        CountLeafNode(T->rchild, num);
    }
}

void PrintLeafNode(BiTree T)
{
    if (T != NULL)
    {
        if (T->lchild == NULL && T->rchild == NULL)
        {
            printf("%c", T->data);
        }
        PrintLeafNode(T->lchild);
        PrintLeafNode(T->rchild);
    }
}

Status InitQueue(LinkQueue &Q)
{
    Q.front = (QueuePtr)malloc(sizeof(QNode));
    if (!Q.front)
    {
        return OVERFLOW;
    }
    Q.rear = Q.front;
    return OK;
}

// Status DisplayLinkQueue(LinkQueue Q)
// {
//     QueuePtr p;
//     p = Q.front->next; // 从头结点的下一个结点开始遍历
//     while (p != Q.rear)
//     { // 当没有回到尾结点时
//         printf("%c ", p->data);
//         p = p->next; // 指针后移
//     }
//     printf("\n");
//     return OK;
// }

Status EnLinkQueue(LinkQueue &Q, QElemType e)
{
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof(QNode));
    if (!p)
    {
        return ERROR;
    }
    p->data = e;
    p->next = Q.rear->next;
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
    Q.front->next = p->next; // 头结点的next指向队首元素的下一个结点
    if (p == Q.rear)
    {
        Q.rear = Q.front;
    }
    e = p->data;             // 保存队首元素的值
    free(p);
    return OK;
}

bool QueueEmpty(LinkQueue Q)
{
    return Q.front == Q.rear;
}

int QueueLength(LinkQueue Q)
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

void PrintTree(BiTree T, int depth)
// 正向显示二叉树的树状格式
{
	int pre = 0, flag = 1;
	LinkQueue Q; // 定义一个循环链队列
	InitQueue(Q); // 初始化队列
	T->layer = 0; // 根结点层次数为0
	EnLinkQueue(Q, T); // 根结点入队
	while (!QueueEmpty(Q)) // 队列不为空时循环
	{
		BiTree node; // 定义一个二叉树结点指针
		DeLinkQueue(Q, node); // 当前队首元素出队
		if (node->layer >= depth) // 若当前队首元素的层次数大于等于二叉树深度，结束循环
        {
			break;
        }
		if (pre != node->layer || flag) // 当前结点层数不等于前一结点层数或者flag值为1
		{
			printf("\n");
			for (int i = 1; i < (1 << (depth - node->layer)); i++) // 控制输出的空格数，'<<'为位运算中的左移运算符
			{
                printf(" ");
            }
			printf("%c", node->data); // 输出当前结点数据域的值
			pre = node->layer;		  // 将当前结点层次数赋值给pre
			flag = 0;				  // flag赋值为0
		}
		else // 若条件不满足
		{
			for (int i = 1; i < (1 << (depth - node->layer + 1)); i++) // 控制输出的空格数，'<<'为位运算中的左移运算符
            {
                printf(" ");
            }
			printf("%c", node->data);
		}
		if (node->lchild) // 若当前结点有左孩子
		{
			node->lchild->layer = node->layer + 1; // 左孩子的层次数等于当前结点层次数+1
			EnLinkQueue(Q, node->lchild);			   // 左孩子入队
		}
		else // 若当前结点无左孩子，补足信息，其左右孩子为空，数据域值为' '，入队
		{
			BiTree node_null = (BiTree)malloc(sizeof(BiTNode));
			node_null->layer = node->layer + 1;
			node_null->lchild = node_null->rchild = NULL;
			node_null->data = ' ';
			EnLinkQueue(Q, node_null);
		}
		if (node->rchild) // 若当前结点有右孩子
		{
			node->rchild->layer = node->layer + 1; // 右孩子的层次数等于当前结点层次数+1
			EnLinkQueue(Q, node->rchild);			   // 右孩子入队
		}
		else // 若当前结点无右孩子，补足信息，其左右孩子为空，数据域值为' '，入队
		{
			BiTree node_null = (BiTree)malloc(sizeof(BiTNode));
			node_null->layer = node->layer + 1;
			node_null->lchild = node_null->rchild = NULL;
			node_null->data = ' ';
			EnLinkQueue(Q, node_null);
		}
	}
}

void PrintTreeTurn(BiTree T, int h)
{
    if (T!= NULL)
    {
        PrintTreeTurn(T->rchild, h + 6);
        for (int i = 0; i < h; i++)
        {
            printf(" ");
        }
        printf("%c\n", T->data);
        PrintTreeTurn(T->lchild, h + 6);
    }
}

Status Path(BiTree T, BiTree p)
{
    if (T == NULL)
    {
        return FALSE;
    }
    if (T->data == p->data || Path(T->lchild, p) || Path(T->rchild, p))
    {
        printf("%c ", T->data);
        return TRUE;
    }
    return FALSE;
}

int main()
{
    int count;
    printf("请输入结点个数:");
    scanf("%d", &count);
    char preOrder[count], inOrder[count];
    // 测试用例
    //  preOrder[] = {'A', 'B', 'C', 'E', 'D'};
    //  inOrder[] = {'C', 'E', 'B', 'D', 'A'};
    getchar();
    printf("请输入先根遍历:");
    for (int i = 0; i < count; i++)
    {
        scanf("%c", preOrder + i);
    }
    getchar();
    printf("请输入中根遍历:");
    for (int i = 0; i < count; i++)
    {
        scanf("%c", inOrder + i);
    }
    int preIndex = 0;
    int inIndex = 0;
    BiTree T = PICreateBiTree(preOrder, inOrder, 0, 0, count);
    printf("树的形状如下");
    PrintTree(T, Depth(T));
    printf("\n逆时针旋转输出\n");
    PrintTreeTurn(T, 10);
    printf("以下为叶节点:");
    PrintLeafNode(T);
    printf("\n");
    getchar();
    printf("请输入要寻找的节点:");
    char x;
    scanf("%c", &x);
    BiTree X = SearchNode(T, x);
    if (X == NULL)
    {
        printf("不存在");
    }
    else if (X->lchild != NULL || X->rchild!= NULL)
    {
        printf("存在但不是叶子结点");
    } 
    else if (X->lchild == NULL && X->rchild == NULL)
    {
        printf("路径如下\n");
        Path(T, X);
    }
    return 0;
}