/*
 * 二叉树的前中后序，以及层次遍历的递归和迭代实现
 */
#include "binary_tree.h"

/* 前序遍历的递归实现 */
void preorder_travelsal_recursive(BinaryTreeNode* pRoot);

/* 前序遍历的迭代实现 */
void preorder_travelsal_iterative1(BinaryTreeNode* pRoot);
void preorder_travelsal_iterative2(BinaryTreeNode* pRoot);

/* 中序遍历的递归实现 */
void inorder_travelsal_recursive(BinaryTreeNode* pRoot);

/* 中序遍历的迭代实现 */
void inorder_travelsal_iterative(BinaryTreeNode* pRoot);

/* 后序遍历的递归实现 */
void postorder_travelsal_recursive(BinaryTreeNode* pRoot);

/* 后序遍历的迭代实现 */
void postorder_travelsal_iterative1(BinaryTreeNode* pRoot);
void postorder_travelsal_iterative2(BinaryTreeNode* pRoot);

/* 层次遍历的递归实现 */
void levelorder_travelsal_recursive(BinaryTreeNode* pRoot);

/* 层次遍历的迭代实现 */
void levelorder_travelsal_iterative(BinaryTreeNode* pRoot);
