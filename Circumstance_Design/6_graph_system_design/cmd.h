#ifndef _CMD_H_
#define _CMD_H_

typedef struct graph_type
{
    void *ptrGraph;
    int type;  // 0 means List, 1 means Matrix
}Graph;

int Help_cmd();
void ShowAllCmd(LinkList *menu);
int CreateGraph_cmd();
int Switch_cmd();
int Display_cmd();
int BFS_cmd();
int DFS_cmd();
int Prim_cmd();
int KrusKal_cmd();
int Dijkstra_cmd();
int Floyd_cmd();
int Quit_cmd();

#endif
