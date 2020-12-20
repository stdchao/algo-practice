/*
 * 面试题32（一）：不分行从上往下打印二叉树
 * 题目：从上往下打印出二叉树的每个结点，同一层的结点按照从左到右的顺序打印。
 */
#include <cstdio>
#include <stdexcept>
#include <deque>
using namespace std;

/* 二叉树相关 */
struct  BinaryTreeNode
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

/* Solution 利用辅助队列先进先出的特性，实现树的层次遍历 */
void print_tree_by_level(BinaryTreeNode* pRoot){
  // 判断输入有效
  if(pRoot == nullptr){
    printf("emtpy tree.\n");
    return;
  }
  
  deque<BinaryTreeNode*> dequeTree;
  dequeTree.push_back(pRoot);

  printf("the tree is: ");
  while(dequeTree.size()){
    BinaryTreeNode* pNode = dequeTree.front();
    dequeTree.pop_front();
    printf("%lf ", pNode->mValue);

    if(pNode->pLeft != nullptr)
      dequeTree.push_back(pNode->pLeft);
    if(pNode->pRight != nullptr)
      dequeTree.push_back(pNode->pRight);
  }
  printf("\n");
}

/*
 * 测试代码
 */
void Test(const char* testName, BinaryTreeNode* pRoot){
  if(testName != nullptr)
    printf("%s begins: ", testName);

  print_tree_by_level(pRoot);
}

// 测试用例
//       10
//   6       14
// 4   8  12   16
void Test1(){
  BinaryTreeNode* pNode10 = create_node(10);
  BinaryTreeNode* pNode6 = create_node(6);
  BinaryTreeNode* pNode14 = create_node(14);
  BinaryTreeNode* pNode4 = create_node(4);
  BinaryTreeNode* pNode8 = create_node(8);
  BinaryTreeNode* pNode12 = create_node(12);
  BinaryTreeNode* pNode16 = create_node(16);

  connect_node(pNode10, pNode6, pNode14);
  connect_node(pNode6, pNode4, pNode8);
  connect_node(pNode14, pNode12, pNode16);

  Test("test1", pNode10);

  destroy_tree(pNode10);
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

// 测试用例：空树
void Test5(){
  Test("test5", nullptr);
}

int main(int argc, char** argv){
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();

  return 0;
}