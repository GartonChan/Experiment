#include <stdlib.h>
#include <stdio.h>
#include "../Graph.h"
#include "Floyd.h"

int main(int argc, char const *argv[])
{
    int i, j;
    AdjMatrixGraph g;
    g.n = 7;
    g.e = 12;
    for (i=0; i<g.n; i++)
    {
        g.vertex->no = i;
        for (j=0; j<g.n; j++)
        {
            if(i == j)
                g.edges[i][j] = 0;
            else
                g.edges[i][j] = INF;
        }
    }
    g.edges[0][1] = 4;
    g.edges[0][2] = 6;
    g.edges[0][3] = 6;
    g.edges[1][2] = 1;
    g.edges[1][4] = 7;
    g.edges[3][2] = 2;
    g.edges[3][5] = 5;
    g.edges[2][5] = 4;
    g.edges[2][4] = 6;
    g.edges[4][6] = 6;
    g.edges[5][4] = 1;
    g.edges[5][6] = 8;
    Floyd(g);
    return 0;
}
