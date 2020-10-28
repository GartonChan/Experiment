#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "cmd.h"
#include "linkList.h"

extern LinkList *menu;
extern Graph graph;
int main(int argc, char const *argv[])
{
    graph.ptrGraph = NULL;
    graph.type = -1;
    char cmd[CMD_MAX_LEN];
    menu = CreateList();
    InitMenu(menu);
    ShowAllCmd(menu);
    while (1)
    {
        printf("Input a cmd >> ");
        scanf("%s", cmd);
        // lower(cmd);
        // printf("input: %s\n", cmd);
        mNode *p = FindCmd(menu, cmd);
        if (p == NULL)
        {
            printf("Error: Cmd Not Found\n");
            continue;
        }
        // printf("%s - %s\n", p->cmd, p->desc);
        if (p->handler != NULL)
        {
            p->handler();
        }
    }
    return 0;
}


void InitMenu(LinkList *mList)
{
    mNode *p = (mNode *)malloc(sizeof(mNode));
    p->cmd = "help";
    p->desc = "Show all cmds in the menu";
    p->handler = Help_cmd;
    // p->arg = NULL;
    AddToTail(mList, (ListNode *)p);
    
    p = (mNode *)malloc(sizeof(mNode));
    p->cmd = "CreateGraph";
    p->desc = "Create a graph using Adjcency list or Adjcent matrix to store";
    p->handler = CreateGraph_cmd;  // CreateListGraph;
    // p->arg = NULL;
    AddToTail(mList, (ListNode *)p);
    
    p = (mNode *)malloc(sizeof(mNode));
    p->cmd = "Switch";
    p->desc = "change from list to matrix or from matrix to list";
    p->handler = Switch_cmd;  // Switch;
    AddToTail(mList, (ListNode *)p);
    
    p = (mNode *)malloc(sizeof(mNode));
    p->cmd = "DisplayGraph";
    p->desc = "Display the graph by the storage form";
    p->handler = Display_cmd;  // Display;
    AddToTail(mList, (ListNode *)p);
    
    p = (mNode *)malloc(sizeof(mNode));
    p->cmd = "BFS";
    p->desc = "Breadth-First Search";
    p->handler = BFS_cmd;  // BFS;
    AddToTail(mList, (ListNode *)p);

    p = (mNode *)malloc(sizeof(mNode));
    p->cmd = "DFS";
    p->desc = "Depth-First Search";
    p->handler = DFS_cmd;  // DFS;
    AddToTail(mList, (ListNode *)p);

    p = (mNode *)malloc(sizeof(mNode));
    p->cmd = "Prim";
    p->desc = "Use Prim algorithm to construct MST";
    p->handler = Prim_cmd;  // Prim;
    AddToTail(mList, (ListNode *)p);

    p = (mNode *)malloc(sizeof(mNode));
    p->cmd = "KrusKal";
    p->desc = "Use KrusKal algorithm to construct MST";
    p->handler = KrusKal_cmd;  // KrusKal;
    AddToTail(mList, (ListNode *)p);

    p = (mNode *)malloc(sizeof(mNode));
    p->cmd = "Dijkstra";
    p->desc = "Compute the shortest way from one vertex to the others";
    p->handler = Dijkstra_cmd;  // Dijkstra;
    AddToTail(mList, (ListNode *)p);

    p = (mNode *)malloc(sizeof(mNode));
    p->cmd = "Floyd";
    p->desc = "Compute the shortest way from each vertex to the others";
    p->handler = Floyd_cmd;  // Floyd;
    AddToTail(mList, (ListNode *)p);

    p = (mNode *)malloc(sizeof(mNode));
    p->cmd = "quit";
    p->desc = "Quit the menu program";
    p->handler = Quit_cmd;
    // p->arg = NULL;
    AddToTail(mList, (ListNode *)p);
}


mNode *FindCmd(LinkList *mList, char *cmd)
{
    mNode *p = (mNode *)mList->head;
    // lower(cmd);
    while (p != NULL)
    {
        // lower(p->cmd);
        if (strcmp(p->cmd, cmd) == 0)
        {
            return p;
        }
        p = (mNode *)GetNextNode(mList, (ListNode *)p);
    }
    return NULL;
}


void ShowAllCmd(LinkList *menu)
{
    printf("----------------------------- Menu List -----------------------------\n");
    mNode *p = (mNode *)menu->head;
    while(p != NULL)
    {
        printf("%s - %s\n", p->cmd, p->desc);
        p = (mNode *)p->next;
    }
    printf("---------------------------------------------------------------------\n");
}

char *lower(char *str)
{
    char *p = str;
    while (*p != '\0')
    {
        if(*p >=65 && *p<=90)
            *p += 32;
        p += 1;
    }
    return str;
}
