#include "list.h"
#include <cstdio>
#include <cstdlib>

/*
 * 创建新结点
 */
ListNode* CreateListNode(int value){
  ListNode* pNode = new ListNode();
  pNode->m_nValue = value;
  pNode->m_pNext = nullptr;
  return pNode;
}

/*
 * 链接结点
 */
void ConnectListNode(ListNode* pCurrent, ListNode* pNext){
  if(pCurrent == nullptr){
    printf("Error to connect two nodes.\n");
    exit(1);
  }

  pCurrent->m_pNext = pNext;
}

/*
 * 打印结点
 */
void PrintListNode(ListNode* pHead){
  if(pHead == nullptr)
    return;

  ListNode* pNode = pHead;
  while(pNode != nullptr){
    printf("%d\t", pNode->m_nValue);
    pNode = pNode->m_pNext;
  }
}