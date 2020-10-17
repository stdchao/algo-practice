/*
 * 二叉树的前中后序，以及层次遍历的递归和迭代实现
 */
#include <stack>
#include <deque>
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

/* 前序遍历的迭代实现1 */
void preorder_travelsal_iterative1(BinaryTreeNode* pRoot){
  if(pRoot == nullptr)
    return;

  // 辅助栈，用来存储访问过的根结点的右左子树
  std::stack<BinaryTreeNode*> stackTree;
  stackTree.push(pRoot);

  while(stackTree.size() > 0){
    // 对于根结点，先访问值并弹栈，然后对右子树压栈，最后对左子树压栈
    BinaryTreeNode* pNode = stackTree.top();
    printf("%.2lf ", pNode->mValue);
    stackTree.pop();

    if(pNode->pRight != nullptr)
      stackTree.push(pNode->pRight);
    
    if(pNode->pLeft != nullptr)
      stackTree.push(pNode->pLeft);
  }
}

/* 前序遍历的迭代实现2 */
void preorder_travelsal_iterative2(BinaryTreeNode* pRoot){
  if(pRoot == nullptr)
    return;
  
  // 辅助栈，用来存储访问过的根结点
  std::stack<BinaryTreeNode*> stackTree;
  BinaryTreeNode* pNode = pRoot;

  while(pNode != nullptr || stackTree.size() > 0){
    // 对于根结点，先访问值，然后持续压栈左子树，至最左叶子结点
    while(pNode != nullptr){
      printf("%.2lf ", pNode->mValue);
      stackTree.push(pNode);
      pNode = pNode->pLeft;
    }

    // 然后弹出栈内根结点，访问其右子树
    pNode = stackTree.top();
    stackTree.pop();
    pNode = pNode->pRight;
  }
}

/* 中序遍历的递归实现 */
void inorder_travelsal_recursive(BinaryTreeNode* pRoot){
  if(pRoot == nullptr)
    return;

  if(pRoot->pLeft != nullptr)
    inorder_travelsal_recursive(pRoot->pLeft);

  printf("%.2lf ", pRoot->mValue);

  if(pRoot->pRight != nullptr)
    inorder_travelsal_recursive(pRoot->pRight);
}

/* 中序遍历的迭代实现 */
void inorder_travelsal_iterative(BinaryTreeNode* pRoot){
  if(pRoot == nullptr)
    return;

  // 辅助栈，用来存储访问过的根结点
  std::stack<BinaryTreeNode*> stackTree;
  BinaryTreeNode* pNode = pRoot;

  while(pNode != nullptr || stackTree.size() > 0){
    // 对于根结点，持续压栈左子树，直至最左叶子结点
    while(pNode != nullptr){
      stackTree.push(pNode);
      pNode = pNode->pLeft;
    }

    // 然后弹出栈内根结点，访问其值，然后访问其右子树
    pNode = stackTree.top();
    printf("%.2lf ", pNode->mValue);
    stackTree.pop();
    pNode = pNode->pRight;
  }
}

/* 后序遍历的递归实现 */
void postorder_travelsal_recursive(BinaryTreeNode* pRoot){
  if(pRoot == nullptr)
    return;
  
  if(pRoot->pLeft != nullptr)
    postorder_travelsal_recursive(pRoot->pLeft);

  if(pRoot->pRight != nullptr)
    postorder_travelsal_recursive(pRoot->pRight);

  printf("%.2lf ", pRoot->mValue);
}

/* 后序遍历的迭代实现1 */
void postorder_travelsal_iterative1(BinaryTreeNode* pRoot){
  if(pRoot == nullptr)
    return;

  // 辅助栈，存储后序遍历序列
  std::stack<double> stackPostorder;

  // 辅助栈，存储根结点的左右子树
  std::stack<BinaryTreeNode*> stackTree;
  stackTree.push(pRoot);

  while(stackTree.size() > 0){
    BinaryTreeNode* pNode = stackTree.top();
    stackTree.pop();
    stackPostorder.push(pNode->mValue);

    if(pNode->pLeft != nullptr)
      stackTree.push(pNode->pLeft);

    if(pNode->pRight != nullptr)
      stackTree.push(pNode->pRight);
  }

  while(stackPostorder.size() > 0){
    printf("%.2lf ", stackPostorder.top());
    stackPostorder.pop();
  }
}

/* 后序遍历的迭代实现2 */
void postorder_travelsal_iterative2(BinaryTreeNode* pRoot){
  if(pRoot == nullptr)
    return;

  // 辅助栈，存储后序遍历序列
  std::stack<double> stackPostorder;

  // 辅助栈，存储访问过的根结点
  std::stack<BinaryTreeNode*> stackTree;
  BinaryTreeNode* pNode = pRoot;

  while(pNode != nullptr || stackTree.size() > 0){
    // 对于根结点，访问其值，然后持续压栈右子树
    while(pNode != nullptr){
      stackPostorder.push(pNode->mValue);
      stackTree.push(pNode);
      pNode = pNode->pRight;
    }

    // 然后弹出栈内根结点，访问其左子树
    pNode = stackTree.top();
    stackTree.pop();
    pNode = pNode->pLeft;
  }

  while(stackPostorder.size() > 0){
    printf("%.2lf ", stackPostorder.top());
    stackPostorder.pop();
  }
}

/* 层次遍历的递归实现 */
void levelorder_travelsal_recursive(BinaryTreeNode* pRoot){
  printf("not complete");
}

/* 层次遍历的迭代实现 */
void levelorder_travelsal_iterative(BinaryTreeNode* pRoot){
  if(pRoot == nullptr)
    return;

  // 辅助队列，存储根结点的左右子结点
  std::deque<BinaryTreeNode*> dequeTree;
  dequeTree.push_back(pRoot);

  while(dequeTree.size() > 0){
    BinaryTreeNode* pNode = dequeTree.front();
    printf("%.2lf ", pNode->mValue);
    dequeTree.pop_front();

    if(pNode->pLeft != nullptr)
      dequeTree.push_back(pNode->pLeft);

    if(pNode->pRight != nullptr)
      dequeTree.push_back(pNode->pRight);
  }
}
