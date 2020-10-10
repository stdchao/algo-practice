/*
 * 面试题27：二叉树的镜像
 * 题目：请完成一个函数，输入一个二叉树，该函数输出它的镜像。
 */
#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;

/* 二叉树相关 */
struct BinaryTreeNode{
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

void connect_node(BinaryTreeNode* pRoot, BinaryTreeNode* pLeft, BinaryTreeNode* pRight){
  if(pRoot == nullptr)
    return;

  pRoot->pLeft = pLeft;
  pRoot->pRight = pRight;
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

void print_node(BinaryTreeNode* pNode){
  if(pNode == nullptr){
    printf("nullptr.\n");
    return;
  }
  
  printf("%lf ", pNode->mValue);
  if(pNode->pLeft != nullptr)
    printf("(%lf, ", pNode->pLeft->mValue);
  else
    printf("(nullptr, ");
  
  if(pNode->pRight != nullptr)
    printf("%lf)", pNode->pRight->mValue);
  else
    printf("nullptr)");

  printf("\n");
}

void print_tree(BinaryTreeNode* pRoot){
  print_node(pRoot);

  if(pRoot == nullptr)
    return;

  if(pRoot->pLeft != nullptr)
    print_tree(pRoot->pLeft);

  if(pRoot->pRight != nullptr)
    print_tree(pRoot->pRight);
}

/* Solution 递归实现 */
void mirror_recursively(BinaryTreeNode* pRoot){
  if(pRoot == nullptr)
    return;
  
  BinaryTreeNode* pTemp = pRoot->pLeft;
  pRoot->pLeft = pRoot->pRight;
  pRoot->pRight = pTemp;

  if(pRoot->pLeft != nullptr)
    mirror_recursively(pRoot->pLeft);

  if(pRoot->pRight != nullptr)
    mirror_recursively(pRoot->pRight);
}

/* Solution 迭代实现：利用栈辅助 */
void mirror_iteratively(BinaryTreeNode* pRoot){
  if(pRoot == nullptr)
    return;
  
  stack<BinaryTreeNode*> stackTree;
  stackTree.push(pRoot);

  while(stackTree.size() > 0){
    BinaryTreeNode* pNode = stackTree.top();
    stackTree.pop();

    BinaryTreeNode* pTemp = pNode->pLeft;
    pNode->pLeft = pNode->pRight;
    pNode->pRight = pTemp;

    if(pNode->pLeft != nullptr)
      stackTree.push(pNode->pLeft);
    
    if(pNode->pRight != nullptr)
      stackTree.push(pNode->pRight);
  }
}

/*
 * 测试代码
 */

// 测试用例 完全二叉树
//      8
//    /   \
//   6    10
//  / \  /  \
// 5  7 9   11
void Test1(){
  printf("=======Test1=======\n");
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

  print_tree(pNode8);

  printf("=====Test1: mirror_recursively=====\n");
  mirror_recursively(pNode8);
  print_tree(pNode8);

  printf("=====Test1: mirror_iterasively=====\n");
  mirror_iteratively(pNode8);
  print_tree(pNode8);

  destroy_tree(pNode8);
}

// 测试二叉树：出叶子结点之外，左右的结点都有且只有一个左子结点
//            8
//          7   
//        6 
//      5
//    4
void Test2()
{
  printf("=====Test2 starts:=====\n");
  BinaryTreeNode* pNode8 = create_node(8);
  BinaryTreeNode* pNode7 = create_node(7);
  BinaryTreeNode* pNode6 = create_node(6);
  BinaryTreeNode* pNode5 = create_node(5);
  BinaryTreeNode* pNode4 = create_node(4);

  connect_node(pNode8, pNode7, nullptr);
  connect_node(pNode7, pNode6, nullptr);
  connect_node(pNode6, pNode5, nullptr);
  connect_node(pNode5, pNode4, nullptr);

  print_tree(pNode8);

  printf("=====Test2: mirror_recursively=====\n");
  mirror_recursively(pNode8);
  print_tree(pNode8);

  printf("=====Test2: mirror_iteratively=====\n");
  mirror_iteratively(pNode8);
  print_tree(pNode8);

  destroy_tree(pNode8);
}

// 测试二叉树：出叶子结点之外，左右的结点都有且只有一个右子结点
//            8
//             7   
//              6 
//               5
//                4
void Test3()
{
  printf("=====Test3 starts:=====\n");
  BinaryTreeNode* pNode8 = create_node(8);
  BinaryTreeNode* pNode7 = create_node(7);
  BinaryTreeNode* pNode6 = create_node(6);
  BinaryTreeNode* pNode5 = create_node(5);
  BinaryTreeNode* pNode4 = create_node(4);

  connect_node(pNode8, nullptr, pNode7);
  connect_node(pNode7, nullptr, pNode6);
  connect_node(pNode6, nullptr, pNode5);
  connect_node(pNode5, nullptr, pNode4);

  print_tree(pNode8);

  printf("=====Test3: mirror_recursively=====\n");
  mirror_recursively(pNode8);
  print_tree(pNode8);

  printf("=====Test3: mirror_iteratively=====\n");
  mirror_iteratively(pNode8);
  print_tree(pNode8);

  destroy_tree(pNode8);
}

// 测试空二叉树：根结点为空指针
void Test4()
{
  printf("=====Test4 starts:=====\n");
  BinaryTreeNode* pNode = nullptr;

  print_tree(pNode);

  printf("=====Test4: mirror_recursively=====\n");
  mirror_recursively(pNode);
  print_tree(pNode);

  printf("=====Test4: mirror_iteratively=====\n");
  mirror_iteratively(pNode);
  print_tree(pNode);
}

// 测试只有一个结点的二叉树
void Test5()
{
  printf("=====Test5 starts:=====\n");
  BinaryTreeNode* pNode8 = create_node(8);

  print_tree(pNode8);

  printf("=====Test4: mirror_recursively=====\n");
  mirror_recursively(pNode8);
  print_tree(pNode8);

  printf("=====Test4: mirror_iteratively=====\n");
  mirror_iteratively(pNode8);
  print_tree(pNode8);
}

int main(int argc, char** argv){
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();

  return 0;
}

