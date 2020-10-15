/*
 * 面试题32（二）：分行从上到下打印二叉树
 * 题目：从上到下按层打印二叉树，同一层的结点按从左到右的顺序打印，每一层打印到一行。
 */
#include <cstdio>
#include <stdexcept>
#include <deque>
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

/* Solution 利用队列先进先出实现层次遍历，并且记住每层的结点数目，实现分行打印 */
void print_tree_by_line(BinaryTreeNode* pRoot){
  if(pRoot == nullptr){
    printf("empty tree.\n");
    return;
  }

  deque<BinaryTreeNode*> stackTree; // 辅助队列
  stackTree.push_back(pRoot);
  int levelCheck = 1; // 记录上一层的结点树，每次pop减一，为零换行
  int levelCount = 0; // 记录每层的结点数
  
  printf("the tree is: \n");
  while(stackTree.size()){
    BinaryTreeNode* pNode = stackTree.front();
    printf("%lf ", pNode->mValue);

    if(pNode->pLeft != nullptr){
      stackTree.push_back(pNode->pLeft);
      levelCount++;
    }
    
    if(pNode->pRight != nullptr){
      stackTree.push_back(pNode->pRight);
      levelCount++;
    }

    stackTree.pop_front();
    if(--levelCheck == 0){
      printf("\n");
      levelCheck = levelCount;
      levelCount = 0;
    }
  }
  printf("\n");
}

/*
 * 测试代码
 */
void Test(const char* testName, BinaryTreeNode* pRoot){
  if(testName != nullptr)
    printf("%s begins: ", testName);

  print_tree_by_line(pRoot);
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

int main(int argc, char** argv){
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();

  return 0;
}