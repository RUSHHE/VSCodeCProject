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

typedef char *VertexType;
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
    ArcNode *nextArc;
} ArcNode;

typedef struct VNode
{
    VertexType data;
    ArcNode *firstArc;
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct
{
    AdjList vertices;
    int vexNum, arcNum;
    int kind;
} ALGraph;

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

// Status CreateUDN(ALGraph &G)
// {
//     int i, j, k, w;
//     ArcNode * pi, * pj;
//     VertexType v1 = (char *)malloc(20), v2 = (char *)malloc(20);
//     printf("输入顶点数G.vexnum:");
//     scanf("%d", &G.vexNum);
//     printf("输入边数G.arcNum:");
//     scanf("%d", &G.arcNum);
//     for (i = 0; i < G.vexNum; i++)
//     {
//         printf("输入顶点G.vertices[%d].data:", i);
//         G.vertices[i].data = (char *)malloc(20);
//         scanf("%s", G.vertices[i].data);
//         G.vertices[i].firstArc = NULL;
//     }
//     for (k = 0; k < G.arcNum; k++)
//     {
//         printf("输入第%d条边vi、vj和权值w:", k + 1);
//         scanf("%s %s %d", v1, v2, &w);
//         i = LocateVex(G, v1);
//         j = LocateVex(G, v2);
//         if (!(pi = (ArcNode *)malloc(sizeof(ArcNode))))
//         {
//             exit(OVERFLOW);
//         }
//         pi->adjVex = j;
//         pi->value = w;
//         pi->nextArc = G.vertices[i].firstArc;
//         G.vertices[i].firstArc = pi;
//         if (!(pj = (ArcNode *)malloc(sizeof(ArcNode))))
//         {
//             exit(OVERFLOW);
//         }
//         pj->adjVex = i;
//         pj->value = w;
//         pj->nextArc = G.vertices[j].firstArc;
//         G.vertices[j].firstArc = pj;
//     }
//     return OK;
// }

Status CreateUDN(ALGraph &G)
{
    ArcNode *pi, *pj;
    VertexType v1 = (char *)malloc(20), v2 = (char *)malloc(20);
    G.vexNum = 19;
    G.arcNum = 23;

    // for (i = 0; i < G.vexNum; i++)
    // {
    //     printf("输入顶点G.vertices[%d].data:", i);
    //     G.vertices[i].data = (char *)malloc(20);
    //     scanf("%s", G.vertices[i].data);
    //     G.vertices[i].firstArc = NULL;
    // }
    for (int i = 0; i < G.vexNum; i++)
    {
        G.vertices[i].data = (char *)malloc(20);
        G.vertices[i].firstArc = NULL;
    }
    G.vertices[0].data = "北京";
    G.vertices[1].data = "天津";
    G.vertices[2].data = "西宁";
    G.vertices[3].data = "兰州";
    G.vertices[4].data = "西安";
    G.vertices[5].data = "郑州";
    G.vertices[6].data = "徐州";
    G.vertices[7].data = "成都";
    G.vertices[8].data = "武汉";
    G.vertices[9].data = "上海";
    G.vertices[10].data = "昆明";
    G.vertices[11].data = "贵阳";
    G.vertices[12].data = "株洲";
    G.vertices[13].data = "南昌";
    G.vertices[14].data = "福州";
    G.vertices[15].data = "南宁";
    G.vertices[16].data = "柳州";
    G.vertices[17].data = "广州";
    G.vertices[18].data = "深圳";

    // for (k = 0; k < G.arcNum; k++)
    // {
    //     printf("输入第%d条边vi、vj和权值w:", k + 1);
    //     scanf("%s %s %d", v1, v2, &w);
    //     i = LocateVex(G, v1);
    //     j = LocateVex(G, v2);
    //     if (!(pi = (ArcNode *)malloc(sizeof(ArcNode))))
    //     {
    //         exit(OVERFLOW);
    //     }
    //     pi->adjVex = j;
    //     pi->value = w;
    //     pi->nextArc = G.vertices[i].firstArc;
    //     G.vertices[i].firstArc = pi;
    //     if (!(pj = (ArcNode *)malloc(sizeof(ArcNode))))
    //     {
    //         exit(OVERFLOW);
    //     }
    //     pj->adjVex = i;
    //     pj->value = w;
    //     pj->nextArc = G.vertices[j].firstArc;
    //     G.vertices[j].firstArc = pj;
    // }
    int i, j, w;
    i = LocateVex(G, "北京");
    j = LocateVex(G, "天津");
    w = 137;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "北京");
    j = LocateVex(G, "郑州");
    w = 695;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "天津");
    j = LocateVex(G, "徐州");
    w = 674;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "西宁");
    j = LocateVex(G, "兰州");
    w = 216;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "兰州");
    j = LocateVex(G, "西安");
    w = 676;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "西安");
    j = LocateVex(G, "郑州");
    w = 511;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "郑州");
    j = LocateVex(G, "徐州");
    w = 349;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "西安");
    j = LocateVex(G, "成都");
    w = 842;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "郑州");
    j = LocateVex(G, "武汉");
    w = 534;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "徐州");
    j = LocateVex(G, "上海");
    w = 651;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "成都");
    j = LocateVex(G, "昆明");
    w = 1100;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "成都");
    j = LocateVex(G, "贵阳");
    w = 967;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "武汉");
    j = LocateVex(G, "株洲");
    w = 409;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "上海");
    j = LocateVex(G, "南昌");
    w = 825;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "昆明");
    j = LocateVex(G, "贵阳");
    w = 639;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "贵阳");
    j = LocateVex(G, "株洲");
    w = 902;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "株洲");
    j = LocateVex(G, "南昌");
    w = 367;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "贵阳");
    j = LocateVex(G, "柳州");
    w = 607;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "株洲");
    j = LocateVex(G, "柳州");
    w = 672;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "株洲");
    j = LocateVex(G, "广州");
    w = 675;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "南昌");
    j = LocateVex(G, "福州");
    w = 622;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "南宁");
    j = LocateVex(G, "柳州");
    w = 255;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    i = LocateVex(G, "广州");
    j = LocateVex(G, "深圳");
    w = 140;
    pi = (ArcNode *)malloc(sizeof(ArcNode));
    pi->adjVex = j;
    pi->value = w;
    pi->nextArc = G.vertices[i].firstArc;
    G.vertices[i].firstArc = pi;
    pj = (ArcNode *)malloc(sizeof(ArcNode));
    pj->adjVex = i;
    pj->value = w;
    pj->nextArc = G.vertices[j].firstArc;
    G.vertices[j].firstArc = pj;

    return OK;
}

