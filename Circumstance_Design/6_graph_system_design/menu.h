#ifndef _MENU_H_
#define _MENU_H_

#include "linkList.h"
#define CMD_MAX_LEN 30  // 最多命令个数

typedef struct menuNode
{
    ListNode *next;
    char *cmd;
    char *desc;
    int (*handler)();
    //void* arg;
}mNode;

void InitMenu(LinkList *mList);
mNode *FindCmd(LinkList *mList, char *cmd);
void ShowAllCmd(LinkList *menu);
char *lower(char *str);

#endif