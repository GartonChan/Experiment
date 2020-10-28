#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <pthread.h>
#include <semaphore.h>

#define DISPATCH_NUM 3
#define MAX_THREADS_NUM 10

typedef void *(*callback_func)(void *);

/* task node type */
typedef struct task_node
{
    callback_func process;
    void *arg;
    struct task_node *next;
}task_t;

/* thread node type */
typedef struct thread_node
{
    pthread_t thread;
    int id;
    int priority;
    struct thread_node *next;
}thread_t;

/* thread pool type */
typedef struct
{
    int alive;
    /* thread_list */
    thread_t *thread_list_head;
    int threads_num;
    int busy_threads_num;

    sem_t lamport_sem;

    /* task_queue  */
    task_t *task_queue_front;
    task_t *task_queue_rear;
    int current_tasks_num;  // current num of tasks in queue
    // int max_tasks_num;
    /* mutex and cond */
    pthread_mutex_t lock;  // lock this struct
    // pthread_mutex_t busy_count;  // to count the busy threads
    pthread_cond_t queue_not_full;  // if full, then wait for dequeue
    pthread_cond_t queue_not_empty;  // if empty, then wait for enqueue

}thread_pool_t;

typedef struct
{
    thread_pool_t *tp;
    thread_t *thread;
}arg_t;


void insert_thread_list(thread_pool_t *tp, thread_t *thread);
thread_pool_t *pool_create(int threads_num);
int pool_destroy(thread_pool_t *tp);

int add_task(thread_pool_t *tp, callback_func process, void *arg);
void task_enqueue(thread_pool_t *tp, task_t *task);
task_t *task_dequeue(thread_pool_t *tp);

static void *thread_lamport(void *arg);

#endif