VertexType GetVex(ALGraph G, int v)
{
    if (v < 0 || v >= G.vexNum)
    {
        exit(0);
    }
    return G.vertices[v].data;
}

int FirstAdjVex(ALGraph G, int v)
{
    ArcNode *p;
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

int NextAdjVex(ALGraph G, int v, int w)
{
    ArcNode *p;
    p = G.vertices[v].firstArc;
    while (p && p->adjVex != w)
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
    Q.rear->next = p; // 尾节点接上新结点
    Q.rear = p;       // 队尾指针指向新结点
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
    e = p->data; // 保存队首元素的值
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
    for (v = 0; v < G.vexNum; v++)
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

// 定义一个结构体，用于存储每个顶点的最短路径信息
typedef struct
{
    int dist; // 从源点到该顶点的最短距离
    int prev; // 该顶点的前驱顶点
    int flag; // 该顶点是否已经确定最短路径
} PathInfo;

// 定义一个函数，用于初始化每个顶点的最短路径信息
void InitPathInfo(ALGraph G, VertexType s, PathInfo P[])
{
    int i, j;
    int s_index = LocateVex(G, s); // 源点在邻接表中的位置
    for (i = 0; i < G.vexNum; i++)
    {
        P[i].dist = INFINITY; // 初始时，所有顶点的最短距离都设为无穷大
        P[i].prev = -1; // 初始时，所有顶点的前驱顶点都设为-1
        P[i].flag = 0; // 初始时，所有顶点都未确定最短路径
    }
    P[s_index].dist = 0; // 源点到自身的最短距离为0
    P[s_index].flag = 1; // 源点已经确定最短路径
    ArcNode *p = G.vertices[s_index].firstArc; // 指向源点的第一个邻接点
    while (p != NULL)
    {
        j = p->adjVex; // 邻接点在邻接表中的位置
        P[j].dist = p->value; // 源点到邻接点的最短距离为边的权值
        P[j].prev = s_index; // 邻接点的前驱顶点为源点
        p = p->nextArc; // 指向下一个邻接点
    }
}

// 定义一个函数，用于在未确定最短路径的顶点中，找出距离源点最近的顶点
int FindMinDist(ALGraph G, PathInfo P[])
{
    int i, min, min_index;
    min = INFINITY; // 初始时，最小距离设为无穷大
    min_index = -1; // 初始时，最小距离顶点设为-1
    for (i = 0; i < G.vexNum; i++)
    {
        if (P[i].flag == 0 && P[i].dist < min) // 如果该顶点未确定最短路径，且距离小于当前最小距离
        {
            min = P[i].dist; // 更新最小距离
            min_index = i; // 更新最小距离顶点
        }
    }
    return min_index; // 返回最小距离顶点的位置
}

// 定义一个函数，用于更新最小距离顶点的邻接点的最短路径信息
void UpdatePathInfo(ALGraph G, int k, PathInfo P[])
{
    int j;
    ArcNode *p = G.vertices[k].firstArc; // 指向最小距离顶点的第一个邻接点
    while (p != NULL)
    {
        j = p->adjVex; // 邻接点在邻接表中的位置
        if (P[j].flag == 0 && P[k].dist + p->value < P[j].dist) // 如果该顶点未确定最短路径，且通过最小距离顶点可以缩短其距离
        {
            P[j].dist = P[k].dist + p->value; // 更新该顶点的最短距离
            P[j].prev = k; // 更新该顶点的前驱顶点
        }
        p = p->nextArc; // 指向下一个邻接点
    }
}

void Dijkstra(ALGraph G, VertexType s, VertexType t)
{
    int i, k;
    PathInfo P[MAX_VERTEX_NUM]; // 定义一个数组，用于存储每个顶点的最短路径信息
    InitPathInfo(G, s, P); // 初始化每个顶点的最短路径信息
    for (i = 1; i < G.vexNum; i++) // 重复n-1次
    {
        k = FindMinDist(G, P); // 找出距离源点最近的顶点
        if (k == -1) // 如果没有找到，说明图不连通，退出循环
        {
            break;
        }
        P[k].flag = 1; // 该顶点已经确定最短路径
        UpdatePathInfo(G, k, P); // 更新该顶点的邻接点的最短路径信息
    }
    int t_index = LocateVex(G, t); // 目标点在邻接表中的位置
    if (P[t_index].dist == INFINITY) // 如果目标点的最短距离仍为无穷大，说明不存在从源点到目标点的路径
    {
        printf("%s 到 %s无路可达\n", s, t); // 输出提示信息
    }
    else // 否则，存在从源点到目标点的最短路径
    {
        printf("%s 到 %s 的最短路径长度为 %d\n", s, t, P[t_index].dist); // 输出最短路径的长度
        printf("此路径是: "); // 输出最短路径的顶点序列
        int path[MAX_VERTEX_NUM]; // 定义一个数组，用于存储最短路径的顶点
        int count = 0; // 定义一个计数器，用于记录最短路径的顶点个数
        i = t_index; // 从目标点开始
        while (i != -1) // 重复直到源点
        {
            path[count++] = i; // 将当前顶点加入路径数组
            i = P[i].prev; // 跳转到前驱顶点
        }
        for (i = count - 1; i >= 0; i--) // 从后往前输出路径数组
        {
            printf("%s", G.vertices[path[i]].data); // 输出当前顶点的数据
            if (i > 0) // 如果不是最后一个顶点
            {
                printf("->");
            }
        }
        printf("\n");
    }
}

int main()
{
    ALGraph G;
    CreateUDN(G);
    VertexType s1 = (char *)malloc(20), s2 = (char *)malloc(20);
    scanf("%s %s", s1, s2);
    Dijkstra(G, s1, s2);
    return 0;
}