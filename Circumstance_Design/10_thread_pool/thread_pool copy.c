#include <stdio.h>
#include <stdlib.h>
#include "thread_pool.h"

void insert_thread_list(thread_pool_t *tp, thread_t *thread)
{
    if(tp->thread_list_head == NULL)
        tp->thread_list_head = thread;
    else
    {
        thread->next = tp->thread_list_head;
        tp->thread_list_head = thread;
    }
}

thread_pool_t *pool_create(int threads_num)
{
    int i;
    thread_pool_t *tp = NULL;
    thread_t *ptr_thread;
    arg_t *argument;
    tp = (thread_pool_t *)malloc(sizeof(thread_pool_t));
    if (tp == NULL)
    {
        printf("Error: malloc for thread_pool_t\n");
        exit(-1);
    }
    // printf("********** thread_pool create and init **********\n");
    tp->alive = 1;

    tp->thread_list_head = NULL;
    tp->threads_num = threads_num;
    tp->busy_threads_num = 0;

    tp->task_queue_front = NULL;
    tp->task_queue_rear = NULL;
    tp->current_tasks_num = 0;

    pthread_mutex_init(&(tp->lock), NULL);
    pthread_mutex_init(&(tp->busy_count), NULL);
    pthread_cond_init(&(tp->queue_not_full), NULL);
    pthread_cond_init(&(tp->queue_not_empty), NULL);
    
    sem_init(&(tp->lamport_sem), 0, DISPATCH_NUM);

    for(i=0; i<threads_num; i++)
    {
        ptr_thread = (thread_t *)malloc(sizeof(thread_t));
        argument = (arg_t *)malloc(sizeof(arg_t));
        if (ptr_thread == NULL)
        {
            printf("Error: malloc for thread\n");
            exit(-1);
        }
        ptr_thread->priority = 0;
        ptr_thread->id = i;
        argument->tp = tp;
        argument->thread = ptr_thread;
        pthread_create(&(ptr_thread->thread), NULL, (void *)thread_lamport, (void *)argument);
        insert_thread_list(tp, ptr_thread);
    }
    sleep(1);
    return tp;
}   // done!


int pool_destroy(thread_pool_t *tp)
{
    int i;
    task_t *tmp_task = NULL;
    thread_t *tmp_thread = NULL;
    tmp_thread = tp->thread_list_head;
    pthread_mutex_lock(&(tp->lock));
    if(tp->alive == 0)
    {
        pthread_mutex_unlock(&(tp->lock));
        return -1;
    }
    tp->alive = 0;
    pthread_cond_broadcast(&(tp->queue_not_empty));
    pthread_mutex_unlock(&(tp->lock));
    while(tp->thread_list_head != NULL)
    {
        tmp_thread = tp->thread_list_head;
        pthread_join(tmp_thread->thread, NULL);
        tp->thread_list_head = tp->thread_list_head->next;
        free(tmp_thread);
    }
    pthread_mutex_lock(&(tp->lock));
    while(tp->task_queue_front != NULL)
    {
        tmp_task = tp->task_queue_front;
        tp->task_queue_front = tp->task_queue_front->next;
        free(tmp_task);
    }
    pthread_mutex_unlock(&(tp->lock));
    pthread_mutex_destroy(&(tp->lock));
    pthread_mutex_destroy(&(tp->busy_count));    
    pthread_cond_destroy(&(tp->queue_not_empty));
    pthread_cond_destroy(&(tp->queue_not_full));
    return 0;
}   // done!!


int add_task(thread_pool_t *tp, callback_func process, void *arg)
{
    task_t *task = NULL;
    task = (task_t *)malloc(sizeof(task_t));
    if (task == NULL)
    {
        printf("Error: add task\n");
        exit(-2);
    }
    pthread_mutex_lock(&(tp->lock));
    task->process = process;
    task->arg = arg;
    task->next = NULL;
    pthread_mutex_unlock(&(tp->lock));
    task_enqueue(tp, task);
    return 0;
}

void task_enqueue(thread_pool_t *tp, task_t *task)
{
    pthread_mutex_lock(&(tp->lock));
    // if full then wait
    if(tp->current_tasks_num == 0)
    {
        tp->task_queue_front = tp->task_queue_rear = task;
    }
    else
    {
        tp->task_queue_rear->next = task;
        tp->task_queue_rear = task;
    }
    (tp->current_tasks_num)++;
    // printf("A new task enqueue, current_task_num: %d\n", tp->current_tasks_num);
    pthread_cond_signal(&(tp->queue_not_empty));
    pthread_mutex_unlock(&(tp->lock));
}

