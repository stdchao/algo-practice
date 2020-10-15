/*
 * 面试题32（三）：之字形打印二叉树
 * 题目：请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺
 * 序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，
 * 其他行以此类推。
 */
#include <cstdio>
#include <stdexcept>
#include <stack>
using namespace std;

/* 二叉树相关 */
struct BinaryTreeNode
{
  /* data */
  double mValue;
  BinaryTreeNode* pLeft;
  BinaryTreeNode* pRight;
};

BinaryTreeNode* create_node(double value){
  BinaryTreeNode* pNode = new BinaryTreeNode();
  pNode->mValue = value;
  pNode->pLeft = nullptr;
  pNode->pRight = nullptr;

  return pNode;
}

void connect_node(BinaryTreeNode* pNode, BinaryTreeNode* pLeft, BinaryTreeNode* pRight){
  if(pNode == nullptr)
    return;

  pNode->pLeft = pLeft;
  pNode->pRight = pRight;
}

void destroy_tree(BinaryTreeNode* pRoot){
  if(pRoot == nullptr)
    return;

  BinaryTreeNode* pLeft = pRoot->pLeft;
  BinaryTreeNode* pRight = pRoot->pRight;

  delete pRoot;
  pRoot = nullptr;

  destroy_tree(pLeft);
  destroy_tree(pRight);
}

/* Solution */
void print_tree_by_zigzag(BinaryTreeNode* pRoot){
  // 判断输入有效
  if(pRoot == nullptr){
    printf("empty tree.\n");
    return;
  }

  // 两个辅助栈，分别存储相邻层的结点
  stack<BinaryTreeNode*> stackTrees[2];
  int current = 0; // current代表当前层
  int next = 1; // next代表下一层

  stackTrees[current].push(pRoot);
  while(stackTrees[0].size() || stackTrees[1].size() ){
    BinaryTreeNode* pNode = stackTrees[current].top();
    stackTrees[current].pop();
    printf("%lf ", pNode->mValue);

    if(current == 0){ // 从左向右压栈
      if(pNode->pLeft != nullptr)
        stackTrees[next].push(pNode->pLeft);
      if(pNode->pRight != nullptr)
        stackTrees[next].push(pNode->pRight);
    }else{ // 从右向左压栈
      if(pNode->pRight != nullptr)
        stackTrees[next].push(pNode->pRight);
      if(pNode->pLeft != nullptr)
        stackTrees[next].push(pNode->pLeft);
    }

    if(stackTrees[current].empty()){
      // 判断是否换层
      printf("\n");
      current = 1 - current;
      next = 1 - next;
    }
  }
}

/*
 * 测试代码
 */
void Test(const char* testName, BinaryTreeNode* pRoot){
  if(testName != nullptr)
    printf("%s begins: ", testName);

  print_tree_by_zigzag(pRoot);
}

// 测试用例
//       8
//   6      10
// 5   7  9   11
void Test1(){
  BinaryTreeNode* pNode8 = create_node(8);
  BinaryTreeNode* pNode6 = create_node(6);
  BinaryTreeNode* pNode10 = create_node(10);
  BinaryTreeNode* pNode5 = create_node(5);
  BinaryTreeNode* pNode7 = create_node(7);
  BinaryTreeNode* pNode9 = create_node(9);
  BinaryTreeNode* pNode11 = create_node(11);

  connect_node(pNode8, pNode6, pNode10);
  connect_node(pNode6, pNode5, pNode7);
  connect_node(pNode10, pNode9, pNode11);

  Test("test1", pNode8);

  destroy_tree(pNode8);
}

// 测试用例
//      5
//        4
//          3
//            2
//              1
void Test2(){
  BinaryTreeNode* pNode5 = create_node(5);
  BinaryTreeNode* pNode4 = create_node(4);
  BinaryTreeNode* pNode3 = create_node(3);
  BinaryTreeNode* pNode2 = create_node(2);
  BinaryTreeNode* pNode1 = create_node(1);

  connect_node(pNode5, nullptr, pNode4);
  connect_node(pNode4, nullptr, pNode3);
  connect_node(pNode3, nullptr, pNode2);
  connect_node(pNode2, nullptr, pNode1);

  Test("test2", pNode5);

  destroy_tree(pNode5);
}

// 测试用例
//      5
//     4
//    3
//   2
//  1
void Test3(){
  BinaryTreeNode* pNode5 = create_node(5);
  BinaryTreeNode* pNode4 = create_node(4);
  BinaryTreeNode* pNode3 = create_node(3);
  BinaryTreeNode* pNode2 = create_node(2);
  BinaryTreeNode* pNode1 = create_node(1);

  connect_node(pNode5, pNode4, nullptr);
  connect_node(pNode4, pNode3, nullptr);
  connect_node(pNode3, pNode2, nullptr);
  connect_node(pNode2, pNode1, nullptr);

  Test("test3", pNode5);

  destroy_tree(pNode5);
}

// 测试用例：一个结点的树
void Test4(){
  BinaryTreeNode* pNode1 = create_node(1);
  Test("test4", pNode1);

  destroy_tree(pNode1);
}

// 测试用例
//     100
//  50
//     150
void Test5(){
  BinaryTreeNode* pNode100 = create_node(100);
  BinaryTreeNode* pNode50 = create_node(50);
  BinaryTreeNode* pNode150 = create_node(150);

  connect_node(pNode100, pNode50, nullptr);
  connect_node(pNode50, nullptr, pNode150);

  Test("test5", pNode100);

  destroy_tree(pNode100);
}

// 测试用例：空树
void Test6(){
  Test("test6", nullptr);
}

// 测试用例
//                8
//        4              12
//     2     6       10      14
//   1  3  5  7     9 11   13  15
void Test7(){
   BinaryTreeNode* pNode8 = create_node(8);
    BinaryTreeNode* pNode4 = create_node(4);
    BinaryTreeNode* pNode12 = create_node(12);
    BinaryTreeNode* pNode2 = create_node(2);
    BinaryTreeNode* pNode6 = create_node(6);
    BinaryTreeNode* pNode10 = create_node(10);
    BinaryTreeNode* pNode14 = create_node(14);
    BinaryTreeNode* pNode1 = create_node(1);
    BinaryTreeNode* pNode3 = create_node(3);
    BinaryTreeNode* pNode5 = create_node(5);
    BinaryTreeNode* pNode7 = create_node(7);
    BinaryTreeNode* pNode9 = create_node(9);
    BinaryTreeNode* pNode11 = create_node(11);
    BinaryTreeNode* pNode13 = create_node(13);
    BinaryTreeNode* pNode15 = create_node(15);

    connect_node(pNode8, pNode4, pNode12);
    connect_node(pNode4, pNode2, pNode6);
    connect_node(pNode12, pNode10, pNode14);
    connect_node(pNode2, pNode1, pNode3);
    connect_node(pNode6, pNode5, pNode7);
    connect_node(pNode10, pNode9, pNode11);
    connect_node(pNode14, pNode13, pNode15);

  Test("test7", pNode8);

  destroy_tree(pNode8);
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