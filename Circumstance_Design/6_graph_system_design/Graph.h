#ifndef _GRAPH_H_
#define _GRAPH_H_
#define MAXNUM 10 
#define INF 32767

/********************  邻接矩阵  ********************/
/* 邻接矩阵的顶点类型 */
typedef struct vertex_type
{
    int no;  // 顶点标号
    // other info
}VType;

/* 邻接矩阵类型 */
typedef struct AdjMatrix
{
    int edges[MAXNUM][MAXNUM];  // 记录边的关系(甚至可以记录权重)
    VType vertex[MAXNUM];  // 记录各顶点信息
    int n, e;  // 记录图的顶点个数和边数
}AdjMatrixGraph;


/********************  邻接表  ********************/
/* 邻接表的边类型 */
typedef struct arc_type
{
    int next_vertex_no;  // 该边另一端的顶点的标号
    int weight;
    struct arc_type *nextArc;  // 指向下一条边的指针，构成链表
}ArcType;

/* 邻接表的顶点类型(作为结点存在) */
typedef struct vertex_node
{
    VType vertex;  // 记录顶点信息
    ArcType *firstArc;  // 指向该顶点的第一条边
}VNode;

/* 邻接表类型 */
typedef VNode AdjList[MAXNUM];  // 邻接表类型

/* 邻接表附加上其细节信息的类型 */
typedef struct adjList
{
    AdjList list;
    int n, e;
}AdjListGraph;


/********************  定义图的(邻接矩阵和邻接表存储方式)相关操作  ********************/
// 创建图
AdjListGraph *CreateAdjListGraph();  
AdjMatrixGraph *CreateAdjMatrixGraph();
// 打印图
void DispAdjMatrixGraph(AdjMatrixGraph G);
void DispAdjListGraph(AdjListGraph G);
// 两种存储方式之间的转换
AdjMatrixGraph *ListToMat(AdjListGraph g);
AdjListGraph *MatToList(AdjMatrixGraph g);
// 图的遍历算法
void DFS_recursion(AdjListGraph g, int v, int VISITED[], int k);
void DFS(AdjListGraph g, int v);
void BFS(AdjListGraph g, int v);

void test();
#endif
