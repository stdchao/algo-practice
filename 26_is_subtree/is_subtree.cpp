/*
 * 面试题26：树的子结构
 * 题目：输入两棵二叉树A和B，判断B是不是A的子结构。
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

BinaryTreeNode* create_node(int value){
  BinaryTreeNode* pNode = new BinaryTreeNode();
  pNode->mValue = value;
  pNode->pLeft = nullptr;
  pNode->pRight = nullptr;

  return pNode;
}

void connect_node(BinaryTreeNode* pParent, BinaryTreeNode* pLeft, BinaryTreeNode* pRight){
  if(pParent == nullptr)
    return;

  pParent->pLeft = pLeft;
  pParent->pRight = pRight;
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
    print_node(pRoot->pLeft);

  if(pRoot->pRight != nullptr)
    print_node(pRoot->pRight);
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

/* Solution 递归实现树的遍历 */
bool equal(double num1, double num2);
bool is_tree1_has_tree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2);

bool is_subtree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2){
  // 判断输入有效
  if(pRoot1 == nullptr || pRoot2 == nullptr)
    return false;

  bool result = false;
  // 算法：如果两根结点相等，则继续判断是否完全包含；
  // 如根结点不相等，或者判断不完全包含，则继续递归pRoot1
  if(equal(pRoot1->mValue, pRoot2->mValue)){
    result = is_tree1_has_tree2(pRoot1, pRoot2);
  }
  if(!result)
    result = is_subtree(pRoot1->pLeft, pRoot2);
  if(!result)
    result = is_subtree(pRoot1->pRight, pRoot2);
  
  return result;
}

// 判断duoble浮点数是否相等
bool equal(double num1, double num2){
  if((num1 - num2 > -1e-6) && (num1 - num2 < 1e-6))
    return true;
  else
    return false;
}

// 判断pRoot2是否完全在pRoot1中
bool is_tree1_has_tree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2){
  if(pRoot2 == nullptr)
    return true;
  
  if(pRoot1 == nullptr)
    return false;

  if(!equal(pRoot1->mValue, pRoot2->mValue))
    return false;
  
  return is_tree1_has_tree2(pRoot1->pLeft, pRoot2->pLeft) && \
    is_tree1_has_tree2(pRoot1->pRight, pRoot2->pRight);
}

// ====================测试代码====================
void Test(const char* testName, BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2, \
  bool expected)
{
    if(is_subtree(pRoot1, pRoot2) == expected)
        printf("%s passed.\n", testName);
    else
        printf("%s failed.\n", testName);
}

// 树中结点含有分叉，树B是树A的子结构
//                  8                8
//              /       \           / \
//             8         7         9   2
//           /   \
//          9     2
//               / \
//              4   7
void Test1()
{
    BinaryTreeNode* pNodeA1 = create_node(8);
    BinaryTreeNode* pNodeA2 = create_node(8);
    BinaryTreeNode* pNodeA3 = create_node(7);
    BinaryTreeNode* pNodeA4 = create_node(9);
    BinaryTreeNode* pNodeA5 = create_node(2);
    BinaryTreeNode* pNodeA6 = create_node(4);
    BinaryTreeNode* pNodeA7 = create_node(7);

    connect_node(pNodeA1, pNodeA2, pNodeA3);
    connect_node(pNodeA2, pNodeA4, pNodeA5);
    connect_node(pNodeA5, pNodeA6, pNodeA7);

    BinaryTreeNode* pNodeB1 = create_node(8);
    BinaryTreeNode* pNodeB2 = create_node(9);
    BinaryTreeNode* pNodeB3 = create_node(2);

    connect_node(pNodeB1, pNodeB2, pNodeB3);

    Test("Test1", pNodeA1, pNodeB1, true);

    destroy_tree(pNodeA1);
    destroy_tree(pNodeB1);
}

// 树中结点含有分叉，树B不是树A的子结构
//                  8                8
//              /       \           / \
//             8         7         9   2
//           /   \
//          9     3
//               / \
//              4   7
void Test2()
{
    BinaryTreeNode* pNodeA1 = create_node(8);
    BinaryTreeNode* pNodeA2 = create_node(8);
    BinaryTreeNode* pNodeA3 = create_node(7);
    BinaryTreeNode* pNodeA4 = create_node(9);
    BinaryTreeNode* pNodeA5 = create_node(3);
    BinaryTreeNode* pNodeA6 = create_node(4);
    BinaryTreeNode* pNodeA7 = create_node(7);

    connect_node(pNodeA1, pNodeA2, pNodeA3);
    connect_node(pNodeA2, pNodeA4, pNodeA5);
    connect_node(pNodeA5, pNodeA6, pNodeA7);

    BinaryTreeNode* pNodeB1 = create_node(8);
    BinaryTreeNode* pNodeB2 = create_node(9);
    BinaryTreeNode* pNodeB3 = create_node(2);

    connect_node(pNodeB1, pNodeB2, pNodeB3);

    Test("Test2", pNodeA1, pNodeB1, false);

    destroy_tree(pNodeA1);
    destroy_tree(pNodeB1);
}

// 树中结点只有左子结点，树B是树A的子结构
//                8                  8
//              /                   / 
//             8                   9   
//           /                    /
//          9                    2
//         /      
//        2        
//       /
//      5
void Test3()
{
    BinaryTreeNode* pNodeA1 = create_node(8);
    BinaryTreeNode* pNodeA2 = create_node(8);
    BinaryTreeNode* pNodeA3 = create_node(9);
    BinaryTreeNode* pNodeA4 = create_node(2);
    BinaryTreeNode* pNodeA5 = create_node(5);

    connect_node(pNodeA1, pNodeA2, nullptr);
    connect_node(pNodeA2, pNodeA3, nullptr);
    connect_node(pNodeA3, pNodeA4, nullptr);
    connect_node(pNodeA4, pNodeA5, nullptr);

    BinaryTreeNode* pNodeB1 = create_node(8);
    BinaryTreeNode* pNodeB2 = create_node(9);
    BinaryTreeNode* pNodeB3 = create_node(2);

    connect_node(pNodeB1, pNodeB2, nullptr);
    connect_node(pNodeB2, pNodeB3, nullptr);

    Test("Test3", pNodeA1, pNodeB1, true);

    destroy_tree(pNodeA1);
    destroy_tree(pNodeB1);
}

