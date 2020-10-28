#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "thread_pool.h"
#include "thread_pool.c"

/* store the callback function */
void *test_task_1(void *arg)
{
    usleep(300000);
    printf("\tfinished task_1 (arg=%d)\n", *(int *)arg);
    return NULL;
}

void *test_task_2(void *arg)
{
    usleep(300000);
    printf("\tfinished task_2 (arg=%d)\n", *(int *)arg);
    return NULL;
}
// print the same value of arg, because the address of i is the same one.

int main(int argc, char const *argv[])
{
    thread_pool_t *tp;
    int i = 0;
    tp = pool_create(10);
    while (i < 25)
    {
        add_task(tp, test_task_1, (void *)&i);
        add_task(tp, test_task_2, (void *)&i);
        usleep(10000);
        i++;
    }
    sleep(10);
    // pool_destroy(tp);
    return 0;
}

/* use the thread pool to finish the work(from callback function) */
// int main(int argc, char const *argv[])
// {
//     thread_pool_t *tp;
//     int i = 0;
//     tp = pool_create(6);
//     sleep(1);
//     while (i < 5)
//     {
//         add_task(tp, task_1, (void *)&i);
//         // sleep(1);
//         add_task(tp, task_2, (void *)&i);   // 对 add_task的顺序做封装(通过lamport算法实现)
//         sleep(1);
//         i++;
//     }
//     sleep(5);
//     pool_destroy(tp);
//     return 0;
// }

