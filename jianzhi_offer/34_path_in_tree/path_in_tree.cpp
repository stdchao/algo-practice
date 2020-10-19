/*
 * 面试题34：二叉树中和为某一值的路径
 * 题目：输入一棵二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所
 * 有路径。从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。
 */
#include <vector>
#include "../../tree/binary_tree.h"

void find_path_core(BinaryTreeNode* pRoot, int expectedSum, \
  std::vector<int>& path, int& currentSum);

void find_path_in_tree(BinaryTreeNode* pRoot, int expectedSum){
  // 判断输入有效
  if(pRoot == nullptr)
    return;
  
  // 动态数组，存储路径
  std::vector<int> path; 
  int currentSum = 0;
  find_path_core(pRoot, expectedSum, path, currentSum);
}

/* Solution 树的深度优先遍历 */
void find_path_core(BinaryTreeNode* pRoot, int expectedSum, \
  std::vector<int>& path, int& currentSum){
  // 当前结点加入路径
  path.push_back(pRoot->mValue);
  currentSum += pRoot->mValue;

  // 判断当前结点是否为叶子结点
  if(pRoot->pLeft == nullptr && pRoot->pRight == nullptr && expectedSum == currentSum){
    printf("find a path: ");
    // 顺序遍历容器数组的全部元素
    std::vector<int>::iterator iter = path.begin();
    for(;iter != path.end(); iter++)
      printf("%d\t", *iter);
    printf("\n");
  }
  
  // 选择结点的左子树作为新的路径
  if(pRoot->pLeft != nullptr)
    find_path_core(pRoot->pLeft, expectedSum, path, currentSum);
    
  // 选择结点的右子树作为新的路径
  if(pRoot->pRight != nullptr)
    find_path_core(pRoot->pRight, expectedSum, path, currentSum);

  // 遍历完当前结点的所有路径后，删除当前结点，并减去其值，返回父结点
  path.pop_back();
  currentSum -= pRoot->mValue;
}

/*
 * 测试代码
 */
void Test(const char* testName, BinaryTreeNode* pRoot, int expectedSum)
{
  if(testName != nullptr)
      printf("%s begins:\n", testName);

  find_path_in_tree(pRoot, expectedSum);

  printf("\n");
}

//            10
//         /      \
//        5        12
//       /\
//      4  7     
// 有两条路径上的结点和为22
void Test1()
{
  BinaryTreeNode* pNode10 = CreateNode(10);
  BinaryTreeNode* pNode5 = CreateNode(5);
  BinaryTreeNode* pNode12 = CreateNode(12);
  BinaryTreeNode* pNode4 = CreateNode(4);
  BinaryTreeNode* pNode7 = CreateNode(7);

  ConnectNode(pNode10, pNode5, pNode12);
  ConnectNode(pNode5, pNode4, pNode7);

  printf("Two paths should be found in Test1.\n");
  Test("Test1", pNode10, 22);

  DestroyTree(pNode10);
}

//            10
//         /      \
//        5        12
//       /\
//      4  7     
// 没有路径上的结点和为15
void Test2()
{
  BinaryTreeNode* pNode10 = CreateNode(10);
  BinaryTreeNode* pNode5 = CreateNode(5);
  BinaryTreeNode* pNode12 = CreateNode(12);
  BinaryTreeNode* pNode4 = CreateNode(4);
  BinaryTreeNode* pNode7 = CreateNode(7);

  ConnectNode(pNode10, pNode5, pNode12);
  ConnectNode(pNode5, pNode4, pNode7);

  printf("No paths should be found in Test2.\n");
  Test("Test2", pNode10, 15);

  DestroyTree(pNode10);
}

//               5
//              /
//             4
//            /
//           3
//          /
//         2
//        /
//       1
// 有一条路径上面的结点和为15
void Test3()
{
  BinaryTreeNode* pNode5 = CreateNode(5);
  BinaryTreeNode* pNode4 = CreateNode(4);
  BinaryTreeNode* pNode3 = CreateNode(3);
  BinaryTreeNode* pNode2 = CreateNode(2);
  BinaryTreeNode* pNode1 = CreateNode(1);

  ConnectNode(pNode5, pNode4, nullptr);
  ConnectNode(pNode4, pNode3, nullptr);
  ConnectNode(pNode3, pNode2, nullptr);
  ConnectNode(pNode2, pNode1, nullptr);

  printf("One path should be found in Test3.\n");
  Test("Test3", pNode5, 15);

  DestroyTree(pNode5);
}

// 1
//  \
//   2
//    \
//     3
//      \
//       4
//        \
//         5
// 没有路径上面的结点和为16
void Test4()
{
  BinaryTreeNode* pNode1 = CreateNode(1);
  BinaryTreeNode* pNode2 = CreateNode(2);
  BinaryTreeNode* pNode3 = CreateNode(3);
  BinaryTreeNode* pNode4 = CreateNode(4);
  BinaryTreeNode* pNode5 = CreateNode(5);

  ConnectNode(pNode1, nullptr, pNode2);
  ConnectNode(pNode2, nullptr, pNode3);
  ConnectNode(pNode3, nullptr, pNode4);
  ConnectNode(pNode4, nullptr, pNode5);

  printf("No paths should be found in Test4.\n");
  Test("Test4", pNode1, 16);

  DestroyTree(pNode1);
}

// 树中只有1个结点
void Test5()
{
  BinaryTreeNode* pNode1 = CreateNode(1);

  printf("One path should be found in Test5.\n");
  Test("Test5", pNode1, 1);

  DestroyTree(pNode1);
}

// 树中没有结点
void Test6()
{
  printf("No paths should be found in Test6.\n");
  Test("Test6", nullptr, 0);
}

int main(int argc, char* argv[])
{
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  Test6();

  return 0;
}
