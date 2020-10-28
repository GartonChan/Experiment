#include <stdio.h>
#include <stdlib.h>
#include "../Graph.h"
#include "AOE.h"

#define MAX_VERTEX_NUM 20
// 保存边的最早开始时间
int ve[MAX_VERTEX_NUM];
// 保存边的最晚开始时间
int vl[MAX_VERTEX_NUM];

static stack_t *stack;

int locateVertex(AdjListGraph G,int u)
{
    for (int i=0; i<G.n; i++) {
        if (G.list[i].vertex.no == u) {
            return i;
        }
    }
    return -1;
}

AdjListGraph *CreateAOE()
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
    for(i=0; i<n; i++)
    {
        printf("输入第%d个顶点的信息: ", i);  // 录入顶点顺序表的信息
        scanf("%d", &G->list[i].vertex.no);
        G->list[i].firstArc =NULL;
    }
    for (k=0; k<e; k++)
    {
        printf("请分别输入起点与终点的序号: ");
        scanf("%d%d", &i, &j);
        printf("请输入权重: ");
        scanf("%d", &weight);
        ArcType *pArc = (ArcType *)malloc(sizeof(ArcType));
        pArc->next_vertex_no = j;
        pArc->weight = weight;
        pArc->nextArc = G->list[i].firstArc;
        G->list[i].firstArc = pArc;
    }
    return G;
}

stack_t *initializeStack()
{
    stack_t *s = (stack_t *)malloc(sizeof(stack_t));
    s->next = NULL;
    return s;
}

int stack_is_empty(stack_t s)
{
    if(s.next == NULL)
        return 1;
    else
        return 0;
}

void push(stack_t *s, int vertex_no)
{
    stack_t *p = (stack_t *)malloc(sizeof(stack_t));
    p->no = vertex_no;
    p->next = NULL;
    p->next = s->next;
    s->next = p;
}

int pop(stack_t *s)
{
    int no;
    stack_t *p = s->next;
    no = p->no;
    s->next = s->next->next;
    return no;
}

/* 统计各个顶点的入度, 记录在indegree数组 */
void findInDegree(AdjListGraph G, int indegree[])
{
    int i;
    for(i=0; i<G.n; i++)
    {
        indegree[i] = 0;
    }
    for (i=0; i<G.n; i++)
    {
        ArcType *pArc = G.list[i].firstArc;
        while(pArc)
        {
            indegree[pArc->next_vertex_no]++;
            pArc = pArc->nextArc;
        }
    }
}

/* 拓扑排序,无回路就返回1,有回路返回0 */
int TopologicalOrder(AdjListGraph G)
{
    int i;
    int indegree[G.n];
    findInDegree(G, indegree);
    stack_t *s;
    s = initializeStack();
    for (i=0; i<G.n; i++)
    {
        if(indegree[i] == 0)
            push(s, i);
    }
    int cnt;
    int no;
    ArcType *pArc = (ArcType *)malloc(sizeof(ArcType));
    while(!stack_is_empty(*s))
    {
        no = pop(s);
        push(stack, no);
        cnt++; //记录个数
        pArc = G.list[no].firstArc;
        while(pArc != NULL)
        {
            int k = pArc->next_vertex_no;
            if((--indegree[k]) == 0)
                push(s, k);
            if(ve[no] + pArc->weight > ve[k])
                ve[k] = ve[no] + pArc->weight;
            pArc = pArc->nextArc;
        }
    }
    if (cnt < G.n)
    {
        printf("有回路\n");
        return 0;
    }
    return 1;
}

void CriticalPath(AdjListGraph G)
{
    if(TopologicalOrder(G) == 0)
        return ;
    int i, j, k;
    ArcType *pArc;
    for (i=0; i<G.n; i++)
        vl[i] = ve[G.n-1];
    while (!stack_is_empty(*stack))
    {
        j = pop(stack);
        pArc = G.list[j].firstArc;
        while(pArc != NULL)
        {
            k = pArc->next_vertex_no;
            if (vl[k] - pArc->weight < vl[j])
                vl[j] = vl[k] - pArc->weight;
            pArc = pArc->nextArc;
        }
    }
    for(j=0; j<G.n; j++)
    {
        pArc = G.list[j].firstArc;
        printf("*表示关键活动\n");
        while(pArc != NULL)
        {
            k = pArc->next_vertex_no;
            int ee = ve[j];
            int el = vl[k] - pArc->weight;
            char tag = (ee == el)?'*':' ';
            printf("%3d%3d%3d%3d%3d%2c\n",j, k, pArc->weight, ee, el, tag);
            pArc = pArc->nextArc;
        }
    }
}

int main(){
    AdjListGraph *G;
    G = CreateAOE();//创建AOE网
    stack = initializeStack();
    TopologicalOrder(*G);
    CriticalPath(*G);
    return  0;
}