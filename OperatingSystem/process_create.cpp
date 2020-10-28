#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define TRUE 1
#define FALSE 0
#define N 2  // 进程数量

int turn;
int t[2] = {1, 0};
bool flag[2];

int main(int argc, char const *argv[])
{
    pid_t pid;
    int num = 0;
    pid = fork();
    if (pid < 0){
        printf("error\n");
        return -1;
    }else if (pid == 0){
        printf("child process\n");
        num = 1;
        printf("%d\n", num);
    }else{
        // wait(NULL);
        printf("parent process\n");
        printf("%d\n", num);
    }
    return 0;
}