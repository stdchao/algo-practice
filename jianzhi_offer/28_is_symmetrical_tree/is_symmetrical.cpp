/*
 * 面试题28：对称的二叉树
 * 题目：请实现一个函数，用来判断一棵二叉树是不是对称的。如果一棵二叉树和
 * 它的镜像一样，那么它是对称的。
 */
#include <iostream>
#include <cstdio>
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
bool is_symmetrical_core(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2);

bool is_symmetrical(BinaryTreeNode* pRoot){
  if(pRoot == nullptr)
    return true;
  
  return is_symmetrical_core(pRoot->pLeft, pRoot->pRight);
}

// 对左子树进行前序遍历，对右子树进行对称前序遍历
bool is_symmetrical_core(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2){
  // 左右子树都为空
  if(pRoot1 == nullptr && pRoot2 == nullptr)
    return true;
  
  // 只有一个为空
  if(pRoot1 == nullptr || pRoot2 == nullptr)
    return false;

  // 左右子树都不为空，但根结点值不同
  if(pRoot1->mValue != pRoot2->mValue)
    return false;
  
  // 左右子树的根结点值相同，继续递归遍历
  return is_symmetrical_core(pRoot1->pLeft, pRoot2->pRight) && \
    is_symmetrical_core(pRoot1->pRight, pRoot2->pLeft);
}

/*
 * 测试代码
 */
