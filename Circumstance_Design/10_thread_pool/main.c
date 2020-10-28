#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "thread_pool.h"
#include "thread_pool.c"

/* store the callback function */
void *task_function(void *arg)
{
    printf("\t调度算法：lamport面包店算法\n\t输出学号：27180428\n");
    // sleep(1);
    printf("\t该任务即将在3s后完成(延时)\n");
    // sleep(1);
    usleep(50000);
}

int main(int argc, char const *argv[])
{   
    thread_pool_t *tp;
    int i = 0;
    tp = pool_create(10);
    sleep(1);
    while (i < 36)
    {
        add_task(tp, task_function, (void *)NULL);
        usleep(100000);
        // sleep(1);
        i++;
    }
    sleep(10);
    return 0;
}

