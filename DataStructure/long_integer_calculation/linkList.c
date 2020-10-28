/* --- 使用双向链表实现长整数的输入输出及加法减法计算 --- */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linkList.h"

int main(int argc, char const *argv[])
{
    Head *num1, *num2;
    num1 = create_and_init();
    num2 = create_and_init();
    printf("Input num_1 (four as a set seperated by a ','): ");
    input(num1);
    printf("Input num_2 (four as a set seperated by a ','): ");
    input(num2);
    choice(num1, num2);
    return 0;
}

/* 功能选择函数，选择做加减运算或退出取消本次运算 */
void choice(Head *num1, Head *num2)  
{
    Head *answer;
    answer = create_and_init();
    char choice = ' ';
    printf("Select a function (Enter '+' or '-'): ");
    scanf("%c", &choice);  // 输入一个字符用于选择功能
    if(choice == '+'){   // 相加并输出结果
        answer = add(num1, num2);
        display(answer);
    }
    else if(choice == '-'){  // 相减并输出结果
        answer = sub(num1, num2);
        display(answer);
    }
    else if(choice == 'q'){  // 退出
        printf("Quit!\n");
    }
    else  // 其他输入都判定为错误的输入，并打印错误信息。
        printf("Error\n");
}

/* 创建并初始化链表 */
Head *create_and_init()
{
    Head *num;
    num = (Head *)malloc(sizeof(Head));
    num->next = NULL;
    num->last_node = NULL;
    num->sign = 0;
    num->node_num =  0;
    return num;
}

/* 在链表尾部插入新的结点(尾插法) */
void Insert_node_rear(Head *num, int data)  // 输入两个长整数时候使用尾插法建表， 高位在前 低位在后。
{
    Node *p;
    p = (Node *)malloc(sizeof(Node));
    p->data = data;
    p->next = NULL;       // 尾插法建表
    num->node_num++;
    if(num->next == NULL || num->last_node == NULL){  // 空表的情况, 说明插入的是最高4位数
        num->next = p;
        num->last_node = p;
        p->prior = NULL;  // 是表头,因此没有前驱结点.
    }
    else{                                             // 不是空表的一般情况
        p->prior = num->last_node;
        num->last_node->next = p;
        num->last_node = p;
    }
}

/* 在链表头部插入新的结点(头插法) */
void Insert_node_head(Head *num, int data)
{
    Node *p;
    p = (Node *)malloc(sizeof(Node));
    p->data = data;
    p->prior = NULL;  // 头插法建表
    num->node_num++;
    if(num->next == NULL || num->last_node == NULL){  // 空表的情况，插入的是最低4位数
        num->next = p;
        num->last_node = p;
        p->next = NULL;  // 是表尾,因此没有后继结点.
    }
    else{                                             // 不是空表的一般情况
        num->next->prior = p;
        p->next = num->next;
        num->next = p;
    }
}

/* 从表头到表尾依次输出链表各节点内容 */
int display(Head *num)
{
    Node *p;
    int data;
    int n1, n2, n3, n4;
    if(num->next==NULL)
        return -1;
    p = num->next;
    printf("The answer is: ");
    while(p != NULL){
        if(p != num->next){  // 不是表头同时还有后续结点时打印 ","
            printf(",");
        }
        data = p->data;
        if(data < 0 || data == 0 && num->sign==-1 && p->prior==NULL){  // 对负数情况的处理
            printf("-");
            data = -data;
        }
        n1 = data / 1000;
        n2 = (data % 1000) / 100;
        n3 = (data % 100) / 10;
        n4 = (data % 10);
        printf("%d%d%d%d", n1, n2, n3, n4);
        p = p->next;
    }
    printf("\n");
    return 0;
}

/* 输入函数：用于接收一个长整数，并建立一个相应的链表 */
void input(Head *num){
    int data;
    char c = ',';
    while(c == ','){
        scanf("%d%c", &data, &c);
        if(data>= -9999 && data <= 9999)
            Insert_node_rear(num, data);
        else{
            Insert_node_rear(num, 0);
            printf("Input Error\n, viewed as 0000\n");
        }
    }
}

