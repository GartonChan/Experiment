#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM 5

void printHello();

int main(int argc, char const *argv[])
{
    pthread_t threads[NUM];
    int rc;
    long t;
    for (t=0; t<NUM; t++){
        rc = pthread_create(&threads[t], NULL, printHello, (void *)t);
    }
    return 0;
}
