/*
 * 面试题24：反转链表
 * 题目：定义一个函数，输入一个链表的头结点，反转该链表并输出反转后链表的头结点。
 */
#include <iostream>
using namespace std;

/* 链表相关 */
struct  ListNode
{
  /* data */
  int mValue;
  ListNode* pNext;
};

ListNode* create_node(int value){
  ListNode* pNode = new ListNode();
  pNode->mValue = value;
  pNode->pNext = nullptr;
  return pNode;
}

void connect_node(ListNode* pNode, ListNode* pNext){
  if(pNode == nullptr)
    return;
  
  pNode->pNext = pNext;
}

void print_list(ListNode* pHead){
  if(pHead == nullptr){
    printf("empty list.\n");
    return;
  }

  ListNode* pNode = pHead;
  while(pNode != nullptr){
    printf("%d->", pNode->mValue);
    pNode = pNode->pNext;
  }
  printf("null.\n");
}

void destroy_list(ListNode* pHead){
  while(pHead != nullptr){
    ListNode* pDelete = pHead;
    pHead = pHead->pNext;

    delete pDelete;
    pDelete = nullptr;
  }
}

/* 算法：反转链表 */
ListNode* reverse_list(ListNode* pHead){
  // 空链表和只有一个结点的链表
  if(pHead == nullptr)
    return nullptr;
  
  ListNode* pNode = pHead;
  ListNode* pPre = nullptr;
  while(pNode != nullptr){
    ListNode* pNext = pNode->pNext;
    pNode->pNext = pPre;
    pPre = pNode;
    pNode = pNext;
  }

  return pPre;
}

/* 测试代码 */
ListNode* Test(ListNode* pHead)
{
  printf("The original list is: \n");
  print_list(pHead);

  ListNode* pReversedHead = reverse_list(pHead);

  printf("The reversed list is: \n");
  print_list(pReversedHead);

  return pReversedHead;
}

// 输入的链表有多个结点
void Test1()
{
  ListNode* pNode1 = create_node(1);
  ListNode* pNode2 = create_node(2);
  ListNode* pNode3 = create_node(3);
  ListNode* pNode4 = create_node(4);
  ListNode* pNode5 = create_node(5);

  connect_node(pNode1, pNode2);
  connect_node(pNode2, pNode3);
  connect_node(pNode3, pNode4);
  connect_node(pNode4, pNode5);

  ListNode* pReversedHead = Test(pNode1);

  destroy_list(pReversedHead);
}

// 输入的链表只有一个结点
void Test2()
{
  ListNode* pNode1 = create_node(1);

  ListNode* pReversedHead = Test(pNode1);

  destroy_list(pReversedHead);
}

// 输入空链表
void Test3()
{
  Test(nullptr);
}

int main(int argc, char* argv[])
{
  Test1();
  Test2();
  Test3();

  return 0;
}