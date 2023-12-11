#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -2
typedef int Status;

#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20

typedef char * VertexType;
typedef int VRType;

typedef enum
{
    UDG,
    DG,
    UDN,
    DN
} GraphKind;

typedef struct ArcNode
{
    int adjVex;
    int value;
    ArcNode * nextArc;
} ArcNode;

typedef struct VNode
{
    VertexType data;
    ArcNode * firstArc;
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct
{
    AdjList vertices;
    int vexNum, arcNum;
    int kind;
} ALGraph;

typedef struct 
{
    VertexType vexs[MAX_VERTEX_NUM];
    VRType arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphKind kind;
} MGraph;


typedef int QElemType;

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

int visited[MAX_VERTEX_NUM];

int LocateVex(ALGraph G, VertexType u)
{
    int i;
    for (i = 0; i < G.vexNum; i++)
    {
        if (strcmp(G.vertices[i].data, u) == 0)
        {
            return i;
        }
    }
    return -1;
}

int LocateVex(MGraph G, VertexType u)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (strcmp(G.vexs[i], u) == 0)
        {
            return i;
        }
    }
    return -1;
}

Status CreateUDG(ALGraph &G)
{
    int i, j, k;
    ArcNode * pi, * pj;
    VertexType v1 = (char *)malloc(20), v2 = (char *)malloc(20);
    printf("输入顶点数G.vexnum");
    scanf("%d", &G.vexNum);
    printf("输入边数G.arcnum");
    scanf("%d", &G.arcNum);
    for (i = 0; i < G.vexNum; i++)
    {
        printf("输入顶点G.vertices[%d].data", i);
        G.vertices[i].data = (char *)malloc(20);
        scanf("%s", G.vertices[i].data);
        G.vertices[i].firstArc = NULL;
    }
    for (k = 0; k < G.arcNum; k++)
    {
        printf("输入第%d条边的两个顶点:", k + 1);
        scanf("%s %s", v1, v2);
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        if (!(pi = (ArcNode *)malloc(sizeof(ArcNode))))
        {
            exit(OVERFLOW);
        }
        pi->adjVex = j;
        pi->nextArc = G.vertices[i].firstArc;
        G.vertices[i].firstArc = pi;
        if (!(pj = (ArcNode *)malloc(sizeof(ArcNode))))
        {
            exit(OVERFLOW);
        }
        pj->adjVex = j;
        pj->nextArc = G.vertices[j].firstArc;
        G.vertices[j].firstArc = pj;
    }
    return OK;
}

Status CreateDG(MGraph &G)
{
    int i, j, k;
    VertexType v1 = (char *)malloc(20), v2 = (char *)malloc(20);
    printf("输入顶点数G.vexnum:");
    scanf("%d", &G.vexnum);
    printf("输入边数G.arcnum:");
    scanf("%d", &G.arcnum);
    for (i = 0; i < G.vexnum; i++)
    {
        printf("输入顶点G.vexs[%d]:", i);
        G.vexs[i] = (char *)malloc(20);
        scanf("%s", G.vexs[i]);
    }
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j] = 0;
        }
    }
    for (k = 0; k < G.arcnum; k++)
    {
        printf("输入第%d条边<vi vj>(用空格隔开)的两个顶点:", k + 1);
        scanf("%s %s", v1, v2);
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        G.arcs[i][j] = 1;
    }
    return OK;
}

VertexType GetVex(MGraph G, int v)
{
    if (v < 0 || v >= G.vexnum)
    {
        exit(0);
    }
    return G.vexs[v];
}

VertexType GetVex(ALGraph G, int v)
{
    if (v < 0 || v >= G.vexNum)
    {
        exit(0);
    }
    return G.vertices[v].data;
}

int FirstAdjVex(MGraph G, int v)
{
    if (v < 0 || v >= G.vexnum)
    {
        return -1;
    }
    for (int j = 0; j < G.vexnum; j++)
    {
        if (G.arcs[v][j] != 0 && G.arcs[v][j] < INFINITY)
        {
            return j;
        }
    }
    return -1;
}

int FirstAdjVex(ALGraph G, int v)
{
    ArcNode * p;
    p = G.vertices[v].firstArc;
    if (p)
    {
        return p->adjVex;
    }
    else
    {
        return -1;
    }
}   