/* 判断长整数符号的函数 */
int judge_sign(Head *num)
{
    if(num->next == NULL)
        return 0;  // 为空时返回0
    if(num->next->data >= 0)
        num->sign = 1;
    else
        num->sign = -1;
    return num->sign;
}

/* 加法函数 */
Head *add(Head *num1, Head *num2)  // num1 + num2
{
    Head *answer;
    answer = create_and_init();  // 由于从后往前(低位到高位)计算, 因此需要使用头插法建表， 这样子同时解决了借位和进位的问题
    Node *p1, *p2;
    int data = 0;  // 新插入结点的数据域内容
    int flag = 0;  // 进位标志, 初值为0 表示无进位, 1表示进位
    p1 = num1->last_node;
    p2 = num2->last_node;
    if(judge_sign(num1) == judge_sign(num2)){  // 同号相加, 从最低4位开始向最高4位遍历直接相加，考虑到进位即可
        while (p1 != NULL && p2 != NULL){
            if(p1->data < 0 && p2->prior!=NULL)  // 不等长,短的负数的最高4位需要转为正的参与下面运算
                p1->data = -(p1->data);
            if(p2->data < 0 && p1->prior!=NULL)
                p2->data = -(p2->data);
            if(p1->data < 0 && p2->data < 0 && flag == 1)  // 等长的两个负数最高位相加的进位是-1
                flag = -1;
            data = p1->data + p2->data + flag;
            flag = forward(flag, &data);
            Insert_node_head(answer, data);
            p1 = p1->prior;
            p2 = p2->prior;
        }
        // 不等长的情况，头插法插入剩余高位的结点
        while (p2){
            if(p2->data < 0)
                flag = -1;
            data = p2->data + flag;
            flag = forward(flag, &data);
            Insert_node_head(answer, data);
            p2 = p2->prior;
        }
        while (p1){
            if(p1->data < 0)
                flag = -1;
            data = p1->data + flag;
            flag = forward(flag, &data);
            Insert_node_head(answer, data);
            p1 = p1->prior;
        }     
        if( flag == 1 || flag == -1){ // 最高位存在进位, 需要头插法插入新的结点
            Insert_node_head(answer, flag);
        }
    }else{  // 异号相加, 转化为同号减法的减法 ,  具体细节问题详见sub函数的同号减法部分
        if(num1->sign == -1 && num2->sign == 1){        // 数1(-) + 数2(+)  -> 数2(+) - 数1(abs(+))
            swap(num1, num2);
            num1->sign = 1;
            num1->next->data = -(num1->next->data);
        }else if(num1->sign == 1 && num2->sign == -1){  // 数1(+) + 数2(-)  -> 数1(+) - 数2(abs(+))
            num2->sign =1;
            num2->next->data = -(num2->next->data);
        }
        answer = sub(num1, num2);
    }
    return answer;
}

/* 加法中用到的判断进位函数 */
int forward(int flag, int *data)  // 同号相加时的进位函数
{  
    // 返回值返回flag，同时通过地址传参改变data的值
    if(*data > 9999){
        *data -= 10000;
        flag = 1;
    }else if(*data < -9999){
        *data += 10000;
        flag = -1;
    }else 
        flag = 0;
    return flag;
}

/* 绝对值比较函数 */
int abs_compare(Head  *num1, Head *num2)
{
    // 返回值: |num1|大 -> 1, |num2|大 -> 2, 相等 -> 0
    int flag = 0;
    Node *p1, *p2;
    p1 = num1->next;
    p2 = num2->next;
    if(num1->node_num > num2->node_num)       // num1 比 num2 长
        flag = 1;
    else if(num1->node_num < num2->node_num)  // num1 比 num2短
        flag = 2;
    else{                                     // num1, num2 等长
        if(abs(p1->data) > abs(p2->data))          // num1最高4位数大 
            flag = 1;
        else if(abs(p1->data) < abs(p2->data))     // num2最高4位数大
            flag = 2;
        else{                                      // 最高4位相等时, 往表尾继续遍历比较 
            while(p1!=NULL && p2!=NULL){
                if(p1->data > p2->data){
                    flag = 1;
                    break;
                }else if(p1->data < p2->data){
                    flag = 2;
                    break;
                }
                p1 = p1->next;
                p2 = p2->next;
            }
        }
    }
    return flag;
}

