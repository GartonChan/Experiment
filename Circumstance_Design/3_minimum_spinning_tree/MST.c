// Minimum spanning tree
#include <stdio.h>
#include <stdlib.h>
#include "MST.h"
#include "../Graph.h" 

/* From the aspect of vertexs to construct a MST */
void Prim(AdjMatrixGraph g, int v)
{   
    // U: A child set of V used to construct MST, only including starting vertex is at first.
    // V: A set of all the vertexs
    // V-U: the vertexs do not add in U yet. 
    int lowest_cost[MAXNUM];  // to record the smallest weight from U to V-U
    int min;  // to select the smallest weight
    int closest_vertex[MAXNUM];  // to record the vertex in U which has the min weight.
    int i, j, k;  // counter
    // initialize the lowest_cost and closest_vertex
    for (i=0; i<g.n; i++) 
    {  
        if(g.edges[v][i] > 0)
            lowest_cost[i] = g.edges[v][i];  // get starting point edge info(weight)
        closest_vertex[i] = v;  // initialize equal to starting vertex
    }
    lowest_cost[v] = 0;
    // to find the n-1 vertexs(n-1 edges)
    for (i=1; i<g.n; i++)
    {  
        min = 32767;  // initialize equal to unlimited big. 
        k = -1;  // initialized equal to -1, meaning no vertex is chosen now.
        for (j=0; j<g.n; j++)
        {  // find the vertex nearest by k
            if (lowest_cost[j] != 0 && lowest_cost[j] < min)  // the j-th vertex not in U and weitght is limited num(to get the minimum)
            {
                k = j;
                min = lowest_cost[j];
            }  // choose the j-th vertex(min in lowCost)
        }
        if (k == -1)  // if not found then break
            break;
        
        printf("Edge:(%d, %d), Weight:%d\n", closest_vertex[k], k, min); 
        lowest_cost[k] = 0;  // flag means the vertex add in U;
        for (j=0; j<g.n; j++)  // Update the edge info for the next selection
        {
            if(g.edges[k][j] < lowest_cost[j])  
            // update min weight of the edges
            {
                lowest_cost[j] = g.edges[k][j];
                closest_vertex[j] = k;
            }
            // printf("lowest_cost[%d]=%d ", j, lowest_cost[j]);
        }
        // printf("\n");
    }
}

/* From the aspect of edges to construct MST */
void KrusKal(AdjMatrixGraph g)
{
    int i, j;
    int u1, v1;
    int sn1, sn2;
    int k;
    int vertex_set[MAXNUM];  // to indicate different groups of vertex
    Edge E[MaxSize];  // using E to store all the edges in g
    k = 0;  // index of E start from 0
    
    // initialize for E
    for (i=0; i<g.n; i++)  // O(n^2)
    {  
        for (j=i+1; j<g.n; j++)
        {
            // get all edge info
            if (g.edges[i][j] != 0 && g.edges[i][j] != 32767)
            {
                E[k].u = i;
                E[k].v = j;
                E[k].w = g.edges[i][j];
                k++;
            }
        }
    }
    InsertSort(E, g.e);  // make the weight of E arrange from min to max
    
    for (i=0; i<g.n; i++)
        vertex_set[i] = i;   
    k = 1;  // the process of construction k-th edge, initialized as 1.
    j = 0;  // index of E
    // to construct the MST
    while (k<g.n && j<g.e)
    {
        u1 = E[j].u;  // read the min-weight edge info
        v1 = E[j].v;
        sn1 = vertex_set[u1];  // judge whether will constrct a circuit
        sn2 = vertex_set[v1];
        if (sn1 != sn2)  // it means not belong to the same group(no circuit) 
        {
            printf("Edge:(%d, %d), Weight:%d\n", u1, v1, E[j].w);
            k++; 
        }
        for (i=0; i<g.n; i++)
        {  // to be in the same group
            if (vertex_set[i] == sn2)
                vertex_set[i] = sn1;
        }
        j++;
    }
}

void InsertSort(Edge E[], int e)
{   // 插入排序，将首个元素视为有序序列，后面n-1个视为无序序列并且需要将其插入有序序列
    Edge temp;
    int i, j;  // i为有序序列下标，j为无序序列下标
    for (i=1; i<e; i++)  // i初始化为1,因为下标为0的首个元素被视作有序序列中的元素  
    {
        temp.u = E[i].u;
        temp.v = E[i].v;
        temp.w = E[i].w;    
        for (j=i-1; j>=0 && temp.w < E[j].w; j--)  // j=i-1初始化为有序序列最后一个元素的下标
        {  // temp.w 和 E[j].w的大小关系决定了排序后大小的顺序
            E[j+1].u = E[j].u;
            E[j+1].v = E[j].v;
            E[j+1].w = E[j].w;
        }  // 内循环是找出适当位置的下表并且将需要部分元素后移的过程
        E[j+1].u = temp.u;
        E[j+1].v = temp.v;
        E[j+1].w = temp.w;
    }
}