// 树中结点只有左子结点，树B不是树A的子结构
//                8                  8
//              /                   / 
//             8                   9   
//           /                    /
//          9                    3
//         /      
//        2        
//       /
//      5
void Test4()
{
    BinaryTreeNode* pNodeA1 = create_node(8);
    BinaryTreeNode* pNodeA2 = create_node(8);
    BinaryTreeNode* pNodeA3 = create_node(9);
    BinaryTreeNode* pNodeA4 = create_node(2);
    BinaryTreeNode* pNodeA5 = create_node(5);

    connect_node(pNodeA1, pNodeA2, nullptr);
    connect_node(pNodeA2, pNodeA3, nullptr);
    connect_node(pNodeA3, pNodeA4, nullptr);
    connect_node(pNodeA4, pNodeA5, nullptr);

    BinaryTreeNode* pNodeB1 = create_node(8);
    BinaryTreeNode* pNodeB2 = create_node(9);
    BinaryTreeNode* pNodeB3 = create_node(3);

    connect_node(pNodeB1, pNodeB2, nullptr);
    connect_node(pNodeB2, pNodeB3, nullptr);

    Test("Test4", pNodeA1, pNodeB1, false);

    destroy_tree(pNodeA1);
    destroy_tree(pNodeB1);
}

// 树中结点只有右子结点，树B是树A的子结构
//       8                   8
//        \                   \
//         8                   9   
//          \                   \
//           9                   2
//            \
//             2        
//              \
//               5
void Test5()
{
    BinaryTreeNode* pNodeA1 = create_node(8);
    BinaryTreeNode* pNodeA2 = create_node(8);
    BinaryTreeNode* pNodeA3 = create_node(9);
    BinaryTreeNode* pNodeA4 = create_node(2);
    BinaryTreeNode* pNodeA5 = create_node(5);

    connect_node(pNodeA1, nullptr, pNodeA2);
    connect_node(pNodeA2, nullptr, pNodeA3);
    connect_node(pNodeA3, nullptr, pNodeA4);
    connect_node(pNodeA4, nullptr, pNodeA5);

    BinaryTreeNode* pNodeB1 = create_node(8);
    BinaryTreeNode* pNodeB2 = create_node(9);
    BinaryTreeNode* pNodeB3 = create_node(2);

    connect_node(pNodeB1, nullptr, pNodeB2);
    connect_node(pNodeB2, nullptr, pNodeB3);

    Test("Test5", pNodeA1, pNodeB1, true);

    destroy_tree(pNodeA1);
    destroy_tree(pNodeB1);
}

// 树A中结点只有右子结点，树B不是树A的子结构
//       8                   8
//        \                   \
//         8                   9   
//          \                 / \
//           9               3   2
//            \
//             2        
//              \
//               5
void Test6()
{
    BinaryTreeNode* pNodeA1 = create_node(8);
    BinaryTreeNode* pNodeA2 = create_node(8);
    BinaryTreeNode* pNodeA3 = create_node(9);
    BinaryTreeNode* pNodeA4 = create_node(2);
    BinaryTreeNode* pNodeA5 = create_node(5);

    connect_node(pNodeA1, nullptr, pNodeA2);
    connect_node(pNodeA2, nullptr, pNodeA3);
    connect_node(pNodeA3, nullptr, pNodeA4);
    connect_node(pNodeA4, nullptr, pNodeA5);

    BinaryTreeNode* pNodeB1 = create_node(8);
    BinaryTreeNode* pNodeB2 = create_node(9);
    BinaryTreeNode* pNodeB3 = create_node(3);
    BinaryTreeNode* pNodeB4 = create_node(2);

    connect_node(pNodeB1, nullptr, pNodeB2);
    connect_node(pNodeB2, pNodeB3, pNodeB4);

    Test("Test6", pNodeA1, pNodeB1, false);

    destroy_tree(pNodeA1);
    destroy_tree(pNodeB1);
}

// 树A为空树
void Test7()
{
    BinaryTreeNode* pNodeB1 = create_node(8);
    BinaryTreeNode* pNodeB2 = create_node(9);
    BinaryTreeNode* pNodeB3 = create_node(3);
    BinaryTreeNode* pNodeB4 = create_node(2);

    connect_node(pNodeB1, nullptr, pNodeB2);
    connect_node(pNodeB2, pNodeB3, pNodeB4);

    Test("Test7", nullptr, pNodeB1, false);

    destroy_tree(pNodeB1);
}

// 树B为空树
void Test8()
{
    BinaryTreeNode* pNodeA1 = create_node(8);
    BinaryTreeNode* pNodeA2 = create_node(9);
    BinaryTreeNode* pNodeA3 = create_node(3);
    BinaryTreeNode* pNodeA4 = create_node(2);

    connect_node(pNodeA1, nullptr, pNodeA2);
    connect_node(pNodeA2, pNodeA3, pNodeA4);

    Test("Test8", pNodeA1, nullptr, false);

    destroy_tree(pNodeA1);
}

// 树A和树B都为空
void Test9()
{
    Test("Test9", nullptr, nullptr, false);
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

    return 0;
}
