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
    struct BiTNode *lchild, *rchild; // 左孩子域和右孩子域
} BiTNode, *BiTree;

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

Status SearchNode(BiTree T, char x)
{
    if (T != NULL)
    {
        if (T->data == x)
        {
            return OK;
        }
        else
        {
            return (SearchNode(T->lchild, x) != ERROR ? SearchNode(T->lchild, x) : SearchNode(T->rchild, x));
        }
    }
    return ERROR;
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

int main()
{
    BiTree T, cpyT;
    T = NULL;
    cpyT = NULL;
    int num;
    while (true)
    {
        printf("建立二叉树的菜单\n");
        printf("1.建立二叉树\n");
        printf("2.复制一棵二叉树\n");
        printf("3.判断两棵二叉树相等\n");
        printf("4.求二叉树的叶子结点\n");
        printf("5.求二叉树的深度\n");
        printf("6.查找\n");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("此为标明空子树的完整先根遍历");
            getchar();
            CreateBiTree(T);
            printf("先根:");
            PreRootTraverse(T);
            printf("\n");
            printf("中根:");
            InRootTraverse(T);
            printf("\n");
            printf("后根:");
            PostRootTraverse(T);
            printf("\n");
            break;
        case 2:
            if (T == NULL)
            {
                printf("你害没建树呢\n");
                break;
            }
            CopyTree(T, cpyT);
            printf("复制成功\n");
            printf("后根:");
            PostRootTraverse(cpyT);
            printf("\n");
            break;
        case 3:
            if (CompareBiTree(T, cpyT))
            {
                printf("这两棵树是相等的，复制操作成功\n");
            }
            else
            {
                printf("这两棵树是不相等的，复制操作不成功\n");
            }
            break;
        case 4:
            num = 0;
            CountLeafNode(T, num);
            printf("叶结点个数为%d\n", num);
            printf("以下为叶子节点:");
            PrintLeafNode(T);
            printf("\n");
            break;
        case 5:
            printf("树的深度为%d\n", Depth(T));
            break;
        case 6:
            if (T == NULL)
            {
                printf("树是空的查个鬼");
                break;
            }
            printf("你要查哪个字母？");
            char x;
            getchar();
            scanf("%c", &x);
            if (SearchNode(T, x) == OK)
            {
                printf("OK\n");
            }
            else
            {
                printf("ERROR\n");
            }
            break;
        default:
            printf("没有这个选项，程序自动退出");
            exit(0);
            break;
        }
    }
    return 0;
}