/*
 * 面试题18（一）：在O(1)时间删除链表结点
 * 题目：给定单向链表的头指针和一个结点指针，定义一个函数在O(1)时间删除该结点。
 */
#include <cstdio>
#include <stdexcept>
using namespace std;

/* 链表结点 */
struct ListNode
{
  int mValue;
  ListNode* pNext;
};

/* 创建结点 */
ListNode* create_node(int value){
  ListNode* pNode = new ListNode();
  pNode->mValue = value;
  pNode->pNext = nullptr;

  return pNode;
}

/* 链接结点 */
void connect_node(ListNode* pCurrent, ListNode* pNext){
  if(pCurrent == nullptr)
    throw runtime_error("input invalid.\n");

  pCurrent->pNext = pNext;
}

/* 打印链表结点 */
void print_list_node(ListNode* pNode){
  if(pNode == nullptr){
    printf("The node is nullptr.\n");
    return;
  }

  printf("The node value is %d.\n", pNode->mValue);
}

/* 打印链表 */
void print_list(ListNode* pHead){
  ListNode* pNode = pHead;

  printf("Print list start: ");
  while(pNode != nullptr){
    printf("%d ", pNode->mValue);
    pNode = pNode->pNext;
  }
  printf("Print list end.\n");
}

/* 销毁链表 */
void destroy_list(ListNode* pHead){
  ListNode* pNode = pHead;
  while(pNode != nullptr){
    pHead = pHead->pNext;
    delete pNode;
    pNode = pHead;
  }
}

/* 删除链表结点, 在O(n)时间内 */
void delete_list_node_N(ListNode** pHead, ListNode* pToDelete){
  // 判断输入有效
  if(*pHead == nullptr || pToDelete == nullptr)
    throw runtime_error("input invalid.\n");

  if(*pHead == pToDelete){
    // 删除头结点
    *pHead = (*pHead)->pNext;
  }else{
    // 删除其他结点，即链表至少有两个结点
    ListNode* pNode = *pHead;
    while(pNode->pNext != nullptr && pNode->pNext != pToDelete)
      pNode = pNode->pNext;
    
    if(pNode->pNext != nullptr && pNode->pNext == pToDelete){
      // 没考虑pToDelete不存在链表的情况，所以必然会进入这条分支
      pNode->pNext = pNode->pNext->pNext;
    }
  }
  
  // 释放结点内存
  if(pToDelete != nullptr){
    delete pToDelete;
    pToDelete = nullptr;
  }
}

/* 删除链表结点，在O(1)时间内 */
void delete_list_node_1(ListNode** pHead, ListNode* pToDelete){
  // 判断输入有效
  if(pHead == nullptr || pToDelete == nullptr)
    throw runtime_error("input invalid.\n");
  
  // 算法：将pToDelete结点内容(mValue和pNext)替换为pToDelete->next的，等效于删除了pToDelete
  if(pToDelete->pNext != nullptr){
    // 删除结点不是尾结点
    ListNode* pNode = pToDelete->pNext;
    pToDelete->mValue = pNode->mValue;
    pToDelete->pNext = pNode->pNext;

    // 释放结点
    delete pNode;
    pNode = nullptr;
  }else if(*pHead == pToDelete){
    // 删除结点是尾结点，也是头结点，即只有一个结点
    *pHead = nullptr;
    
    // 释放结点
    delete pToDelete;
    pToDelete = nullptr;
  }else{
    // 删除结点是尾结点，但不是头结点，即链表至少有两个结点
    ListNode* pNode = *pHead;
    while(pNode->pNext != pToDelete)
      pNode = pNode->pNext;
    
    if(pNode->pNext == pToDelete){
      // 不考虑删除结点不在链表的情况，所以必然会进入这条分支
      pNode->pNext = nullptr;

      // 释放结点
      delete pToDelete;
      pToDelete = nullptr;
    }
  }
}

/*
 * 测试代码
 */
void Test(ListNode* pListHead, ListNode* pNode)
{
    printf("The original list is: \n");
    print_list(pListHead);

    printf("The node to be deleted is: \n");
    print_list_node(pNode);

    delete_list_node_1(&pListHead, pNode);
    
    printf("The result list is: \n");
    print_list(pListHead);
}

// 链表中有多个结点，删除中间的结点
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

    Test(pNode1, pNode3);

    destroy_list(pNode1);
}

// 链表中有多个结点，删除尾结点
void Test2()
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

    Test(pNode1, pNode5);

    destroy_list(pNode1);
}

// 链表中有多个结点，删除头结点
void Test3()
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

    Test(pNode1, pNode1);

    destroy_list(pNode1);
}

// 链表中只有一个结点，删除头结点
void Test4()
{
    ListNode* pNode1 = create_node(1);

    Test(pNode1, pNode1);
}

// 链表为空
void Test5()
{
    Test(nullptr, nullptr);
}

int main(int argc, char* argv[])
{
  Test1();
  Test2();
  Test3();
  Test4();
  
  try{
    Test5();
  }catch(exception &e){
    printf("Exception %s", e.what());
  }
  
  return 0;
}