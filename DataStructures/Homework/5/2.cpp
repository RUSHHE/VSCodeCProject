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

Status CountXDepth(BiTree T, int x, int &num)
{
    num = Depth(SearchNode(T, x));
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

int main()
{
    BiTree T;
    CreateBiTree(T);
    PreRootTraverse(T);
    printf("\n");
    InRootTraverse(T);
    printf("\n");
    PostRootTraverse(T);
    printf("\n");
    printf("%d", Depth(T));
    int num = 0;
    printf("\n%d", num);
    return 0;
}