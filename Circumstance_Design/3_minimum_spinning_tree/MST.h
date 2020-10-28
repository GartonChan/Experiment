#ifndef _MST_H_
#define _MST_H_

// Minimum spanning tree
#include "../Graph.h"
#define MaxSize (MAXNUM * (MAXNUM-1) / 2)

/* store the edge info(including weight and the two vertex no) */
typedef struct
{
    int u;  // start point
    int v;  // end point
    int w;  // weight
}Edge;  

void Prim(AdjMatrixGraph g, int v);  // MST Construction Algorithm
void KrusKal(AdjMatrixGraph g);  // MST COnstruction Algorithm
void InsertSort(Edge E[], int e);  // Insert Sort Algorithm

#endif