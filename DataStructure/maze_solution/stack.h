/* --- 栈的深度优先算法进行迷宫求解 --- */

/*
    假定迷宫由诸多方块组成规则的矩形，
    迷宫(mg)可由 M × N 的矩阵进行表示，
    其中，用1表示墙方块， 0表示通道方块, -1表示已经走过的方块
*/

// 这里与课堂示例一样，以同样的 10 × 10的迷宫为例
// 假定左上角为迷宫入口， 右下角为迷宫出口
#define M 10
#define N 10

typedef struct stack_node
{
    int x;
    int y;  // x,y记录方块坐标
    struct stack_node *next;
}Stack;
// 用链表实现栈

void stack_init(Stack *&s);
int stack_is_empty(Stack *s);
void push(Stack *&s, int x, int y);
int pop(Stack *&s);
int get_the_top(Stack *s, int &x, int &y);
void display(Stack *s);
void search_path(Stack *&s, int xi, int yi, int xo, int yo);
void print_path(Stack *s);