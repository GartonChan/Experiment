#ifndef _FLOYD_H_
#define _FLOYD_H_

#include <stdio.h>
#include <stdlib.h>
#include "../Graph.h"

// 弗洛伊德算法
void Floyd(AdjMatrixGraph g);

// 输出路径
void PrintPath(int path[MAXNUM][MAXNUM], int i, int j);
void DisPath(int A[MAXNUM][MAXNUM], int path[MAXNUM][MAXNUM], int n);

#endif
