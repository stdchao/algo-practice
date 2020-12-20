/*
 * 面试题23：链表中环的入口结点
 * 题目：一个链表中包含环，如何找出环的入口结点？例如，在图3.8的链表中，
 * 环的入口结点是结点3。
 */
#include <iostream>
#include <cstdio>
using namespace std;

/* 链表相关 */
struct ListNode{
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

/*
 * 算法：使用快慢指针，最终会在链表环中的某个结点相遇
 */
ListNode* meeting_node(ListNode* pHead){
  if(pHead == nullptr)
    return nullptr;
  
  ListNode* pSlow = pHead->pNext;
  if(pSlow == nullptr)
    return nullptr;

  ListNode* pFast = pSlow->pNext;
  while(pFast != nullptr && pSlow != nullptr){
    if(pFast == pSlow)
      return pFast;
    
    pSlow = pSlow->pNext;
    pFast = pFast->pNext;
    if(pFast != nullptr)
      pFast = pFast->pNext;
  }

  return pFast;
}

/*
 * 算法：先达到链表环中的某个结点，依次确认链表中存在环；获取环中结点总数；再用前后指针找到环入口
 */
ListNode* entry_in_list_loop(ListNode* pHead){
  // 判断链表中存在环，并获得环中某个结点
  ListNode* pMeetNode = meeting_node(pHead);
  if(pMeetNode == nullptr)
    return nullptr;
  
  // 获取环中结点总数N
  int nodesInLoop = 1;
  ListNode* pNode = pMeetNode;
  while(pNode->pNext != pMeetNode){
    pNode = pNode->pNext;
    nodesInLoop++;
  }

  // 用前后指针，前指针先走N步，然后同步移动前后指针，最终会相遇在环入口结点
  pNode = pHead;
  while(nodesInLoop > 0){
    pNode = pNode->pNext;
    nodesInLoop--;
  }

  ListNode* pEntry = pHead;
  while(pEntry != pNode){
    pNode = pNode->pNext;
    pEntry = pEntry->pNext;
  }

  return pEntry;
}

/*
 * 测试代码
 */
void Test(const char* testName, ListNode* pHead, ListNode* pEntry){
  if(testName != nullptr)
    printf("%s begins: ", testName);

  if(entry_in_list_loop(pHead) == pEntry)
    printf("passed.\n");
  else
    printf("failed.\n");
}

// 测试用例：单结点的无环链表
void Test1(){
  ListNode* pNode1 = create_node(1);
  Test("Test1", pNode1, nullptr);
  
  delete pNode1;
  pNode1 = nullptr;
}

// 测试用例：单结点的带环链表
void Test2(){
  ListNode* pNode1 = create_node(1);
  connect_node(pNode1, pNode1);
  Test("Test2", pNode1, pNode1);

  delete pNode1;
  pNode1 = nullptr;
}

// 测试用例：多结点的带环链表 1->2->3->4->5->3
void Test3(){
  ListNode* pNode1 = create_node(1);
  ListNode* pNode2 = create_node(2);
  ListNode* pNode3 = create_node(3);
  ListNode* pNode4 = create_node(4);
  ListNode* pNode5 = create_node(5);
  connect_node(pNode1, pNode2);
  connect_node(pNode2, pNode3);
  connect_node(pNode3, pNode4);
  connect_node(pNode4, pNode5);
  connect_node(pNode5, pNode3);

  Test("Test3", pNode1, pNode3);

  delete pNode1;
  pNode1 = nullptr;
  delete pNode2;
  pNode2 = nullptr;
  delete pNode3;
  pNode3 = nullptr;
  delete pNode4;
  pNode4 = nullptr;
  delete pNode5;
  pNode5 = nullptr;
}

// 测试用例：多结点的带环链表 1->2->3->4->5->1
void Test4(){
  ListNode* pNode1 = create_node(1);
  ListNode* pNode2 = create_node(2);
  ListNode* pNode3 = create_node(3);
  ListNode* pNode4 = create_node(4);
  ListNode* pNode5 = create_node(5);
  connect_node(pNode1, pNode2);
  connect_node(pNode2, pNode3);
  connect_node(pNode3, pNode4);
  connect_node(pNode4, pNode5);
  connect_node(pNode5, pNode1);

  Test("Test4", pNode1, pNode1);

  delete pNode1;
  pNode1 = nullptr;
  delete pNode2;
  pNode2 = nullptr;
  delete pNode3;
  pNode3 = nullptr;
  delete pNode4;
  pNode4 = nullptr;
  delete pNode5;
  pNode5 = nullptr;
}

// 测试用例：多结点的带环链表 1->2->3->4->5->5
void Test5(){
  ListNode* pNode1 = create_node(1);
  ListNode* pNode2 = create_node(2);
  ListNode* pNode3 = create_node(3);
  ListNode* pNode4 = create_node(4);
  ListNode* pNode5 = create_node(5);
  connect_node(pNode1, pNode2);
  connect_node(pNode2, pNode3);
  connect_node(pNode3, pNode4);
  connect_node(pNode4, pNode5);
  connect_node(pNode5, pNode5);

  Test("Test5", pNode1, pNode5);

  delete pNode1;
  pNode1 = nullptr;
  delete pNode2;
  pNode2 = nullptr;
  delete pNode3;
  pNode3 = nullptr;
  delete pNode4;
  pNode4 = nullptr;
  delete pNode5;
  pNode5 = nullptr;
}

// 测试用例：多结点的无环链表 1->2->3->4->5
void Test6(){
  ListNode* pNode1 = create_node(1);
  ListNode* pNode2 = create_node(2);
  ListNode* pNode3 = create_node(3);
  ListNode* pNode4 = create_node(4);
  ListNode* pNode5 = create_node(5);
  connect_node(pNode1, pNode2);
  connect_node(pNode2, pNode3);
  connect_node(pNode3, pNode4);
  connect_node(pNode4, pNode5);

  Test("Test6", pNode1, nullptr);

  delete pNode1;
  pNode1 = nullptr;
  delete pNode2;
  pNode2 = nullptr;
  delete pNode3;
  pNode3 = nullptr;
  delete pNode4;
  pNode4 = nullptr;
  delete pNode5;
  pNode5 = nullptr;
}

// 测试用例：空链表
void Test7(){
  Test("Test7", nullptr, nullptr);
}

int main(int argc, char** argv){
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  Test6();
  Test7();

  return 0;
}