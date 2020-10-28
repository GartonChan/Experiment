#ifndef _FLOYD_H_
#define _FLOYD_H_

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

void Floyd(AdjMatrixGraph g);
void PrintPath_floyd(int path[MAXNUM][MAXNUM], int i, int j);
void DisPath_floyd(int A[MAXNUM][MAXNUM], int path[MAXNUM][MAXNUM], int n);

#endif
