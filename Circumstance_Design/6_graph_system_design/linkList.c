#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkList.h"

LinkList *CreateList()
{
    LinkList *pLinkList;
    pLinkList = (LinkList *)malloc(sizeof(pLinkList));
    pLinkList->head = NULL;
    pLinkList->tail = NULL;
    pLinkList->sumOfNode = 0;
    return pLinkList;
}

int Destroy(LinkList *pLinkList)
{
    ListNode *pNode, *tempNode;
    pNode = tempNode = pLinkList->head;
    while (pNode != NULL)
    {
        pNode = pNode->next;
        free(tempNode);
        tempNode = pNode;
    }
    return 1;
}

int AddToHead(LinkList *pLinkList, ListNode *pNode)
{
    if (pLinkList->sumOfNode == 0)
        pLinkList->tail = pNode;
    pNode->next = pLinkList->head;
    pLinkList->head = pNode;
    pLinkList->sumOfNode++;
    return 1;
}

int AddToTail(LinkList *pLinkList, ListNode *pNode)
{
    pNode->next = NULL;
    if(pLinkList->tail != NULL)
    {
        pLinkList->tail->next = pNode;
        pLinkList->tail = pNode;
    }
    else
    {
        pLinkList->head = pNode;
        pLinkList->tail = pNode;
    }
    pLinkList->sumOfNode++;
    return 1;
}

int DeleteNode(LinkList *pLinkList, ListNode *pNode)
{
    ListNode *p, *tmp;
    p = tmp = pLinkList->head;
    while(tmp!=NULL)
    {
        if(tmp == pNode)
            break;
        p = tmp;
        tmp = tmp->next;
    }
    if(p == pLinkList->head)
    {
        pLinkList->head = pLinkList->head->next;
        free(tmp);
        pLinkList->sumOfNode --;
        return 1;
    }
    else
    {
        p->next = tmp->next;
        free(tmp);
        pLinkList->sumOfNode --;
        return 1;
    }
    return 0;
}

ListNode *GetHeadNode(LinkList *pLinkList)
{
    return pLinkList->head;
}

ListNode *GetTailNode(LinkList *pLinkList)
{
    return pLinkList->tail;
}

ListNode *GetNextNode(LinkList *pLinkList, ListNode *pNode)
{
    ListNode *p;
    p = pLinkList->head;
    while (p!=NULL)
    {
        if(p == pNode)
            break;
        p = p->next;
    }
    if(p == NULL)
        return NULL;
    else
        return p->next;
}

