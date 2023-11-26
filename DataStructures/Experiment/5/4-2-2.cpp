#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define MAXSIZE 100
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef char TElemType;

typedef struct BiTNode // 结点结构
{
	TElemType data;					 // 数据域
	int layer;						 // 结点所在层次数
	struct BiTNode *lchild, *rchild; // 左孩子域和右孩子域
} BiTNode, *BiTree;

struct Queue
{
	BiTree *data; // 数据域,存放的是二叉树结点地址
	int front;	  // 头指针
	int rear;	  // 尾指针
	int size;	  // 当前分配的存储容量
} q;

void push(BiTree T) // 简易版入队操作
{
	q.data[q.rear++] = T;
	if (q.rear >= q.size)
	{
		printf("no space\n");
		exit(-1);
	}
}

BiTree pop() // 简易版出队操作
{
	if (q.front >= q.rear)
	{
		printf("error\n");
		exit(-1);
	}
	return q.data[q.front++];
}

BiTree PICreateBiTree(char PreOrder[], char InOrder[], int PreIndex, int InIndex, int count)
// 已知一棵二叉树的先根遍历和中根遍历序列，构建这棵二叉树
{
	BiTree T;
	if (count > 0) // 先根和中根非空，count表示二叉树中结点数
	{
		char r = PreOrder[PreIndex]; // 取先根遍历序列中的第一个元素
		int i = 0;
		for (; i < count; i++) // 寻找根结点在中根遍历序列中的位置
		{
			if (r == InOrder[i + InIndex])
				break;
		}
		T = (BiTree)malloc(sizeof(BiTNode));															 // 建立根结点
		T->data = r;																					 // 数据域赋值
		T->lchild = PICreateBiTree(PreOrder, InOrder, PreIndex + 1, InIndex, i);						 // 建立左子树
		T->rchild = PICreateBiTree(PreOrder, InOrder, PreIndex + i + 1, InIndex + i + 1, count - i - 1); // 建立右子树
	}
	else
		T = NULL;
	return T;
}

int Depth(BiTree T)
// 求二叉树的深度
{
	int depthLeft, depthRight, depthval;
	if (T != NULL)
	{
		depthLeft = Depth(T->lchild);
		depthRight = Depth(T->rchild);
		depthval = ((depthLeft > depthRight) ? depthLeft : depthRight) + 1;
	}
	else
		depthval = 0;
	return depthval;
}

void PrintTree(BiTree T, int deepth)
// 正向显示二叉树的树状格式
{
	int pre = 0, flag = 1;
	q.data = (BiTree *)malloc(MAXSIZE * sizeof(BiTree)); // 队列分配存储空间
	q.front = q.rear = 0;								 // 初始化为空队列
	q.size = MAXSIZE;
	T->layer = 0; // 根结点层次数为0
	push(T);	  // 根结点入队
	while (1)
	{
		BiTree node = pop();	   // 当前队首元素出队
		if (node->layer >= deepth) // 若当前队首元素的层次数大于等于二叉树深度，结束循环
			break;
		if (pre != node->layer || flag) // 当前结点层数不等于前一结点层数或者flag值为1
		{
			printf("\n");
			for (int i = 1; i < (1 << (deepth - node->layer)); i++) // 控制输出的空格数，'<<'为位运算中的左移运算符
				printf(" ");
			printf("%c", node->data); // 输出当前结点数据域的值
			pre = node->layer;		  // 将当前结点层次数赋值给pre
			flag = 0;				  // flag赋值为0
		}
		else // 若条件不满足
		{
			for (int i = 1; i < (1 << (deepth - node->layer + 1)); i++) // 控制输出的空格数，'<<'为位运算中的左移运算符
				printf(" ");
			printf("%c", node->data);
		}
		if (node->lchild) // 若当前结点有左孩子
		{
			node->lchild->layer = node->layer + 1; // 左孩子的层次数等于当前结点层次数+1
			push(node->lchild);					   // 左孩子入队
		}
		else // 若当前结点无左孩子，补足信息，其左右孩子为空，数据域值为' '，入队
		{
			BiTree node_null = (BiTree)malloc(sizeof(BiTNode));
			node_null->layer = node->layer + 1;
			node_null->lchild = node_null->rchild = NULL;
			node_null->data = ' ';
			push(node_null);
		}
		if (node->rchild) // 若当前结点有右孩子
		{
			node->rchild->layer = node->layer + 1; // 右孩子的层次数等于当前结点层次数+1
			push(node->rchild);					   // 右孩子入队
		}
		else // 若当前结点无右孩子，补足信息，其左右孩子为空，数据域值为' '，入队
		{
			BiTree node_null = (BiTree)malloc(sizeof(BiTNode));
			node_null->layer = node->layer + 1;
			node_null->lchild = node_null->rchild = NULL;
			node_null->data = ' ';
			push(node_null);
		}
	}
}

