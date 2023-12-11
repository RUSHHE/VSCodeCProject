void ShortestPath_DIJ(MGraph G, int start, int end, int *prev, int *dist)
// prev为前驱顶点数组，即prev[i]的值是“顶点vs”到“顶点i”的最短路径所经历的全部顶点中
// 位于"顶点i"之前的那个顶点。dist -- 长度数组。即，dist[i]是"顶点vs"到"顶点i"的最短路径的长度
{
  int i, j, k, min, tmp;
  // flag[i]=1表示"顶点v"到"顶点i"的最短路径已成功获取。
  bool flag[MAX_VERTEX_NUM];
  // 初始化
  for (i = 0; i < G.vexnum; i++)
  {
    flag[i] = FALSE;            // 顶点i的最短路径还没获取到
    prev[i] = start;            // 顶点i的前驱顶点为0
    dist[i] = G.arcs[start][i]; // 顶点i的最短路径为“顶点v”到“顶点i”的权
  }
  // 对"顶点v"自身进行初始化
  flag[start] = 1;
  dist[start] = 0;
  // 遍历G.vexnum-1次；每次找出一个顶点的最短路径
  for (i = 1; i < G.vexnum; i++)
  {
    // 寻找当前最小的路径
    // 即，在未获取最短路径的顶点中，找到离vs最近的顶点(k)
    min = INFINITY;
    for (j = 0; j < G.vexnum; j++)
    {
      if (!flag[j] && dist[j] < min)
      {
        min = dist[j];
        k = j;
      }
    }
    // 标记“顶点k”为已经获取到最短路径
    flag[k] = TRUE;
    // 修正当前最短路径和前驱顶点
    // 当已经“顶点k的最短路径”之后，更新“未获取最短路径的顶点的最短路径和前驱顶点”
    for (j = 0; j < G.vexnum; j++)
    { // 防止溢出
      tmp = (G.arcs[k][j] == INFINITY ? INFINITY : (min + G.arcs[k][j]));
      if (!flag[j] && (tmp < dist[j]))
      {
        dist[j] = tmp;
        prev[j] = k;
      }
    }
  }
}

void DisplayShortestPath(MGraph G, int start, int end, int *prev, int *dist)
{ // 打印dijkstra最短路径的结果
  int cnt = 0, i = end;
  int next[MAX_VERTEX_NUM];
  while (i != start)
  {
    next[cnt++] = i;
    i = prev[i];
  }
  next[cnt++] = start;
  printf("最短路径是：");
  for (i = cnt - 1; i > 0; i--)
    printf("%s->", G.vexs[next[i]]);
  printf("%s\n", G.vexs[next[0]]);
  printf("最短路径长度是：%d", dist[end]);
}

int main()
{
  MGraph G;
  char sstart[20], send[20];
  int i, j, start, end;
  CreateDN(G);
  int prev[MAX_VERTEX_NUM], dist[MAX_VERTEX_NUM];
  printf("请输入起点和终点：");
  scanf("%s %s", sstart, send);
  start = LocateVex(G, sstart);
  end = LocateVex(G, send); // 确定v1和v2在G中位置
  ShortestPath_DIJ(G, start, end, prev, dist);
  DisplayShortestPath(G, start, end, prev, dist);
}
