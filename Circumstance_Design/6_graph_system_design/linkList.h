#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

/******************************************************************************
 *  
 *  Description: General Module of LinkList
 * 
 *  Author: GartonChan
 *  
 *  Date: 2020/06/29
 * 
 *  Version: 1.1
 * 
******************************************************************************/


/*** LinkList Node Type ***/

typedef int ElemType;

typedef struct listNode
{
    struct listNode *next;
    ElemType data;
}ListNode;  


/*** LinkList Type ***/
typedef struct linkList
{
    ListNode *head;
    ListNode *tail;
    int sumOfNode;
}LinkList;

/*** The operations of link-list ***/
LinkList *CreateList();
int Destroy(LinkList *pLinkList);
int AddToHead(LinkList *pLinkList, ListNode *pNode);
int AddToTail(LinkList *pLinkList, ListNode *pNode);
int DeleteNode(LinkList *pLinkList, ListNode *pNode);
// int SearchByNode(LinkList *pLinkList, ListNode *pNode);
// ListNode *SearchByData(LinkList *pLinkList, ElemType data);
ListNode *GetHeadNode(LinkList *pLinkList);
ListNode *GetTailNode(LinkList *pLinkList);
ListNode *GetNextNode(LinkList *pLinkList, ListNode *pNode);

#endif
