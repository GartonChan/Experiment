#include <stdio.h>
#include <stdlib.h>
#include "../Graph.h"
#include "Floyd.h"

void Floyd(AdjMatrixGraph g)
{
    int A[MAXNUM][MAXNUM];
    int path[MAXNUM][MAXNUM];
    int i, j, k;
    for(i=0; i<g.n; i++)  // initialize A[][] and path[][]
    {
        for(j=0; j<g.n; j++)
        {
            A[i][j] = g.edges[i][j];
            path[i][j] = -1;
        }
    }
    for (k=0; k<g.n; k++)  // from vi to vk then to vj
    {
        for (i=0; i<g.n; i++)  // from vi to vj
        {
            for (j=0; j<g.n; j++)
            {
                if (A[i][k] + A[k][j] < A[i][j])
                {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
    DisPath(A, path, g.n);
}

void DisPath(int A[MAXNUM][MAXNUM], int path[MAXNUM][MAXNUM], int n)
{
    int i, j;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            if (A[i][j] == INF && i!=j)
            {
                printf("从%d到%d没有路径\n", i, j);
            }
            else{
                printf("从%d到%d的最短路径长度为:%d，路径为:", i, j, A[i][j]);
                printf("(%d->", i);
                PrintPath(path, i, j);
                printf("%d)\n", j);
            }
        }
    }
}

void PrintPath(int path[MAXNUM][MAXNUM], int i, int j)
{
    int k;
    k = path[i][j];  // path[k][k] == 1
    if (k == -1)
        return;
    else
    {   
        PrintPath(path, i, k);  // ! recursion
        printf("%d->", k);
        PrintPath(path, k, j);
    }
    
}