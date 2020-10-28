#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

// int main()
// {
//     test();
//     return 0;
// }

void test()
{
    AdjMatrixGraph g;
    int i, j;
    g.n = 6;
    g.e = 9;
    for (i=0; i<g.n; i++)
    {
        for(j=0; j<g.n; j++)
        {
            if(i == j)
                g.edges[i][j] = 0;
            else
                g.edges[i][j] = INF;
        }
        g.vertex[i].no = i;
    }
    g.edges[0][1] = g.edges[1][0] = 250;
    g.edges[0][3] = g.edges[3][0] = 350;
    g.edges[0][5] = g.edges[5][0] = 300;
    g.edges[1][2] = g.edges[2][1] = 200;
    g.edges[1][4] = g.edges[4][1] = 450;
    g.edges[2][3] = g.edges[3][2] = 300;
    g.edges[2][5] = g.edges[5][2] = 400;
    g.edges[3][4] = g.edges[4][3] = 200;
    g.edges[5][4] = g.edges[4][5] = 250;
    DispAdjListGraph(*MatToList(g));
}

AdjMatrixGraph *CreateAdjMatrixGraph()
{
    int n, e;
    AdjMatrixGraph *G;
    G = (AdjMatrixGraph *)malloc(sizeof(AdjMatrixGraph));
    int i, j, k;
    int weight;
    printf("请分别输入顶点数和边数：");
    scanf("%d%d", &n, &e);
    G->n = n;
    G->e = e;
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
        {
            if(i == j)
                G->edges[i][j] = 0;
            else
                G->edges[i][j] = INF;
        }
    // 顶点信息输入
    for (i=0; i<n; i++)
    {
        printf("输入第%d个顶点的信息: ", i);
        scanf("%d", &(G->vertex[i].no));
    }
    // 边的信息输入
    for (k=0; k<e; k++)
    {
        printf("请输入边的两顶点序号: ");
        scanf("%d%d", &i, &j);
        printf("输入边的权重: ");
        scanf("%d", &weight);
        G->edges[i][j] = G->edges[j][i] = weight;
    }
    return G;
}

AdjListGraph *CreateAdjListGraph()
{
    int n, e;
    AdjListGraph *G;
    ArcType *pArc;
    int i, j, k;
    int weight;
    G = (AdjListGraph *)malloc(sizeof(AdjListGraph));
    printf("请分别输入顶点数和边数：");
    scanf("%d%d", &n, &e);
    G->n = n;
    G->e = e;
    // 顶点信息输入
    for(i=0; i<n; i++)
    {
        printf("输入第%d个顶点的信息: ", i);  // 录入顶点顺序表的信息
        scanf("%d", &(G->list[i].vertex.no)); 
        G->list[i].firstArc = NULL;  // 初始化边链表
    }
    // 边的信息输入
    for(k=0; k<e; k++)
    {
        printf("请输入边的两顶点的序号: ");
        scanf("%d%d", &i, &j);
        printf("请输入边的权重: ");
        scanf("%d", &weight);

        pArc = (ArcType *)malloc(sizeof(ArcType));
        pArc->next_vertex_no = j;  // 头插法建表
        pArc->weight = weight;
        pArc->nextArc = G->list[i].firstArc;
        G->list[i].firstArc = pArc;

        pArc = (ArcType *)malloc(sizeof(ArcType));
        pArc->next_vertex_no = i;  // 头插法建表
        pArc->weight = weight;
        pArc->nextArc = G->list[j].firstArc;
        G->list[j].firstArc = pArc;
    }
    return G;
}

void DispAdjMatrixGraph(AdjMatrixGraph G)
{
    int i, j;
    printf("邻接矩阵:\n");
    printf("\t");
    for (i=0; i<G.n; i++)
    {
        printf("%3d\t", G.vertex[i].no);
    }
    printf("\n");
    for (i=0; i<G.n; i++)
    {
        printf("%3d\t", G.vertex[i].no);
        for(j=0; j<G.n; j++)
        {
            printf("%3d\t", G.edges[i][j]);
        }
        printf("\n");
    }

}

