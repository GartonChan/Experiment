#define M 10
#define N 10

typedef struct queue_node
{
    int x;
    int y;
    struct queue_node *next;  // 指向队列的下一结点
    struct queue_node *pre;  // 指向前一方块
}Queue_Node;

typedef struct queue
{
    Queue_Node *front;  // 指向队列的队首结点
    Queue_Node *rear;  // 指向队列的队尾结点
}Queue;


void queue_init(Queue *&q);
void enQueue(Queue *&q, int x, int y);
int deQueue(Queue *&q, int&x, int &y);
int queue_is_empty(Queue *&q);
int search_path(Queue *&q,
         int xi, int yi, int xo, int yo);  // BFS
void print_path(Queue *&q);
