#include "binary_tree_travels.h"

/*
 * 测试代码
 */
void test(){
  //                   1
  //         2                    3
  //    4        5          6          7
  //  8   9   10   11   12    13    14    15  
  BinaryTreeNode* pNode1 = CreateNode(1);
  BinaryTreeNode* pNode2 = CreateNode(2);
  BinaryTreeNode* pNode3 = CreateNode(3);
  BinaryTreeNode* pNode4 = CreateNode(4);
  BinaryTreeNode* pNode5 = CreateNode(5);
  BinaryTreeNode* pNode6 = CreateNode(6);
  BinaryTreeNode* pNode7 = CreateNode(7);
  BinaryTreeNode* pNode8 = CreateNode(8);
  BinaryTreeNode* pNode9 = CreateNode(9);
  BinaryTreeNode* pNode10 = CreateNode(10);
  BinaryTreeNode* pNode11 = CreateNode(11);
  BinaryTreeNode* pNode12 = CreateNode(12);
  BinaryTreeNode* pNode13 = CreateNode(13);
  BinaryTreeNode* pNode14 = CreateNode(14);
  BinaryTreeNode* pNode15 = CreateNode(15);

  ConnectNode(pNode1, pNode2, pNode3);
  ConnectNode(pNode2, pNode4, pNode5);
  ConnectNode(pNode3, pNode6, pNode7);
  ConnectNode(pNode4, pNode8, pNode9);
  ConnectNode(pNode5, pNode10, pNode11);
  ConnectNode(pNode6, pNode12, pNode13);
  ConnectNode(pNode7, pNode14, pNode15);

  printf("Print Tree(default): ");
  PrintTree(pNode1);
  printf("\n");

  printf("Preorder(recursive): ");
  preorder_travelsal_recursive(pNode1);
  printf("\n");

  printf("Preorder(iterative): ");
  preorder_travelsal_iterative(pNode1);
  printf("\n");

  

  DestroyTree(pNode1);
}

/* 主函数 */
int main(int argc, char** argv){
  test();

  return 0;
}