/* 两个长整数的交换函数 */
void swap(Head  *num1, Head *num2)
{
    Head *temp;
    temp = create_and_init();
    temp->sign = num1->sign;
    temp->node_num = num1->node_num;
    temp->next = num1->next;
    temp->last_node = num1->last_node;

    num1->sign = num2->sign;
    num1->node_num = num2->node_num;
    num1->next = num2->next;
    num1->last_node = num2->last_node;

    num2->sign = temp->sign;
    num2->node_num = temp->node_num;
    num2->next = temp->next;
    num2->last_node = temp->last_node;
}

/* 减法函数 */
Head *sub(Head *num1, Head *num2)
{
    Head *answer;
    answer=create_and_init();
    if (judge_sign(num1) != judge_sign(num2)){      // 异号减法,转化为两个正数或两个负数的加法
        if(num1->sign == 1 && num2->sign == -1){
            num2->sign=1;
            num2->next->data = -(num2->next->data);
            answer = add(num1, num2);
        }
        else if(num1->sign == -1 && num2->sign == 1){
            num2->sign=-1;
            num2->next->data = -(num2->next->data); 
            answer = add(num1, num2);
        }
    }else{                                          // 同号减法,需要考虑的细节有: 不等长, 借位, 符号等. 可以引入绝对值做减法解决这个问题
        int abs_compare_flag;
        abs_compare_flag = abs_compare(num1, num2);
        if(abs_compare_flag == 1 || abs_compare_flag == 0){
            answer = abs_sub(num1, num2);  
            //  一种情况为 大正数 - 小正数 = 正数
            //  此时不需要处理符号问题    
            if(num1->sign < 0){            //  另一种情况为 小负数 - 大负数  = 负数
                answer->sign = -1;         //  此时需要处理符号问题
                answer->next->data = -(answer->next->data);
            }
        }else if(abs_compare_flag == 2){
            swap(num1, num2);  // 交换二者次序, 使得满足abs_sub()的要求
            answer = abs_sub(num1, num2);
            //  一种情况为 大负数 - 小负数 = 正数
            //  此时不需要处理符号问题   
            if(num1->sign > 0){            //  另一种情况为 小正数 - 大正数  = 负数
                answer->sign = -1;         //  此时需要处理符号问题
                answer->next->data = -(answer->next->data);
            } 
        }  
    }
    return answer;  
}

/* 绝对值减法函数，表达式见函数内注释 */
Head *abs_sub(Head *num1, Head *num2)  // 将两负数减法 通过绝对值转化为 两正数减法来完成sub函数的同号减法部分
{
    // answer = | |num1| - |num2| |
    // 默认前提条件是: |num1| >= |num2|   ->  需要比较长整数绝对值的大小并调用swap函数来保证满足这个前提条件
    Head *answer;
    answer = create_and_init();
    Node *p1, *p2;
    int data, d1, d2;
    int flag =  0;  // 借位标志
    // 先对num1 num2取绝对值
    num1->sign=1;
    num2->sign=1;
    num1->next->data = num1->next->data>=0? num1->next->data: -(num1->next->data);
    num2->next->data = num2->next->data>=0? num2->next->data: -(num2->next->data);
    // 下面是计算过程
    p1 = num1->last_node;
    p2 = num2->last_node;
    while(p1!=NULL && p2!=NULL){
        d1 = p1->data;
        d2 = p2->data;
        data = d1 - d2 - flag;
        if(data < 0){  // 需要向高位借位
            data += 10000;
            flag = 1;
        }else{
            flag = 0;
        }
        Insert_node_head(answer, data);        
        p1 = p1->prior;
        p2 = p2->prior;
    }
    // 不等长时, 继续建立剩余的结点
    while(p1!=NULL){
        data = p1->data;
        data -= flag;
        if(data < 0){
            data += 10000;
            flag = 1;
        }else{
            flag = 0;
        }
        Insert_node_head(answer, data);
        p1 = p1->prior;
    }
    answer->sign = 1;
    return answer;
}