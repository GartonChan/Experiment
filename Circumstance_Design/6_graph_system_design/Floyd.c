#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
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
                if (A[i][k]+A[k][j] < A[i][j])
                {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
    DisPath_floyd(A, path, g.n);
}

void DisPath_floyd(int A[MAXNUM][MAXNUM], int path[MAXNUM][MAXNUM], int n)
{
    int i, j;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            if (A[i][j] == INF && i!=j)
            {
                printf("从%2d到%2d没有路径\n", i, j);
            }
            else{
                printf("从%2d到%2d的最短路径长度为:%5d， 路径为:", i, j, A[i][j]);
                printf("(%d->", i);
                PrintPath_floyd(path, i, j);
                printf("%d)\n", j);
            }
        }
    }
}

void PrintPath_floyd(int path[MAXNUM][MAXNUM], int i, int j)
{
    int k;
    k = path[i][j];  // path[k][k] == 1
    if (k == -1)
        return;
    else
    {   
        PrintPath_floyd(path, i, k);  // ! recursion
        printf("%d->", k);
        PrintPath_floyd(path, k, j);
    }
    
}