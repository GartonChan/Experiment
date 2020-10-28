#include "../Graph.h"

typedef struct stack{
    int no;
    struct stack * next;
}stack_t;

int locateVertex(AdjListGraph G,int u);

AdjListGraph *CreateAOE();

stack_t *initializeStack();

int stack_is_empty(stack_t s);

void push(stack_t *s, int vertex_no);

int pop(stack_t *s);

/* 统计各个顶点的入度, 记录在indegree数组 */
void findInDegree(AdjListGraph G, int indegree[]);

/* 拓扑排序,无回路就返回1,有回路返回0 */
int TopologicalOrder(AdjListGraph G);

void CriticalPath(AdjListGraph G);