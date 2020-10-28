#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "../Graph.h"

// 迪克斯特算法
void Dijkstra(AdjMatrixGraph g, int v);

// 输出正向路径中除起点和终点外的中间路径
void PrintPath(int prePath[], int i, int v);
// 输出完整路径
void DispPath(int dis[], int prePhth[], int S[], int n, int v);

#endif
