/* --- 使用双向链表实现长整数的输入输出及加法减法计算 --- */

typedef struct node    // 链表中的结点
{
    int data;               // 数据域
    struct node *prior;     // 
    struct node *next;
}Node;

typedef struct head    // 链表头结点
{
    int sign;               // -1表示负数, 1表示正数
    struct node *next;      // 指向下一个结点
    struct node *last_node; // 尾结点指针, 避免对尾结点多次的遍历查找
    int node_num;           // 结点个数
}Head;

void choice(Head *num1, Head *num2);
Head *create_and_init();
// H_set *initial(H_set *num);
void Insert_node_rear(Head *num, int data);  // 尾插法 插入一个4位数结点
void Insert_node_head(Head *num, int data);  // 头插法 插入一个4位数结点
int display(Head *num);                      // 打印出num指向的长整数
void input(Head *num);                       // 封装的输入函数, 输入一个长整数到num指向的链表中
int judge_sign(Head *num);                   // 根据num设置num->sign, 并且返回num->sign
void swap(Head  *num1, Head *num2);          // num1, num2指向的链表包括相关信息进行交换
Head *add(Head *num1, Head *num2);           // 加法
int forward(int flag, int *data);
Head *sub(Head *num1, Head *num2);           // 减法
Head *abs_sub(Head *num1, Head *num2);       // 绝对值减法:  answer = | |num1| - |num2| |
int abs_compare(Head  *num1, Head *num2);    // 比较两数的绝对值大小
