#include <stdio.h>
#include <stdlib.h>
#include "sqList.h"

int main(int argc, char const *argv[])
{
    long_int num1, num2, answer;
    init(num1);
    init(num2);
    init(answer);
    input_long_int(num1);
    input_long_int(num2);
    // insert_element_head(num, 2222);
    add(num1, num2, answer);
    display(answer);
    return 0;
}

void init(long_int &num)
{
    int i;
    for (i=0; i<maxN; i++){
        num.data[i] = 0;
        num.length = 0;
        num.sign = 0;
    }
}

int find_last(long_int num)
{
    return num.length;
}

void insert_element_rear(long_int &num, int data)
{
    num.data[num.length] = data;   // 0 ~ length-1 表头到尾指针处 存储的是 长整数高到低位数据, 即运算时顺序要倒过来
    num.length += 1;
    
}

void insert_element_head(long_int &num, int data)
{
    if(num.length < maxN-1){  // 确保再拓长高4位后未溢出
        // 原先各元素后移,空出一个元素的位置
        int i, temp;
        num.length += 1;
        if(data<0)
            num.sign = -1;
        else
            num.sign = 1;
        for (i=num.length-1; i>=0; i--)
            num.data[i+1] = num.data[i];
        num.data[0] = data;
    }
}

void input_long_int(long_int &num)
{
    int data;
    char ch = ',';
    printf("Enter a long integer: ");
    while(ch == ','){  // 当输入完最后4位之后回车停止循环
        scanf("%d%c", &data, &ch);
        insert_element_rear(num, data);
    }
}

void display(long_int num)
{
    for (int i=0; i<num.length; i++){
        if (i!=0)
            printf(",");
        printf("%d", num.data[i]);
    }
    printf("\n");
}

int judge_sign(long_int &num)
{
    if(num.data[0] < 0)
        num.sign = -1;
    else
        num.sign = 1;
    return num.sign;
}

void add(long_int num1, long_int num2, long_int &answer)
{
    if(judge_sign(num1) == judge_sign(num2)){  // 同号相加
        int index1, index2;
        int data;
        int flag = 0;  // 进位标志
        index1 = num1.length-1;
        index2 = num2.length-1;
        while(index1 != -1 && index2 != -1){  
            if(num1.data[index1] < 0 && index2!=0)  // 不等长,短的负数的最高4位需要转为正的参与下面运算
                num1.data[index1] = -(num1.data[index1]);
            if(num2.data[index2] < 0 && index1!=0)
                num2.data[index1] = -(num2.data[index1]);
            if(num1.data[index1] < 0 && num2.data[index2] < 0 && flag == 1)  // 等长最高4位都为负数时候的进位为-1
                flag = -1;
            data = num1.data[index1] + num2.data[index2] + flag;
            flag = forward(flag, &data);
            insert_element_head(answer, data);
            index1--;
            index2--;
        }
        while(index1 != -1){
            if(num1.sign < 0)
                flag = -1;
            data = num1.data[index1] + flag;
            flag = forward(flag, &data);
            insert_element_head(answer, data);
            index1--;
        }
        while(index2 != -1){
            if(num2.sign < 0)
                flag = -1;
            data = num2.data[index2] + flag;
            flag = forward(flag, &data);
            insert_element_head(answer, data);
            index2--;
        }
    }else{  // 异号相加， 转化为同号减法
        if (num1.sign < 0 && num2.sign > 0){
            swap(num1, num2);
            num2.sign = 1;
            num2.data[0] = -(num2.data[0]);
        }else if(num1.sign > 0 && num2.sign < 0){
            num2.sign = 1;
            num2.data[0] = -(num2.data[0]);
        }
        sub(num1, num2, answer);
    }
}

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

void sub(long_int num1, long_int num2, long_int &answer)
{
    if(judge_sign(num1) == judge_sign(num2)){  // 同号减法

    }else{  // 异号减法 转化为同号加法
        
    }
}

int abs_compare(long_int num1, long_int num2)
{

}

void swap(long_int &num1, long_int &num2)
{

}

int abs_sub(long_int num1, long_int num2, long_int &answer)
{

}

void choice(long_int num1, long_int num2)
{


}