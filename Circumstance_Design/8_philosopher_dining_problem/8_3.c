/*** 
 * Dining philosopher's problem
 * the forks stand for the critical area
 * the philosophers stand for the thread. 
***/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define N 5  // the number of philosophers

sem_t chopstick_sem[N];
int philosopher_id[N];

int init();
void philosopher(void *id);
void think(int id);
void getForks(int id);
int leftHand(int id);
int rightHand(int id);
void eat(int id);
void putForks(int id);

int main()
{
    int i;
    pthread_t philosopher_thread[N];
    init();

    for (i=0; i<N; i++)
    {
        // printf("philosopher_id[%d] = %d\n", i, philosopher_id[i]);    
        if( pthread_create(&philosopher_thread[i], NULL, (void *)philosopher, (void *)&philosopher_id[i]) != 0)
        {
            perror("Create threads failed.\n");
            exit(-1);
        }
    }
    for (i=0; i<N; i++)
        pthread_join(philosopher_thread[i], NULL);
    for (i=0; i<N; i++)
        sem_destroy(&chopstick_sem[i]);
    return 0;
}

int init()
{
    int i;
    for (i=0; i<N; i++)
    {
        philosopher_id[i] = i;
        // printf("philosopher_id[%d] = %d\n", i, philosopher_id[i]);
        if(sem_init(&chopstick_sem[i], 0, 1) == -1)
        {
            perror("Init failed\n");
            exit(-1);
        }
    }
    printf("init chopstick_sem!\n");  // done
    return 0;
}

void philosopher(void *arg)
{
    int id = *(int *)arg;
    // printf("%d\n", id);
    while(1)
    {
        think(id);
        getForks(id);
        eat(id);
        putForks(id);
        sleep(1);
    }
}

void think(int id)
{
    char name = (char)65 + (char)id;
    printf("Philosopher %c is thinking...\n", name);
    sleep(3);
}

void eat(int id)
{
    char name = (char)65 + (char)id;
    printf("Philosopher %c is dining...\n", name);
    sleep(1);
}

void getForks(int id)
{
    char name = 65 + id;
    if(id%2 == 0)  // 不对称的获取筷子方式
    {
        sem_wait(&chopstick_sem[leftHand(id)]);
        printf("Philosopher %c get left fork(%d).\n", name, leftHand(id));
        sem_wait(&chopstick_sem[rightHand(id)]);
        printf("Philosopher %c get right fork(%d).\n", name, rightHand(id));
    }
    else
    {
        sem_wait(&chopstick_sem[rightHand(id)]);
        printf("Philosopher %c get right fork(%d).\n", name, rightHand(id));
        sem_wait(&chopstick_sem[leftHand(id)]);
        printf("Philosopher %c get left fork(%d).\n", name, leftHand(id));
    }
}

int leftHand(int id)
{
    // printf("leftHand %d\n", id);
    return id;
}

int rightHand(int id)
{
    // printf("rightHand %d\n", (id+1)%N);
    return (id+1)%N;
}

void putForks(int id)
{
    char name = 65 + id;
    if(id%2 == 0)
    {
        sem_post(&chopstick_sem[leftHand(id)]);
        printf("Philosopher %c put left fork(%d).\n", name, leftHand(id));
        sem_post(&chopstick_sem[rightHand(id)]);
        printf("Philosopher %c put right fork(%d).\n", name, rightHand(id));
    }
    else
    {
        sem_post(&chopstick_sem[rightHand(id)]);
        printf("Philosopher %c put right fork(%d).\n", name, rightHand(id));
        sem_post(&chopstick_sem[leftHand(id)]);
        printf("Philosopher %c put left fork(%d).\n", name, leftHand(id));
    }
}