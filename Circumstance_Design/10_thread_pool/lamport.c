#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define THREADS_NUM 10
int choosing[THREADS_NUM];
int number[THREADS_NUM];
int init()
{
    int i;
    for (i=0; i<THREADS_NUM; i++)
    {
        choosing[i] = false;
        number[i] = 0;
    }
    return 0;
}

int get_max()
{
    int max=0, i;
    for (i=0; i<THREADS_NUM; i++)
    {
        if (number[i] > max)
            max = number[i];
    }
    return max;
}

int main(int argc, char const *argv[])
{
    init();
    int i = 3;  // Process (i)  / Thread (i)
    int j;   // i为当前线程id, j为迭代的线程id

    while(true)
    {
        choosing[i] = true;  // 正在取号
        number[i] = 1 + get_max();  // 为上次已发放的排队号+1
        choosing[i] = false;  // 取号完毕

        for (j=0; j<THREADS_NUM; j++)
        {
            while(choosing[j]);  // j正在取号 则等待其取号完毕
            while(number[j] !=0 && number[j] < number[i] );  // (a, c) < (b, d)

        }
        // critical section
        // 当前进程注销排队号
        // 一旦线程在临界区执行完毕，需要将自己排队签到号码设置为0，表示处于非临界区
        number[i] = 0;
        // 其他代码
    }
    return 0;
}
