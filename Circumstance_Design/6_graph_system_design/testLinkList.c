#include <stdio.h>
#include <stdlib.h>
#include "linkList.c"

typedef struct node
{
    ListNode *next;
    int data;  // data
}Node;

int main()
{
    int i;
    LinkList *list;
    list = CreateList();
    Node *node;
    for (i=0; i<10; i++)
    {
        node = (ListNode *)malloc(sizeof(Node));
        node->data = i+1;
        AddToTail(list, (ListNode *)node);
    }
    node = (Node *)list->head;
    for (i=0; i<10; i++)
    {
        printf("%d\n", node->data);
        node = (Node *)node->next;
    }
    // printf("%d\n", SearchByNode(list, list->tail));
    return 0;
}