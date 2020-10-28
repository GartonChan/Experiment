#include <stdio.h>
#include <stdlib.h>
#include "../Graph.h"

int main()
{
    AdjMatrixGraph *g_mat;
    AdjListGraph *g_list;
    g_list = CreateAdjListGraph();
    DispAdjListGraph(*g_list);
    g_mat = ListToMat(*g_list);
    DispAdjMatrixGraph(*g_mat);
    return 0;
}