/* To get a task */
task_t *get_task(thread_pool_t *tp)
{
    return task_dequeue(tp);
}

task_t *task_dequeue(thread_pool_t *tp)
{
    task_t *task = NULL;
    pthread_mutex_lock(&(tp->lock));
    // printf("current_task_num=%d\n", tp->current_tasks_num);
    while(tp->current_tasks_num == 0 && tp->alive)
    {
        // printf("thread 0x%lx is waiting for a task\n", pthread_self());
        printf("Thread (0x%lx)已挂起，等待投放任务\n", pthread_self());
        pthread_cond_wait(&(tp->queue_not_empty), &(tp->lock));
    }
    if (tp->alive == 0)
    {
        // printf("thread 0x%lx will be destroyed\n", pthread_self());
        pthread_mutex_unlock(&(tp->lock));
        pthread_exit(NULL);
    }
    task = tp->task_queue_front;
    tp->task_queue_front = tp->task_queue_front->next;
    (tp->current_tasks_num)--;
    // printf("thread 0x%lx received a task\n", pthread_self());
    pthread_mutex_unlock(&(tp->lock));
    return task;
}


static int choosing[MAX_THREADS_NUM] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static int number[MAX_THREADS_NUM] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static int get_max_from_number(int threads_num)
{
    int i;
    int max = 0;
    for (i=0; i<threads_num; i++)
        if (max < number[i])
            max = number[i];
    return max;
}

static void *thread_lamport(void *argument)   /* Threads get the task in queue to run */
{
    thread_pool_t *tp = NULL;
    task_t *task = NULL;
    int i, j;
    tp = ((arg_t *)argument)->tp;
    i = ((arg_t *)argument)->thread->id;
    int cnt = 0;
    while (1)
    {
        cnt ++;
        task = get_task(tp);
        if (task != NULL)
        {
            // printf("----------- Thread #%d (0x%lx)已获取任务 -----------\n", i, pthread_self());
            sem_wait(&(tp->lamport_sem));  // initialize to 3
            // 当前线程#i正在取号
            // printf("----- thread #%d is geting num -----\n", i);
            choosing[i] = 1;
            // number派号为上一个已发放的排队号加1
            number[i] = 1 + get_max_from_number(tp->threads_num);
            // 当前线程#i取号完毕
            choosing[i] = 0;
            // 迭代所有线程
            for (j = 0; j < tp->threads_num; j++)
            {
                // 若当前迭代到的 线程j 正在取号，则等待其取号完毕
                while(choosing[j] == 1);
                // 同时满足，当前线程才能顺利通过，访问临界区代码
                while (number[j] != 0 && (number[j]<number[i] || (number[j]==number[i] && j < i)));  // (number[j], j) < (number[i], i)
            }
            /* 临界区代码 */
            // pthread_mutex_lock(&(tp->busy_count));
            // (tp->busy_threads_num)++;
            // pthread_mutex_unlock(&(tp->busy_count));
            // printf("thread #%d (0x%lx) is busy(busy_num=%d) in working\n", i, pthread_self(), tp->busy_threads_num);
            number[i] = 0;
            printf("----------- Thread #%d (0x%lx)(第%d次调度该线程) -----------\n", i, pthread_self(), cnt);
            if(task->process != NULL)
                task->process(task->arg);
            sem_post(&tp->lamport_sem); 
            free(task);
            task = NULL;
            // pthread_mutex_lock(&(tp->busy_count));
            // (tp->busy_threads_num)--;
            // pthread_mutex_unlock(&(tp->busy_count));

            // 当前进程注销排队号
            // 一旦线程在临界区执行完毕，需要把自己的排队签到号码置为0，表示处于非临界区
            
        }
    }
}

// static void *assign(void *arg)   /* Threads get the task in queue to run */
// {
//     thread_pool_t *tp = (thread_pool_t *)arg;
//     while (1)
//     {
//         task_t *task = NULL;
//         task = get_task(tp);  // dequeue 之前使用lamport算法来调度线程
//         pthread_mutex_lock(&(tp->busy_count));
//         (tp->busy_threads_num)++;
//         pthread_mutex_unlock(&(tp->busy_count));
//         if (task != NULL)
//         {
//             printf("thread 0x%lx is busy in working\n", pthread_self());
//             if(task->process != NULL)
//                 task->process(task->arg);
//             free(task);
//             task = NULL;
//         }
//     }
// }
