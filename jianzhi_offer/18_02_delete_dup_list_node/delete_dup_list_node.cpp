/*
 * 面试题18（二）：删除链表中重复的结点
 * 题目：在一个排序的链表中，如何删除重复的结点？例如，在图3.4（a）中重复
 * 结点被删除之后，链表如图3.4（b）所示。
 */
#include <cstdio>
#include <stdexcept>
using namespace std;

/* 链表结点 */
struct ListNode{
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

/* Solution 时间复杂度O(n)  */
void delete_dup_list_node(ListNode **pHead){
  // 判断输入有效
  if(pHead == nullptr || *pHead == nullptr)
    throw runtime_error("input invalid.");

  // 算法：pre, node, next
  ListNode* pPreNode = nullptr;
  ListNode* pNode = *pHead;
  while(pNode != nullptr){
    ListNode* pNext = pNode->pNext;
    
    // 判断当前结点pNode是否是重复
    if(pNext != nullptr && pNode->mValue == pNext->mValue){
      int value = pNode->mValue;
      ListNode* pDelete = pNode;
      while(pDelete != nullptr && pDelete->mValue == value){
        // 删除重复结点
        pNext = pDelete->pNext;
        delete pDelete;
        pDelete = pNext;
      }

      // 拼接pre和next
      if(pPreNode == nullptr)
        *pHead = pNext;
      else
        pPreNode->pNext = pNext;
      
      // 继续循环
      pNode = pNext;
    }else{
      pPreNode = pNode;
      pNode = pNext;
    }
  }
}

/*
 * 测试代码
 */
void Test(const char* testName, ListNode** pHead, int *expectVals, int expectLen){
  if(testName != nullptr)
    printf("%s begins: ", testName);
  
  delete_dup_list_node(pHead);

  int index = 0;
  ListNode* pNode = *pHead;
  while(pNode != nullptr && index < expectLen){
    if(pNode->mValue != expectVals[index])
      break;

    pNode = pNode->pNext;
    index++;
  }

  if(pNode == nullptr && index == expectLen)
    printf("passed.\n");
  else
    printf("failed.\n");
}

// 测试用例
// 某些结点是重复的
void Test1()
{
    ListNode* pNode1 = create_node(1);
    ListNode* pNode2 = create_node(2);
    ListNode* pNode3 = create_node(3);
    ListNode* pNode4 = create_node(3);
    ListNode* pNode5 = create_node(4);
    ListNode* pNode6 = create_node(4);
    ListNode* pNode7 = create_node(5);

    connect_node(pNode1, pNode2);
    connect_node(pNode2, pNode3);
    connect_node(pNode3, pNode4);
    connect_node(pNode4, pNode5);
    connect_node(pNode5, pNode6);
    connect_node(pNode6, pNode7);

    ListNode* pHead = pNode1;

    int expectedValues[] = { 1, 2, 5 };
    Test("Test1", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

    destroy_list(pHead);
}

// 没有重复的结点
void Test2()
{
    ListNode* pNode1 = create_node(1);
    ListNode* pNode2 = create_node(2);
    ListNode* pNode3 = create_node(3);
    ListNode* pNode4 = create_node(4);
    ListNode* pNode5 = create_node(5);
    ListNode* pNode6 = create_node(6);
    ListNode* pNode7 = create_node(7);

    connect_node(pNode1, pNode2);
    connect_node(pNode2, pNode3);
    connect_node(pNode3, pNode4);
    connect_node(pNode4, pNode5);
    connect_node(pNode5, pNode6);
    connect_node(pNode6, pNode7);

    ListNode* pHead = pNode1;

    int expectedValues[] = { 1, 2, 3, 4, 5, 6, 7 };
    Test("Test2", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

    destroy_list(pHead);
}

// 除了一个结点之外其他所有结点的值都相同
void Test3()
{
    ListNode* pNode1 = create_node(1);
    ListNode* pNode2 = create_node(1);
    ListNode* pNode3 = create_node(1);
    ListNode* pNode4 = create_node(1);
    ListNode* pNode5 = create_node(1);
    ListNode* pNode6 = create_node(1);
    ListNode* pNode7 = create_node(2);

    connect_node(pNode1, pNode2);
    connect_node(pNode2, pNode3);
    connect_node(pNode3, pNode4);
    connect_node(pNode4, pNode5);
    connect_node(pNode5, pNode6);
    connect_node(pNode6, pNode7);

    ListNode* pHead = pNode1;

    int expectedValues[] = { 2 };
    Test("Test3", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

    destroy_list(pHead);
}

// 所有结点的值都相同
void Test4()
{
    ListNode* pNode1 = create_node(1);
    ListNode* pNode2 = create_node(1);
    ListNode* pNode3 = create_node(1);
    ListNode* pNode4 = create_node(1);
    ListNode* pNode5 = create_node(1);
    ListNode* pNode6 = create_node(1);
    ListNode* pNode7 = create_node(1);

    connect_node(pNode1, pNode2);
    connect_node(pNode2, pNode3);
    connect_node(pNode3, pNode4);
    connect_node(pNode4, pNode5);
    connect_node(pNode5, pNode6);
    connect_node(pNode6, pNode7);

    ListNode* pHead = pNode1;

    Test("Test4", &pHead, nullptr, 0);

    destroy_list(pHead);
}

// 所有结点都成对出现
void Test5()
{
    ListNode* pNode1 = create_node(1);
    ListNode* pNode2 = create_node(1);
    ListNode* pNode3 = create_node(2);
    ListNode* pNode4 = create_node(2);
    ListNode* pNode5 = create_node(3);
    ListNode* pNode6 = create_node(3);
    ListNode* pNode7 = create_node(4);
    ListNode* pNode8 = create_node(4);

    connect_node(pNode1, pNode2);
    connect_node(pNode2, pNode3);
    connect_node(pNode3, pNode4);
    connect_node(pNode4, pNode5);
    connect_node(pNode5, pNode6);
    connect_node(pNode6, pNode7);
    connect_node(pNode7, pNode8);

    ListNode* pHead = pNode1;

    Test("Test5", &pHead, nullptr, 0);

    destroy_list(pHead);
}

// 除了两个结点之外其他结点都成对出现
void Test6()
{
    ListNode* pNode1 = create_node(1);
    ListNode* pNode2 = create_node(1);
    ListNode* pNode3 = create_node(2);
    ListNode* pNode4 = create_node(3);
    ListNode* pNode5 = create_node(3);
    ListNode* pNode6 = create_node(4);
    ListNode* pNode7 = create_node(5);
    ListNode* pNode8 = create_node(5);

    connect_node(pNode1, pNode2);
    connect_node(pNode2, pNode3);
    connect_node(pNode3, pNode4);
    connect_node(pNode4, pNode5);
    connect_node(pNode5, pNode6);
    connect_node(pNode6, pNode7);
    connect_node(pNode7, pNode8);

    ListNode* pHead = pNode1;

    int expectedValues[] = { 2, 4 };
    Test("Test6", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

    destroy_list(pHead);
}

// 链表中只有两个不重复的结点
void Test7()
{
    ListNode* pNode1 = create_node(1);
    ListNode* pNode2 = create_node(2);

    connect_node(pNode1, pNode2);

    ListNode* pHead = pNode1;

    int expectedValues[] = { 1, 2 };
    Test("Test7", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

    destroy_list(pHead);
}

// 结点中只有一个结点
void Test8()
{
    ListNode* pNode1 = create_node(1);

    connect_node(pNode1, nullptr);

    ListNode* pHead = pNode1;

    int expectedValues[] = { 1 };
    Test("Test8", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

    destroy_list(pHead);
}

// 结点中只有两个重复的结点
void Test9()
{
    ListNode* pNode1 = create_node(1);
    ListNode* pNode2 = create_node(1);

    connect_node(pNode1, pNode2);

    ListNode* pHead = pNode1;

    Test("Test9", &pHead, nullptr, 0);

    destroy_list(pHead);
}

// 空链表
void Test10()
{
    ListNode* pHead = nullptr;

    Test("Test10", &pHead, nullptr, 0);
}

int main(int argc, char* argv[])
{
  try{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();
    Test9();
    Test10();
  }catch(exception &e){
    printf("exception %s", e.what());
  }
  
  return 0;
}