/*
 * 面试题22：链表中倒数第k个结点
 * 题目：输入一个链表，输出该链表中倒数第k个结点。为了符合大多数人的习惯，
 * 本题从1开始计数，即链表的尾结点是倒数第1个结点。例如一个链表有6个结点，
 * 从头结点开始它们的值依次是1、2、3、4、5、6。这个链表的倒数第3个结点是
 * 值为4的结点。
 */
// #include <iostream>
#include <iostream>
#include <cstdio>
using namespace std;

/* 链表相关 */
struct ListNode
{
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

void destroy_list(ListNode* pHead){
  while(pHead != nullptr){
    ListNode* pDelete = pHead;
    pHead = pHead->pNext;

    delete pDelete;
    pDelete = nullptr;
  }
}

ListNode* find_k_from_end(ListNode* pHead, unsigned int k){
  // 判断输入有效
  if(pHead == nullptr || k == 0)
    return nullptr;

  // 同向的双指针，一个指针先指向第k-1个结点，另一个指针指向头结点
  // 然后两指针保持相同速度，直到前面指针到达链表尾结点
  ListNode* pAhead = pHead;
  ListNode* pBehind = nullptr;

  for(int i = 0; i < k-1; i++){
    if(pAhead->pNext != nullptr){
      pAhead = pAhead->pNext;
    }else{
      // 当链表不足k
      return nullptr;
    }
  }

  pBehind = pHead;
  while(pAhead->pNext != nullptr){
    pAhead = pAhead->pNext;
    pBehind = pBehind->pNext;
  }

  return pBehind;
}

/*
 * 测试代码
 */

// 测试用例，k在链表中间
void Test1(){
  printf("====Test1 stats:====\n");
  ListNode* pNode1 = create_node(1);
  ListNode* pNode2 = create_node(2);
  ListNode* pNode3 = create_node(3);
  ListNode* pNode4 = create_node(4);
  ListNode* pNode5 = create_node(5);

  connect_node(pNode1, pNode2);
  connect_node(pNode2, pNode3);
  connect_node(pNode3, pNode4);
  connect_node(pNode4, pNode5);

  ListNode* pNode = find_k_from_end(pNode1, 2);
  printf("the %d node from end expect %d, find %d.\n", 2, 4, pNode->mValue);
  destroy_list(pNode1);
}

// 测试用例：k在链表尾部
void Test2(){
  printf("====Test2 stats:====\n");
  ListNode* pNode1 = create_node(1);
  ListNode* pNode2 = create_node(2);
  ListNode* pNode3 = create_node(3);
  ListNode* pNode4 = create_node(4);
  ListNode* pNode5 = create_node(5);

  connect_node(pNode1, pNode2);
  connect_node(pNode2, pNode3);
  connect_node(pNode3, pNode4);
  connect_node(pNode4, pNode5);

  ListNode* pNode = find_k_from_end(pNode1, 1);
  printf("the %d node from end expect %d, find %d.\n", 1, 5, pNode->mValue);
  destroy_list(pNode1);
}

// 测试用例：k在链表头部
void Test3(){
  printf("====Test3 stats:====\n");
  ListNode* pNode1 = create_node(1);
  ListNode* pNode2 = create_node(2);
  ListNode* pNode3 = create_node(3);
  ListNode* pNode4 = create_node(4);
  ListNode* pNode5 = create_node(5);

  connect_node(pNode1, pNode2);
  connect_node(pNode2, pNode3);
  connect_node(pNode3, pNode4);
  connect_node(pNode4, pNode5);

  ListNode* pNode = find_k_from_end(pNode1, 5);
  printf("the %d node from end expect %d, find %d.\n", 5, 1, pNode->mValue);
  destroy_list(pNode1);
}

// 测试用例：空链表
void Test4()
{
  printf("=====Test4 starts:=====\n");
  ListNode* pNode = find_k_from_end(nullptr, 100);
  if(pNode == nullptr){
    printf("passed.\n");
  }else{
    printf("failed.\n");
  }
}

// 测试用例：k大于链表长度
void Test5(){
  printf("====Test5 stats:====\n");
  ListNode* pNode1 = create_node(1);
  ListNode* pNode2 = create_node(2);
  ListNode* pNode3 = create_node(3);
  ListNode* pNode4 = create_node(4);
  ListNode* pNode5 = create_node(5);

  connect_node(pNode1, pNode2);
  connect_node(pNode2, pNode3);
  connect_node(pNode3, pNode4);
  connect_node(pNode4, pNode5);

  ListNode* pNode = find_k_from_end(pNode1, 6);
  if(pNode == nullptr)
    printf("passed.\n");
  else
    printf("failed.\n");
  
  destroy_list(pNode1);
}

// 测试用例：k=0
void Test6(){
  printf("====Test6 stats:====\n");
  ListNode* pNode1 = create_node(1);
  ListNode* pNode2 = create_node(2);
  ListNode* pNode3 = create_node(3);
  ListNode* pNode4 = create_node(4);
  ListNode* pNode5 = create_node(5);

  connect_node(pNode1, pNode2);
  connect_node(pNode2, pNode3);
  connect_node(pNode3, pNode4);
  connect_node(pNode4, pNode5);

  ListNode* pNode = find_k_from_end(pNode1, 0);
  if(pNode == nullptr)
    printf("passed.\n");
  else
    printf("failed.\n");

  destroy_list(pNode1);
}

int main(int argc, char** argv){
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  Test6();

  return 0;
}