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

int main()
{
    BiTree T;
    char x;
    CreateBiTree(T);
    getchar();
    PreRootTraverse(T);
    printf("\n");
    MirrorTree(T);
    PreRootTraverse(T);
    printf("\n");
    // scanf("%c", &x);
    // getchar();
    // if (SearchNode(T2, x))
    // {
    //     printf("Search Succeeded!");
    // }
    // else
    // {
    //     printf("Search Failed!");
    // }
    return 0;
}