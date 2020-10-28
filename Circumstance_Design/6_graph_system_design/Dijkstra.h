#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "Graph.h"

void Dijkstra(AdjMatrixGraph g, int v);
void PrintPath_dijkstra(int prePath[], int i, int v);
void DispPath_dijkstra(int dis[], int prePhth[], int S[], int n, int v);

#endif