void Test(const char* testName, BinaryTreeNode* pRoot, bool expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(is_symmetrical(pRoot) == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

//            8
//        6      6
//       5 7    7 5
void Test1()
{
  BinaryTreeNode* pNode8 = create_node(8);
  BinaryTreeNode* pNode61 = create_node(6);
  BinaryTreeNode* pNode62 = create_node(6);
  BinaryTreeNode* pNode51 = create_node(5);
  BinaryTreeNode* pNode71 = create_node(7);
  BinaryTreeNode* pNode72 = create_node(7);
  BinaryTreeNode* pNode52 = create_node(5);

  connect_node(pNode8, pNode61, pNode62);
  connect_node(pNode61, pNode51, pNode71);
  connect_node(pNode62, pNode72, pNode52);

  Test("Test1", pNode8, true);

  destroy_tree(pNode8);
}

//            8
//        6      9
//       5 7    7 5
void Test2()
{
  BinaryTreeNode* pNode8 = create_node(8);
  BinaryTreeNode* pNode61 = create_node(6);
  BinaryTreeNode* pNode9 = create_node(9);
  BinaryTreeNode* pNode51 = create_node(5);
  BinaryTreeNode* pNode71 = create_node(7);
  BinaryTreeNode* pNode72 = create_node(7);
  BinaryTreeNode* pNode52 = create_node(5);

  connect_node(pNode8, pNode61, pNode9);
  connect_node(pNode61, pNode51, pNode71);
  connect_node(pNode9, pNode72, pNode52);

  Test("Test2", pNode8, false);

  destroy_tree(pNode8);
}

//            8
//        6      6
//       5 7    7
void Test3()
{
  BinaryTreeNode* pNode8 = create_node(8);
  BinaryTreeNode* pNode61 = create_node(6);
  BinaryTreeNode* pNode62 = create_node(6);
  BinaryTreeNode* pNode51 = create_node(5);
  BinaryTreeNode* pNode71 = create_node(7);
  BinaryTreeNode* pNode72 = create_node(7);

  connect_node(pNode8, pNode61, pNode62);
  connect_node(pNode61, pNode51, pNode71);
  connect_node(pNode62, pNode72, nullptr);

  Test("Test3", pNode8, false);

  destroy_tree(pNode8);
}

//               5
//              / \
//             3   3
//            /     \
//           4       4
//          /         \
//         2           2
//        /             \
//       1               1
void Test4()
{
  BinaryTreeNode* pNode5 = create_node(5);
  BinaryTreeNode* pNode31 = create_node(3);
  BinaryTreeNode* pNode32 = create_node(3);
  BinaryTreeNode* pNode41 = create_node(4);
  BinaryTreeNode* pNode42 = create_node(4);
  BinaryTreeNode* pNode21 = create_node(2);
  BinaryTreeNode* pNode22 = create_node(2);
  BinaryTreeNode* pNode11 = create_node(1);
  BinaryTreeNode* pNode12 = create_node(1);

  connect_node(pNode5, pNode31, pNode32);
  connect_node(pNode31, pNode41, nullptr);
  connect_node(pNode32, nullptr, pNode42);
  connect_node(pNode41, pNode21, nullptr);
  connect_node(pNode42, nullptr, pNode22);
  connect_node(pNode21, pNode11, nullptr);
  connect_node(pNode22, nullptr, pNode12);

  Test("Test4", pNode5, true);

  destroy_tree(pNode5);
}


//               5
//              / \
//             3   3
//            /     \
//           4       4
//          /         \
//         6           2
//        /             \
//       1               1
void Test5()
{
  BinaryTreeNode* pNode5 = create_node(5);
  BinaryTreeNode* pNode31 = create_node(3);
  BinaryTreeNode* pNode32 = create_node(3);
  BinaryTreeNode* pNode41 = create_node(4);
  BinaryTreeNode* pNode42 = create_node(4);
  BinaryTreeNode* pNode6 = create_node(6);
  BinaryTreeNode* pNode22 = create_node(2);
  BinaryTreeNode* pNode11 = create_node(1);
  BinaryTreeNode* pNode12 = create_node(1);

  connect_node(pNode5, pNode31, pNode32);
  connect_node(pNode31, pNode41, nullptr);
  connect_node(pNode32, nullptr, pNode42);
  connect_node(pNode41, pNode6, nullptr);
  connect_node(pNode42, nullptr, pNode22);
  connect_node(pNode6, pNode11, nullptr);
  connect_node(pNode22, nullptr, pNode12);

  Test("Test5", pNode5, false);

  destroy_tree(pNode5);
}

//               5
//              / \
//             3   3
//            /     \
//           4       4
//          /         \
//         2           2
//                      \
//                       1
void Test6()
{
  BinaryTreeNode* pNode5 = create_node(5);
  BinaryTreeNode* pNode31 = create_node(3);
  BinaryTreeNode* pNode32 = create_node(3);
  BinaryTreeNode* pNode41 = create_node(4);
  BinaryTreeNode* pNode42 = create_node(4);
  BinaryTreeNode* pNode21 = create_node(2);
  BinaryTreeNode* pNode22 = create_node(2);
  BinaryTreeNode* pNode12 = create_node(1);

  connect_node(pNode5, pNode31, pNode32);
  connect_node(pNode31, pNode41, nullptr);
  connect_node(pNode32, nullptr, pNode42);
  connect_node(pNode41, pNode21, nullptr);
  connect_node(pNode42, nullptr, pNode22);
  connect_node(pNode21, nullptr, nullptr);
  connect_node(pNode22, nullptr, pNode12);

  Test("Test6", pNode5, false);

  destroy_tree(pNode5);
}

// 只有一个结点
void Test7()
{
  BinaryTreeNode* pNode1 = create_node(1);
  Test("Test7", pNode1, true);

  destroy_tree(pNode1);
}

// 没有结点
void Test8()
{
  Test("Test8", nullptr, true);
}

// 所有结点都有相同的值，树对称
//               5
//              / \
//             5   5
//            /     \
//           5       5
//          /         \
//         5           5
void Test9()
{
  BinaryTreeNode* pNode1 = create_node(5);
  BinaryTreeNode* pNode21 = create_node(5);
  BinaryTreeNode* pNode22 = create_node(5);
  BinaryTreeNode* pNode31 = create_node(5);
  BinaryTreeNode* pNode32 = create_node(5);
  BinaryTreeNode* pNode41 = create_node(5);
  BinaryTreeNode* pNode42 = create_node(5);

  connect_node(pNode1, pNode21, pNode22);
  connect_node(pNode21, pNode31, nullptr);
  connect_node(pNode22, nullptr, pNode32);
  connect_node(pNode31, pNode41, nullptr);
  connect_node(pNode32, nullptr, pNode42);
  connect_node(pNode41, nullptr, nullptr);
  connect_node(pNode42, nullptr, nullptr);

  Test("Test9", pNode1, true);

  destroy_tree(pNode1);
}

// 所有结点都有相同的值，树不对称
//               5
//              / \
//             5   5
//            /     \
//           5       5
//          /       /
//         5       5
void Test10()
{
  BinaryTreeNode* pNode1 = create_node(5);
  BinaryTreeNode* pNode21 = create_node(5);
  BinaryTreeNode* pNode22 = create_node(5);
  BinaryTreeNode* pNode31 = create_node(5);
  BinaryTreeNode* pNode32 = create_node(5);
  BinaryTreeNode* pNode41 = create_node(5);
  BinaryTreeNode* pNode42 = create_node(5);

  connect_node(pNode1, pNode21, pNode22);
  connect_node(pNode21, pNode31, nullptr);
  connect_node(pNode22, nullptr, pNode32);
  connect_node(pNode31, pNode41, nullptr);
  connect_node(pNode32, pNode42, nullptr);
  connect_node(pNode41, nullptr, nullptr);
  connect_node(pNode42, nullptr, nullptr);

  Test("Test10", pNode1, false);

  destroy_tree(pNode1);
}

int main(int argc, char* argv[])
{
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

  return 0;
}