void PrintTreeTurn(BiTree T, int h)
// 逆时针旋转90度以树状格式输出二叉树
{
	int i;
	if (T != NULL)
	{
		PrintTreeTurn(T->rchild, h + 6); // 在右子树上执行的递归操作
		for (i = 1; i <= h; i++)
			printf(" ");
		printf("%c\n", T->data);		 // 输出根结点数据域值
		PrintTreeTurn(T->lchild, h + 6); // 在左子树上执行的递归操作
	}
}

void PrintLeaf(BiTree T)
// 输出二叉树中的所有叶结点
{
	if (T != NULL)
	{
		if (T->lchild == NULL && T->rchild == NULL) // 若判断为叶结点，则输出该结点的数据域值
			printf("%c  ", T->data);
		PrintLeaf(T->lchild); // 在左子树上执行的递归操作
		PrintLeaf(T->rchild); // 在右子树上执行的递归操作
	}
}

void Locate(BiTree T, char x, BiTree &p)
// 查找指定的结点，返回指向该结点的指针
{
	if (T != NULL)
	{
		if (T->data == x) // 找到所需的结点
			p = T;
		Locate(T->lchild, x, p); // 在左子树中执行的递归操作
		Locate(T->rchild, x, p); // 在右子树中执行的递归操作
	}
}

Status Path(BiTree T, BiTree p)
// 输出指定结点到根结点的路径的递归算法
{
	if (T == NULL)
		return FALSE;
	if (T->data == p->data || Path(T->lchild, p) || Path(T->rchild, p))
	{
		printf("%c ", T->data);
		return TRUE;
	}
	return FALSE;
}

int main()
{
	BiTree T, p;
	char PreNode[100], InNode[100];
	int i = 0, n, j, deepth;
	char ch, x;
	char *array;
	printf("请输入二叉树中的结点数量:");
	scanf("%d", &n);
	getchar();
	printf("请输入二叉树的先根遍历序列:");
	while ((ch = getchar()) && ch != '\n')
		PreNode[i++] = ch;
	printf("请输入二叉树的中根遍历序列:");
	i = 0;
	while ((ch = getchar()) && ch != '\n')
		InNode[i++] = ch;
	T = PICreateBiTree(PreNode, InNode, 0, 0, n);
	printf("\n正向以树状格式显示的二叉树:\n");
	deepth = Depth(T);
	PrintTree(T, deepth);
	printf("\n逆时针旋转90度以树状格式显示的二叉树:\n");
	PrintTreeTurn(T, 10);
	printf("\n");
	printf("这棵二叉树中所有的叶结点为：\n");
	PrintLeaf(T);
	printf("\n");
	p = NULL;
	printf("请输入需要查找的叶结点的数据域的值:");
	scanf("%c", &ch);
	getchar();
	Locate(T, ch, p);
	if (p != NULL)
	{
		if (p->lchild == NULL && p->rchild == NULL)
		{
			printf("从此叶结点到根结点的路径为:");
			Path(T, p);
		}
		else
			printf("此结点不是叶结点！");
	}
	else
		printf("此叶结点不存在！");
	printf("\n");
	return 0;
}