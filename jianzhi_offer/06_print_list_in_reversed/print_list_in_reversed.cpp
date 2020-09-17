/*
 * 面试题6：从尾到头打印链表
 * 题目：输入一个链表的头结点，从尾到头反过来打印出每个结点的值。
 */
#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;

/*
 * 定义链表结点
 */
struct ListNode
{
  int value;
  ListNode* pNext;
};

// 创建链表
ListNode* create_list(int numbers[], int length){
  ListNode* pHead = nullptr;
  ListNode* pCurrent = nullptr;

  int i = 0;
  while(i < length){
    ListNode* pNode = new ListNode();
    pNode->value = numbers[i];
    pNode->pNext = nullptr;

    if(pHead == nullptr){
      pHead = pNode;
    }else{
      pCurrent->pNext = pNode;
    }

    pCurrent = pNode;
    i++;
  }

  return pHead;
}

// 删除链表
void delete_list(ListNode* pHead){
  ListNode* pCurrent = pHead;

  while(pCurrent != nullptr){
    pHead = pHead->pNext;
    delete pCurrent;
    pCurrent = pHead;
  }
}

// 打印链表的方法
void print_list(ListNode* pHead){
  if(pHead == nullptr)
    return;
  
  ListNode* pNode = pHead;
  while(pNode != nullptr){
    printf("%d\t", pNode->value);
    pNode = pNode->pNext;
  }
}

/* 
 * 参数：
 *  pHead，指向链表头结点的指针
 * 返回值：
 *  空
 * 复杂度：
 *  时间 O(n)
 *  空间 O(n)
 * 算法：
 *  迭代法与递归法
 */
void print_list_in_reversed_interatively(ListNode* pHead){
  // 判断输入有效
  if(pHead == nullptr)
    return;

  // 迭代算法：利用栈的后进先出特性，先顺序遍历链表结点，依次压栈，结束后开始出栈，直至栈空
  stack<ListNode*> stack_nodes;

  // 遍历链表，依次压栈
  ListNode* pNode = pHead;
  while(pNode != nullptr){
    stack_nodes.push(pNode);
    pNode = pNode->pNext;
  }

  // 访问栈顶，然后出栈
  while(!stack_nodes.empty()){
    pNode = stack_nodes.top();
    printf("%d\t", pNode->value);
    stack_nodes.pop();
  }
}

void print_list_in_reversed_recursively(ListNode* pHead){
  if(pHead == nullptr)
    return;

  // 递归算法：递归本质就是栈，所以可将迭代转换成递归
  if(pHead->pNext != nullptr){
    print_list_in_reversed_recursively(pHead->pNext);
  }

  printf("%d\t", pHead->value);
}

/*
 * 测试代码
 */
void Test(ListNode* pHead)
{
    print_list(pHead);
    printf("\n");
    print_list_in_reversed_interatively(pHead);
    printf("\n");
    print_list_in_reversed_recursively(pHead);
}

// 测试用例 1->2->3->4->5
void Test1()
{
    printf("\nTest1 begins.\n");

    int numbers[] = {1, 2, 3, 4, 5};
    int length = 5;
    ListNode* pHead = create_list(numbers, length);

    Test(pHead);

    delete_list(pHead);
}

// 只有一个结点的链表: 1
void Test2()
{
    printf("\nTest2 begins.\n");

    int numbers[] = {1};
    int length = 1;
    ListNode* pHead = create_list(numbers, length);

    Test(pHead);

    delete_list(pHead);
}

// 空链表
void Test3()
{
    printf("\nTest3 begins.\n");

    Test(nullptr);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();

    return 0;
}