void DispAdjListGraph(AdjListGraph G)
{
    int i;
    ArcType *pArc;
    printf("邻接表:\n");
    for (i=0; i<G.n; i++)
    {
        pArc = G.list[i].firstArc;
        printf("%d: ->", i);
        while (1)
        {
            if (pArc == NULL)
            {
                printf("^");
                break;
            }
            printf("%d(%d)->", pArc->next_vertex_no, pArc->weight);
            pArc = pArc->nextArc;
        }
        printf("\n");
    }
}

AdjListGraph *MatToList(AdjMatrixGraph g)
{
    int i, j;
    int n = g.n;
    AdjListGraph *G;
    ArcType *pArc;
    G = (AdjListGraph *)malloc(sizeof(AdjListGraph));
    G->n = g.n;
    G->e = g.e;
    for (i=0; i<n; i++)  // initialize
    {
        G->list[i].firstArc = NULL;
    }   
    for (i=0; i<n; i++) 
    {
        for (j=n-1; j>=0; j--)
        {
            if(g.edges[i][j] != 0 && g.edges[i][j] != INF)
            {
                pArc = (ArcType *)malloc(sizeof(ArcType));
                pArc->weight = g.edges[i][j];
                pArc->next_vertex_no = j;
                pArc->nextArc = G->list[i].firstArc;  // 头插法建表
                G->list[i].firstArc = pArc;
            }
        }
        G->list[i].vertex.no = g.vertex[i].no;
    }
    return G;
}

AdjMatrixGraph *ListToMat(AdjListGraph g)
{
    int i, j;
    int n = g.n;
    ArcType *pArc;
    AdjMatrixGraph *G;
    G = (AdjMatrixGraph *)malloc(sizeof(AdjMatrixGraph));
    G->n = g.n;
    G->e = g.e;
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
        {
            if (i == j)
                G->edges[i][j] = 0;
            else
                G->edges[i][j] = INF;
        }
    for (i=0; i<n; i++)  // scan the sequenceList
    {
        pArc = g.list[i].firstArc;
        G->vertex[i].no = g.list[i].vertex.no;
        while (pArc != NULL)
        {
            j = pArc->next_vertex_no;
            G->edges[i][j] = pArc->weight;
            pArc = pArc->nextArc;
        }
    }
    return G;
}

/**
 * Depth-first Search 
 * g: Adjacency list Graph 
 * v: the beginning vertex 
 **/
void DFS(AdjListGraph g, int v)
{
    static int k = 0;  // using to record the num of visited vertex.
    static int VISITED[MAXNUM];  // flag array initialized as 0 means not be visited
    printf("深度优先遍历：\n");
    DFS_recursion(g, v, VISITED, k);
    printf("\n");
}

void DFS_recursion(AdjListGraph g, int v, int VISITED[], int k)
{
    ArcType *pArc;
    printf("%3d ", g.list[v].vertex.no);
    VISITED[v] = 1;
    k++;
    pArc = g.list[v].firstArc;
    while (pArc != NULL)
    {
        v = pArc->next_vertex_no;
        if (VISITED[v] == 0)
            DFS_recursion(g, v, VISITED, k);
        if (k == g.n)
            return;
        pArc = pArc->nextArc;
    }
}

/** 
 * Breadth-first Search
 * g: Adjacency list Graph 
 * v: the beginning vertex
 **/
void BFS(AdjListGraph g, int v)
{
    ArcType *pArc;
    int w, i;
    int k = 0;
    int queue[MAXNUM];
    int front = 0, rear = 0;
    int visited[MAXNUM];
    for (i=0; i<g.n; i++)  // initialize
        visited[i] = 0;
    
    printf("广度优先遍历：\n");
    printf("%3d ", v);
    visited[v] = 1;
    k++;
    rear = (rear + 1) % MAXNUM;
    queue[rear] = v;  // the beginning vertex enQueue
    while (front != rear)
    {
        if (k == g.n)
            break;
        front = (front + 1) % MAXNUM;
        w = queue[front];  // deQueue
        pArc = g.list[w].firstArc;
        while(pArc != NULL)
        {
            if (visited[pArc->next_vertex_no] == 0)
            {
                printf("%3d ", pArc->next_vertex_no);
                visited[pArc->next_vertex_no] = 1;
                rear = (rear + 1) % MAXNUM;  
                queue[rear] = pArc->next_vertex_no;  // enQueue
            }
            pArc = pArc->nextArc;
        }
    }
    printf("\n");
}
