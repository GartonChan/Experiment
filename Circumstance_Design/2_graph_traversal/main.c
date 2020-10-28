#include <stdio.h>
#include <stdlib.h>
#include "../Graph.h"

int main()
{
    AdjListGraph *g;
    g = CreateAdjListGraph();
    DFS(*g, 0);
    printf("\n");
    BFS(*g, 0);
    return 0;
}
