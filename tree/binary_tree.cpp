#include "binary_tree.h"

/* 创建结点 */
BinaryTreeNode* CreateNode(double value){
  BinaryTreeNode* pNode = new BinaryTreeNode();
  pNode->mValue = value;
  pNode->pLeft = nullptr;
  pNode->pRight = nullptr;

  return pNode;
}

/* 链接结点 */
void ConnectNode(BinaryTreeNode* pNode, BinaryTreeNode* pLeft, BinaryTreeNode* pRight){
  if(pNode == nullptr)
    return;

  pNode->pLeft = pLeft;
  pNode->pRight = pRight;
}

/* 销毁二叉树 */
void DestroyTree(BinaryTreeNode* pRoot){
  if(pRoot == nullptr)
    return;

  BinaryTreeNode* pLeft = pRoot->pLeft;
  BinaryTreeNode* pRight = pRoot->pRight;

  delete pRoot;
  pRoot = nullptr;

  DestroyTree(pLeft);
  DestroyTree(pRight);
}

/* 打印二叉树，采用前序遍历 */
void PrintTree(BinaryTreeNode* pRoot){
  if(pRoot == nullptr){
    printf("empty tree.\n");
    return;
  }

  printf("%.2lf ", pRoot->mValue);

  if(pRoot->pLeft != nullptr)
    PrintTree(pRoot->pLeft);
    
  if(pRoot->pRight != nullptr)
    PrintTree(pRoot->pRight);
}
