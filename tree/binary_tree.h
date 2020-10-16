/*
 * 二叉树定义相关
 */
#include <cstdio>
#include <stdexcept>

struct BinaryTreeNode{
  double mValue;
  BinaryTreeNode* pLeft;
  BinaryTreeNode* pRight;
};

BinaryTreeNode* CreateNode(double value);
void ConnectNode(BinaryTreeNode* pNode, BinaryTreeNode* pLeft, BinaryTreeNode* pRight);
void DestroyTree(BinaryTreeNode* pRoot);
void PrintTree(BinaryTreeNode* pRoot);
