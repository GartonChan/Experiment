#include <unistd.h>
#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"
#include "semaphore.h"

#define NUM 5

int ID[NUM]={0,1,2,3,4};
sem_t sem_chopsticks[NUM];
sem_t sem_eaters;
int eaters_num=0;

void sem_signal_init(){
    int i;
    for (i=0; i<NUM; i++){
        if (sem_init(&sem_chopsticks[i],0,1) == -1){
            perror("oops:em_init error!");
            exit(1);
        }
    }
    if (sem_init(&sem_eaters,0,NUM-1) == -1){
        perror("oops:em_init error!");
        exit(1);
    }
}

void philosopher(void * ptid){
    int pthread_id = *(int *)ptid%NUM;
    printf("%d philosopher is thinking...\n",(int)pthread_id);
    sem_wait(&sem_eaters);
    sem_wait(&sem_chopsticks[pthread_id]);
    printf("%d philosopher takes chopstick %d...\n",(int)pthread_id,(int)pthread_id);
    sem_wait(&sem_chopsticks[(pthread_id+1)%NUM]);
    printf("%d philosopher takes chopstick %d...\n",(int)pthread_id,((int)pthread_id+1)%NUM);
    printf("%d philosopher is eating, %d philosopher had already dined.\n",(int)pthread_id,eaters_num);
    sem_post(&sem_chopsticks[(pthread_id+1)%NUM]);
    sem_post(&sem_chopsticks[pthread_id]);
    sem_post(&sem_eaters);
    eaters_num++;
    printf("%d philosopher had dined, by now %d philosopher had already dined.\n",(int)pthread_id,eaters_num);

}

int main(){
    int i,l,j,k;
    for (l = 0; l < 1000; ++l) {
        printf("**********************%d times try ******************************",l+1);
        pthread_t philosopher_threads[NUM];
        sem_signal_init();
        for ( i= 0; i < NUM; i++) {
            printf("%d times\n",i);
            if (pthread_create(&philosopher_threads[i], NULL, (void *)&philosopher, &ID[i]) != 0){
                perror("oops:pthread_create error!");
                exit(1);
            }
        }

        for ( j = 0; j < NUM; j++) {
            pthread_join(philosopher_threads[j], NULL);
        }
        sem_destroy(&sem_eaters);
        for (k = 0; k < NUM ; ++k) {
            sem_destroy(&sem_chopsticks[k]);
        }
        eaters_num = 0;
        // sleep(2);
    }

    return 0;
}
