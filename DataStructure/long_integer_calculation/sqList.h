#define maxN 25  // 最多结点数(最多100位, 4位作为一个结点  -> 25)
typedef struct sqlist 
{
    int data[maxN];
    int length;  // 记录最低位的指针
    int sign;  // 符号标志
}long_int;

void init(long_int &num);
void insert_element_head(long_int &num, int data);
void insert_element_rear(long_int &num, int data);
void input_long_int(long_int &num);
void display(long_int num);
int judge_sign(long_int &num);
void add(long_int num1, long_int num2, long_int &answer);
int forward(int flag, int *data);
void sub(long_int num1, long_int num2, long_int &answer);
int abs_compare(long_int num1, long_int num2);
void swap(long_int &num1, long_int &num2);
int abs_sub(long_int num1, long_int num2, long_int &answer);
void choice(long_int num1, long_int num2);
