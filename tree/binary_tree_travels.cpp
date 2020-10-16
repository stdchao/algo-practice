/*
 * 二叉树的前中后序，以及层次遍历的递归和迭代实现
 */
#include <stack>
#include "binary_tree.h"

/* 前序遍历的递归实现 */
void preorder_travelsal_recursive(BinaryTreeNode* pRoot){
  if(pRoot == nullptr)
    return;

  printf("%.2lf ", pRoot->mValue);

  if(pRoot->pLeft != nullptr)
    preorder_travelsal_recursive(pRoot->pLeft);
  
  if(pRoot->pRight != nullptr)
    preorder_travelsal_recursive(pRoot->pRight);
}

/* 前序遍历的迭代实现 */
void preorder_travelsal_iterative(BinaryTreeNode* pRoot){
  if(pRoot == nullptr)
    return;
  
  // 辅助栈，用来存储所有的右子树
  std::stack<BinaryTreeNode*> stackTree;
  stackTree.push(pRoot);

  while(stackTree.size()){
    BinaryTreeNode* pNode = stackTree.top();
    stackTree.pop();

    while(pNode != nullptr){
      // 对于每个根结点，先访问值，然后将右子树压栈，最后循环访问左子树
      printf("%.2lf ", pNode->mValue);

      if(pNode->pRight != nullptr)
        stackTree.push(pNode->pRight);
      
      pNode = pNode->pLeft;
    }
  }
}

/* 中序遍历的递归实现 */
void inorder_travelsal_recursive(BinaryTreeNode* pRoot){
  if(pRoot == nullptr)
    return;

  // 辅助栈，用来存储根结点和右子树
  std::stack<BinaryTreeNode*> stackTree;
  stackTree.push(pRoot);

  while(stackTree.size()){
    BinaryTreeNode* pNode = stackTree.top();
    stackTree.pop();

    while(pNode->pLeft != nullptr){
      stackTree.push(pNode);
      pNode = pNode->pLeft;
    }

    printf("%.2lf ", pNode);
    
    if(pNode->pRight != nullptr)
      stackTree.push(pNode->pRight);
  }
}

/* 中序遍历的迭代实现 */
void inorder_travelsal_iterative(BinaryTreeNode* pRoot){

}

/* 后序遍历的递归实现 */
void postorder_travelsal_recursive(BinaryTreeNode* pRoot){

}

/* 后序遍历的迭代实现 */
void postorder_travelsal_iterative(BinaryTreeNode* pRoot){

}

/* 层次遍历的递归实现 */
void levelorder_travelsal_recursive(BinaryTreeNode* pRoot){

}

/* 层次遍历的迭代实现 */
void levelorder_travelsal_iterative(BinaryTreeNode* pRoot){

}
