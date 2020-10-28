#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int mg[M][N]={
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,1,0,0,0,1,0,1},
    {1,0,0,1,0,0,0,1,0,1},
    {1,0,0,0,0,1,1,0,0,1},
    {1,0,1,1,1,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,1},
    {1,0,1,1,1,0,1,1,0,1},
    {1,1,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};

int main(int argc, char const *argv[])
{
    Queue *q;
    queue_init(q);
    search_path(q, 1, 1, 8, 8);
    printf("通过队列实现的BFS算法求解迷宫\n解得一条路径为:\n");
    print_path(q);
    return 0;
}

/* 队列的初始化函数 */
void queue_init(Queue *&q)
{
    q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
}

/* 入队函数 */
void enQueue(Queue *&q, int x, int y)
{
    // 链队采用尾插法建立队列, 表尾即为队尾.
    Queue_Node *p;
    p = (Queue_Node *)malloc(sizeof(Queue_Node));
    p->x = x;
    p->y = y;
    p->pre = NULL;
    if(q->rear == NULL)  // 空队的情况
        q->front = q->rear = p;
    else{  // 一般情况
        q->rear->next = p;
        q->rear = p;
    }
}

/* 出队函数 */
int deQueue(Queue *&q, int &x, int &y)
{
    Queue_Node *p;
    if(q->rear == NULL)  // 空队列
        return 0;
    else{
        p = q->front;
        x = p->x;
        y = p->y;
        if(q->front == q->rear)  // 链队只剩一个结点
            q->front = q->rear = NULL;
        else{  // 一般情况
            q->front = p->next;
        }        
        free(p);
        return 1;
    }
}

/* 判断是否为空队的函数 */
int queue_is_empty(Queue *&q)
{
    return(q->rear == NULL);
}

/* BFS求解迷宫路径的函数 */
int search_path(Queue *&q,
         int xi, int yi, int xo, int yo)
{
    // 用队列实现BFS算法求解迷宫问题
    int x = 0, y = 0;
    // 首先将起点方块入队
    enQueue(q, xi, yi);
    mg[xi][yi] = -1;
    Queue_Node *ptr_block;
    ptr_block = q->front;  // 从队头开始不断往后遍历队列直至到队尾后结束
    // BFS
    while(ptr_block != NULL){
        x = ptr_block->x;
        y = ptr_block->y;
        if(mg[xo][yo] == -1)  // 如果已经到达过终点方块,那么直接return 1结束函数，同时队尾一定是终点方块
            return 1;
        // ptr_block除了作为循环的条件变量之外，它的意义在于指向当前方块，需要让它的相邻方块中仍为0的方块的pre指针指向p
        // 即借助p使得入队的相邻方块指向当前方块，以便在后续中输出路径

        // 下面4个if条件语句是顺序关系，从当前方块上面方块开始顺时针将相邻的4个方块中可走的方块进行入队操作，并且入队的方块pre指针指向当前方块
        if(mg[x-1][y] == 0){
            mg[x-1][y] = -1;
            enQueue(q, x-1, y);
            q->rear->pre = ptr_block;  // 下一方块入队后, 设置其pre指针指向当前方块
        }
        if(mg[x][y+1] == 0){
            mg[x][y+1] = -1;
            enQueue(q, x, y+1);
            q->rear->pre = ptr_block;
        }
        if(mg[x+1][y] == 0){
            mg[x+1][y] = -1;
            enQueue(q, x+1, y);
            q->rear->pre = ptr_block; 
        }
        if(mg[x][y-1] == 0){
            mg[x][y-1] = -1;
            enQueue(q, x, y-1);
            q->rear->pre = ptr_block; 
        }
        ptr_block = ptr_block->next;  // ptr_block指针指向链队中的下一个结点（下一个方块）
    }
    return 0;
}

/* 打印迷宫路径的函数 */
void print_path(Queue *&q)
{
    int cnt = 0;  // 用于输出计数换行 
    Queue_Node *p = q->rear;  // 由于search函数中在遍历只要找到终点就返回1, 所以终点必然就是队尾结点
    while(p != NULL){
        mg[p->x][p->y] = 2;  // 将路径上的方块标记为2,以便正向打印路径
        p = p->pre;
    }
    p = q->front;
    while(p != NULL){  // 从队首到队尾扫描各个元素,若方块被标记为2,则输出其坐标
        if(mg[p->x][p->y] == 2){
            if(cnt == 0){
                printf("    ");
            }else
                printf(" -> ");
            printf("(%d, %d)", p->x, p->y);
            cnt++;
            if(cnt % 5 == 0)
                printf("\n");
        }
        p = p->next;
    }
}