int NextAdjVex(MGraph G, int v, int w)
{
    if (v < 0 || v >= G.vexnum)
    {
        return -1;
    }
    for (int j = w + 1; j < G.vexnum; j++)
    {
        if (G.arcs[v][j]!= 0 && G.arcs[v][j] < INFINITY)
        {
            return j;
        }
    }
    return -1;
}

int NextAdjVex(ALGraph G, int v, int w)
{
    ArcNode * p;
    p = G.vertices[v].firstArc;
    while (p && p->adjVex!= w)
    {
        p = p->nextArc;
    }
    if (!p || !p->nextArc)
    {
        return -1;
    }
    else
    {
        return p->nextArc->adjVex;
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

Status EnQueue(LinkQueue &Q, QElemType e)
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

Status DeQueue(LinkQueue &Q, QElemType &e)
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

void BFS(MGraph G, int v)
{
    int u, w;
    VertexType V;
    LinkQueue Q;
    InitQueue(Q);
    visited[v] = 1;
    V = GetVex(G, v);
    printf("%s ", V);
    EnQueue(Q, v);
    while (!QueueEmpty(Q))
    {
        DeQueue(Q, u);
        for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
        {
            if (!visited[w])
            {
                visited[w] = 1;
                V = GetVex(G, w);
                printf("%s ", V);
                EnQueue(Q, w);
            }
        }
    }
}

void BFSTraverse(MGraph G)
{
    int v;
    for (v = 0; v < G.vexnum; v++)
    {
        visited[v] = 0;
    }
    for (v = 0; v < G.vexnum; v++)
    {
        if (!visited[v])
        {
            BFS(G, v);
        }
    }
}

void BFSTraverse(ALGraph G)
{
    int v, u, w;
    VertexType v1, u1, w1;
    LinkQueue Q;

    for (v = 0; v < G.vexNum; ++v)
    {
        visited[v] = 0;
    }
    InitQueue(Q);
    for(v = 0; v < G.vexNum; v++)
    {
        if (!visited[v])
        {
            visited[v] = 1;
            v1 = GetVex(G, v);
            printf("%s ", v1);
            EnQueue(Q, v);
            while (!QueueEmpty(Q))
            {
                DeQueue(Q, u);
                u1 = GetVex(G, u);
                for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
                {
                    if (!visited[w])
                    {
                        visited[w] = 1;
                        w1 = GetVex(G, w);
                        printf("%s ", w1);
                        EnQueue(Q, w);
                    }
                }
            }
        }
    }
}

void DFS(ALGraph G, int v)
{
    int w;
    VertexType v1;

    visited[v] = 1;
    v1 = GetVex(G, v);
    printf("%s ", v1);
    for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
    {
        if (!visited[w])
        {
            DFS(G, w);
        }
    }
}

void DFS(MGraph G, int v)
{
    int w;
    VertexType v1;

    visited[v] = 1;
    v1 = GetVex(G, v);
    printf("%s ", v1);
    for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
    {
        if (!visited[w])
        {
            DFS(G, w);
        }
    }
}

void DFSTraverse(ALGraph G)
{
    int v;
    for (v = 0; v < G.vexNum; v++)
    {
        visited[v] = 0;
    }
    for (v = 0; v < G.vexNum; v++)
    {
        if (!visited[v])
        {
            DFS(G, v);
        }
    }
}

void DFSTraverse(MGraph G)
{
    int v;
    for (v = 0; v < G.vexnum; v++)
    {
        visited[v] = 0;
    }
    for (v = 0; v < G.vexnum; v++)
    {
        if (!visited[v])
        {
            DFS(G, v);
        }
    }
}

int main()
{
    MGraph G1;
    ALGraph G2;
    printf("无向图1:\n");
    CreateDG(G1);
    printf("深度优先搜索遍历序列:");
    DFSTraverse(G1);
    printf("广度优先搜索遍历序列:");
    BFSTraverse(G1);
    printf("\n");
    printf("有向图2:\n");
    CreateUDG(G2);
    printf("深度优先搜索遍历序列:");
    DFSTraverse(G2);
    printf("广度优先搜索遍历序列:");
    BFSTraverse(G2);
    return 0;
}