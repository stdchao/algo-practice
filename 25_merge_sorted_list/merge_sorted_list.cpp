/*
 * 面试题25：合并两个排序的链表
 * 题目：输入两个递增排序的链表，合并这两个链表并使新链表中的结点仍然是按照递增排序的。
 * 例如输入图3.11中的链表1和链表2，则合并之后的升序链表如链表3所示。
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

void print_list(ListNode* pHead){
  if(pHead == nullptr){
    printf("empty list.\n");
    return;
  }

  while(pHead != nullptr){
    printf("%d->", pHead->mValue);
    pHead = pHead->pNext;
  }
  printf("null.\n");
}

void destroy_list(ListNode* pHead){
  ListNode* pDelete = nullptr;
  while(pHead != nullptr){
    pDelete = pHead;
    pHead = pHead->pNext;

    delete pDelete;
    pDelete = nullptr;
  }
}

/* Solution 递归方法 */
ListNode* merge_recursively(ListNode* pHead1, ListNode* pHead2){
  // 递归结束条件
  if(pHead1 == nullptr)
    return pHead2;
  else if(pHead2 == nullptr)
    return pHead1;
  
  ListNode* pMerge = nullptr;
  if(pHead1->mValue <= pHead2->mValue){
    pMerge = pHead1;
    pMerge->pNext = merge_recursively(pHead1->pNext, pHead2);
  }else{
    pMerge = pHead2;
    pMerge->pNext = merge_recursively(pHead1, pHead2->pNext);
  }

  return pMerge;
}

ListNode* merge_iteratively(ListNode* pHead1, ListNode* pHead2){
  if(pHead1 == nullptr)
    return pHead2;
  else if(pHead2 == nullptr)
    return pHead1;
  
  // 先确认头结点
  ListNode* pHead = nullptr;
  if(pHead1->mValue <= pHead2->mValue){
    pHead = pHead1;
    pHead1 = pHead1->pNext;
  }else{
    pHead = pHead2;
    pHead2 = pHead2->pNext;
  }
  
  // Main Loop
  ListNode* pNode = pHead;
  while(pHead1 != nullptr && pHead2 != nullptr){
    if(pHead1->mValue <= pHead2->mValue){
      pNode->pNext = pHead1;
      pHead1 = pHead1->pNext;
    }else{
      pNode->pNext = pHead2;
      pHead2 = pHead2->pNext;
    }
    pNode = pNode->pNext;
  }

  if(pHead1 == nullptr)
    pNode->pNext = pHead2;
  else if(pHead2 == nullptr)
    pNode->pNext = pHead1;

  return pHead;
}

/*
 * 测试代码
 */
ListNode* Test(const char* testName, ListNode* pHead1, ListNode* pHead2){
  if(testName != nullptr)
    printf("%s begins:\n", testName);
  
  printf("The first list is:\n");
  print_list(pHead1);

  printf("The second list is:\n");
  print_list(pHead2);

  printf("The merge list is:\n");
  ListNode* pMerge = merge_recursively(pHead1, pHead2);
  // ListNode* pMerge = merge_iteratively(pHead1, pHead2);
  print_list(pMerge);

  return pMerge;
}

// 测试用例 1->3->5, 2->4->6
void Test1(){
  ListNode* pNode1 = create_node(1);
  ListNode* pNode3 = create_node(3);
  ListNode* pNode5 = create_node(5);

  connect_node(pNode1, pNode3);
  connect_node(pNode3, pNode5);

  ListNode* pNode2 = create_node(2);
  ListNode* pNode4 = create_node(4);
  ListNode* pNode6 = create_node(6);

  connect_node(pNode2, pNode4);
  connect_node(pNode4, pNode6);

  ListNode* pMergedHead = Test("Test1", pNode1, pNode2);

  destroy_list(pMergedHead);
}

// 两个链表中有重复的数字
// list1: 1->3->5
// list2: 1->3->5
void Test2()
{
  ListNode* pNode1 = create_node(1);
  ListNode* pNode3 = create_node(3);
  ListNode* pNode5 = create_node(5);

  connect_node(pNode1, pNode3);
  connect_node(pNode3, pNode5);

  ListNode* pNode2 = create_node(1);
  ListNode* pNode4 = create_node(3);
  ListNode* pNode6 = create_node(5);

  connect_node(pNode2, pNode4);
  connect_node(pNode4, pNode6);

  ListNode* pMergedHead = Test("Test2", pNode1, pNode2);

  destroy_list(pMergedHead);
}

// 两个链表都只有一个数字
// list1: 1
// list2: 2
void Test3()
{
  ListNode* pNode1 = create_node(1);
  ListNode* pNode2 = create_node(2);

  ListNode* pMergedHead = Test("Test3", pNode1, pNode2);

  destroy_list(pMergedHead);
}

// 一个链表为空链表
// list1: 1->3->5
// list2: 空链表
void Test4()
{
  ListNode* pNode1 = create_node(1);
  ListNode* pNode3 = create_node(3);
  ListNode* pNode5 = create_node(5);

  connect_node(pNode1, pNode3);
  connect_node(pNode3, pNode5);

  ListNode* pMergedHead = Test("Test4", pNode1, nullptr);

  destroy_list(pMergedHead);
}

// 两个链表都为空链表
// list1: 空链表
// list2: 空链表
void Test5()
{
  ListNode* pMergedHead = Test("Test5", nullptr, nullptr);
}

int main(int argc, char* argv[])
{
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();

  return 0;
}