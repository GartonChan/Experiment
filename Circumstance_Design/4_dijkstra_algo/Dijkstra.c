#include <stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"

void Dijkstra(AdjMatrixGraph g, int v)
{
    int i, j;
    int min_dis;
    int closest_vertex;
    int S[MAXNUM];  // maintain a set S( G-Gp ) for calculation
    int dis[MAXNUM];  // The min dis Set Gp
    int prePath[MAXNUM];  // record the pre node
    for (i=0; i<g.n; i++)
    {
        dis[i] = g.edges[v][i];
        S[i] = 0;
        if (g.edges[v][i] < INF)
            prePath[i] = v;
        else
            prePath[i] = -1;
    }
    S[v] = 1;
    prePath[v] = -1;  // -1 means no pre vertex
    for (i=1; i<g.n; i++)
    {
        min_dis = INF;
        closest_vertex = -1;
        for (j=0; j<g.n; j++)
        {
            if(S[j]==0 && dis[j] < min_dis)
            {  // to find the closest vertex and get its weight.
                min_dis = dis[j];
                closest_vertex = j;
            }
        }
        if (closest_vertex == -1)
            break;
        S[closest_vertex] = 1;
        for (j=0; j<g.n; j++)
        {  // Update dis array after find a min_dis
            if ( g.edges[closest_vertex][j]<INF 
                && dis[closest_vertex]+g.edges[closest_vertex][j]<dis[j] )
            {
                dis[j] = dis[closest_vertex] + g.edges[closest_vertex][j];
                prePath[j] = closest_vertex;
            }
        } 
    }
    DispPath(dis, prePath, S, g.n, v);
}

void DispPath(int dis[], int prePhth[], int S[], int n, int v)
{
    int i;
    for (i=0; i<n; i++)
    {
        if (S[i] == 1)
        {
            printf("%d到%d的最短路径长度为:%d, 路径为:", v, i, dis[i]);
            printf("(%d->", v);
            PrintPath(prePhth, i, v);
            printf("%d)\n", i);
        }
        else
        {
            printf("%d到%d的最短路径不存在", v, i);
        }
    }
}

void PrintPath(int prePath[], int i, int v)
{
    int path_stack[MAXNUM] = {0};  // define a stack for printing
    int top = 0;
    int pre = prePath[i];  // pre node  
    while(pre>=0 && pre!=v)
    {
        path_stack[top] = pre;
        pre = prePath[pre];
        top++;
    }
    while(top>0)
    {
        top--;
        printf("%d->", path_stack[top]);
    }
}
