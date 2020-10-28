#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

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
    Stack *s;
    int x, y;
    stack_init(s);
    search_path(s, 1, 1, 8, 8);
    print_path(s);
    return 0;
}

/* 栈的初始化函数 */
void stack_init(Stack *&s)
{
    // 开辟内存空间并初始化栈
    s = (Stack *)malloc(sizeof(Stack));
    s->x = 0;
    s->y = 0;
    s->next = NULL;
}

/* 判断栈是否为空的函数 */
int stack_is_empty(Stack *s)
{
    return (s->next==NULL);
}

/* 进栈函数(头插法,表头是栈顶,表尾是栈底) */
void push(Stack *&s, int x, int y)
{
    Stack *p;
    p = (Stack *)malloc(sizeof(Stack));
    p->x = x;
    p->y = y;
    p->next = s->next;  // 头插法，使得栈顶永远在起始结点
    s->next = p;  // s是指向链表的指针，它与栈顶建立关联。
}

/* 出栈函数(栈顶元素位于表头) */
int pop(Stack *&s)
{
    if(s->next == NULL)  // 栈为空
        return 0;
    Stack *p;
    p = s->next;
    s->next = p->next;
    free(p);
    return 1;
}

/* 获得栈顶元素的函数 */
int get_the_top(Stack *s, int &x, int &y)
{
    if(s->next == NULL)
        return 0;
    x = s->next->x;
    y = s->next->y;
    return 1;
}

/* 从栈顶到栈底依次输出各结点元素信息 */
void display(Stack *s)
{
    Stack *p;
    int x, y;
    int cnt = 0;  // 用于输出计数换行
    p = s->next;
    while(p != NULL){
        x = p->x;
        y = p->y;
        if(cnt == 0)
            printf("    ");
        else
            printf(" -> ");
        printf("(%d, %d)", x, y);
        cnt++;
        if(cnt % 5 == 0)
            printf("\n");
        p = p->next;
    }
}

/* DFS求解迷宫路径的函数 */
void search_path(Stack *&s,
        int xi, int yi, int xo, int yo)  
{
    // 用栈实现DFS算法求解迷宫问题
    // 首先将入口进栈
    push(s, xi, yi);
    mg[xi][yi] = -1;
    int x, y;
    while(!stack_is_empty(s)){ 
        if(mg[xo][yo] == -1){  // 如果已经到达出口方块则跳出循环
            break;
        }
        get_the_top(s, x, y);  // 取得栈顶元素(并不出栈),作为当前方块
        /*
            下面选取可走的方块入栈标记为已走过,并继续循环处理
            如果当前方块的四面都走不通,则将当前方块出栈,
            下次循环重新获取栈顶元素以回退到前一方块.
        */
        if(mg[x-1][y] == 0){        // 首先考虑当前方块上面的方块
            mg[x-1][y] = -1;  // 若为未走过的通道,则将该方块入栈,并赋值-1表示走过这个方块
            push(s, x-1, y);  
            continue;  // 该方块入栈后,进入下一次循环, 将其作为当前方块继续进行处理 
        // 下面的三个条件判断同理
        }else if(mg[x][y+1] == 0){  // 再考虑当前方块右面的方块
            mg[x][y+1] = -1;
            push(s, x, y+1);
            continue;
        }else if(mg[x+1][y] == 0){  // 然后考虑当前方块下面的方块
            mg[x+1][y] = -1;
            push(s, x+1, y);
            continue;
        }else if(mg[x][y-1] == 0){  // 最后考虑当前方块左面的方块
            mg[x][y-1] = -1;
            push(s, x, y-1);
            continue;
        }else                       // 当前方块四面都走不通,出栈回退到前一方块.
            pop(s);
    }
}

// 想要输出正向路径也就是从栈底到栈顶的打印, 可以通过构造另一个栈来实现逆向打印
/* 打印迷宫路径的函数 */
void print_path(Stack *s)  // 从起点到终点正向输出路径信息
{
    Stack *s_reverse;
    int x, y;
    int cnt;  // 用于输出计数换行 
    stack_init(s_reverse);
    while(!stack_is_empty(s)){  // 栈不为空
        get_the_top(s, x, y);
        pop(s);
        push(s_reverse, x, y);
    }
    printf("通过栈实现的DFS算法求解迷宫\n解得一条路径为:\n");
    display(s_reverse);
    printf("\n");
}

/*
    指针引发的bug:
        一下忽略了通过指针传参给函数时, 修改指针指向的内容会被同步修改(地址传递),
        然而修改指针自身的值或者说修改指针指向(指针也是一个变量)(值传递)是无法与外部同步的,
        此时,要么使用c++的引用,要么使用指针的指针(可能比较笨拙),
        或者考虑能否通过返回指针类型的函数来解决

        所以课程中使用引用传参的原因由此可见.
*/