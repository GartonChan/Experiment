#include <stdio.h>
#include <stdlib.h>
#include "linkList.h"
#include "cmd.h"
#include "Graph.h"
#include "MST.h"
#include "Dijkstra.h"
#include "Floyd.h"

LinkList *menu;
Graph graph;

int Help_cmd()
{
    ShowAllCmd(menu);
    return 0;
}

int CreateGraph_cmd()
{
    printf("0.Use Adjacency List to store\n");
    printf("1.Use Adjacent Matrix to store\n");
    printf("Select a mode(input number): ");
    scanf("%d", &graph.type);
    printf("type:%d\n", graph.type);
    if (graph.type == 0)
        graph.ptrGraph = CreateAdjListGraph();
    else if(graph.type == 1)
        graph.ptrGraph = CreateAdjMatrixGraph();
    else
        return -1;
    return 0;
}

int Switch_cmd()
{
    if (graph.type == 0)
    {
        graph.ptrGraph = ListToMat(*(AdjListGraph *)graph.ptrGraph);
        graph.type = 1;
    }
    else if (graph.type == 1)
    {
        graph.ptrGraph = MatToList(*(AdjMatrixGraph *)graph.ptrGraph);
        graph.type = 0;
    }
    else
        return -1;
}

int Display_cmd()
{
    if (graph.type == 0)
        DispAdjListGraph(*(AdjListGraph *)graph.ptrGraph);
    else if (graph.type == 1)
        DispAdjMatrixGraph(*(AdjMatrixGraph *)graph.ptrGraph);
    else
        return -1;
    return 0;
}

int BFS_cmd()
{
    int v_no;
    printf("The start vertex no:");
    scanf("%d", &v_no);
    if(graph.type == 1)
    {
        Graph graph_tmp;
        graph_tmp.ptrGraph = MatToList(*(AdjMatrixGraph *)graph.ptrGraph);
        graph_tmp.type = 0;
        BFS(*(AdjListGraph *)graph_tmp.ptrGraph, v_no);
    }
    else if(graph.type == 0)
        BFS(*(AdjListGraph *)graph.ptrGraph, v_no);
    else
        return -1;
    return 0;
}

int DFS_cmd()
{
    int v_no;
    printf("The start vertex no:");
    scanf("%d", &v_no);
    if(graph.type == 1)
    {
        Graph graph_tmp;
        graph_tmp.ptrGraph = MatToList(*(AdjMatrixGraph *)graph.ptrGraph);
        graph_tmp.type = 0;
        DFS(*(AdjListGraph *)graph_tmp.ptrGraph, v_no);
    }
    else if(graph.type == 0)
        DFS(*(AdjListGraph *)graph.ptrGraph, v_no);
    else
        return -1;
    return 0;
}

int Prim_cmd() 
{
    int v_no;
    printf("The start vertex no:");
    scanf("%d", &v_no);
    if(graph.type == 0)
    {
        Graph graph_tmp;
        graph_tmp.ptrGraph = ListToMat(*(AdjListGraph *)graph.ptrGraph);
        graph_tmp.type = 0;
        Prim(*(AdjMatrixGraph *)graph_tmp.ptrGraph, v_no);
    }
    else if(graph.type == 1)
        Prim(*(AdjMatrixGraph *)graph.ptrGraph, v_no);
    else
        return -1;
    return 0;
}

int KrusKal_cmd() 
{
    if(graph.type == 0)
    {
        Graph graph_tmp;
        graph_tmp.ptrGraph = ListToMat(*(AdjListGraph *)graph.ptrGraph);
        graph_tmp.type = 0;
        KrusKal(*(AdjMatrixGraph *)graph_tmp.ptrGraph);
    }
    else if(graph.type == 1)
        KrusKal(*(AdjMatrixGraph *)graph.ptrGraph);
    else
        return -1;
    return 0;
}

int Dijkstra_cmd()
{
    int v_no;
    printf("The start vertex no:");
    scanf("%d", &v_no);
    if(graph.type == 0)  // if it is listGraph then change to Mat
    {
        Graph graph_tmp;
        graph_tmp.ptrGraph = ListToMat(*(AdjListGraph *)graph.ptrGraph);
        graph_tmp.type = 0;
        Dijkstra(*(AdjMatrixGraph *)graph_tmp.ptrGraph, v_no);
    }
    else if(graph.type == 1)
        Dijkstra(*(AdjMatrixGraph *)graph.ptrGraph, v_no);
    else
        return -1;
    return 0;
}

int Floyd_cmd()
{
    if(graph.type == 0)
    {
        Graph graph_tmp;
        graph_tmp.ptrGraph = ListToMat(*(AdjListGraph *)graph.ptrGraph);
        graph_tmp.type = 0;
        Floyd(*(AdjMatrixGraph *)graph_tmp.ptrGraph);
    }
    else if(graph.type == 1)
        Floyd(*(AdjMatrixGraph *)graph.ptrGraph);
    else
        return -1;
    return 0;
}

int Quit_cmd()
{
    printf("Bye~\n");
    exit(0);
    return 0;
}
