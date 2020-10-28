#include <stdio.h>
#include <stdlib.h>
#include "../Graph.h"
#include "MST.h"

int main()
{
    AdjMatrixGraph g;
    int i, j;
    g.n = 6;
    g.e = 10;
    for(i=0; i<g.n; i++)
    {
        g.vertex[i].no = i;
        for(j=0; j<g.n; j++)
        {
            if (i == j)
                g.edges[i][j] = 0;
            else
            g.edges[i][j] = INF;
        }
    }
    g.edges[0][1] = g.edges[1][0] = 6;
    g.edges[0][2] = g.edges[2][0] = 1;
    g.edges[0][3] = g.edges[3][0] = 5;
    g.edges[1][2] = g.edges[2][1] = 5;
    g.edges[1][4] = g.edges[4][1] = 3;
    g.edges[2][3] = g.edges[3][2] = 5;
    g.edges[2][4] = g.edges[4][2] = 6;
    g.edges[2][5] = g.edges[5][2] = 4;
    g.edges[3][5] = g.edges[5][3] = 2;
    g.edges[4][5] = g.edges[5][4] = 6;
    DispAdjMatrixGraph(g);
    printf("\nPrim:\n");
    Prim(g, 2);
    printf("\nKrusKal:\n");
    KrusKal(g);
    return 0;
}