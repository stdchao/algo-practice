/*
 * 面试题33：二叉搜索树的后序遍历序列
 * 题目：输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
 * 如果是则返回true，否则返回false。假设输入的数组的任意两个数字都互不相同。
 */
#include <float.h>
#include <cstdio>
#include <stdexcept>
#include <stack>
using namespace std;

/* Solution 二叉搜索树BST性质，左子树结点值<根结点值<右子树结点值 */
bool is_postorder_core(int* numbers, int start, int end);

bool is_postorder_recursively(int* numbers, int length){
  // 判断输入有效
  if(numbers == nullptr || length <= 0)
    return false;

  // 算法：先选择数组最后一个元素为根结点，然后遍历数组划分左右子树序列，继续递归判断
  return is_postorder_core(numbers, 0, length-1);
}

bool is_postorder_core(int* numbers, int start, int end){
  // 递归结束条件，单结点子树即叶子结点
  if(start >= end)
    return true;

  // 划分左子树范围
  int i = start;
  while(numbers[i] < numbers[end]){
    i++;
  }

  // 判断右子树是否符合条件
  for(int j=i; j <= end; j++){
    if(numbers[j] < numbers[end])
      return false;
  }

  return is_postorder_core(numbers, start, i-1) && \
    is_postorder_core(numbers, i, end-1);
}

/*
 * 数据观察
 *          10
 *    6           14
 *  4   8     12      16
 * 3 5 7 9  11  13  15  17
 * 后序 3 [5 4] 7 [9 8 6] 11 [13 12] 15 [17 16 14 10]
 * 前序 [10 6 4 3] 5 [8 7] 9 [14 12 11] 13 [16 15] 17
 * 
 * Solution: 后序遍历(左右根)，相当于倒序的(根右左)，遍历顺序为从根结点不断访问右子树，
 * 然后访问其左子树；从后向前循环后序序列，利用辅助栈存储一个递增序列，就是根结点及其右子树们，
 * 当遇到减小的结点，说明访问到了某根结点的左子树，弹栈并保存树根结点，并压栈该左子树(作为
 * 其根结点的树的最小值)，至循环结束，满足条件则返回true
 */
bool is_postorder_iteratively(int* numbers, int length){
  // 判断输入有效
  if(numbers == nullptr || length <= 0)
    return false;

  // 辅助栈，存储一个递增序列，存储根结点及其右子树们
  stack<double> stackTree;
  double root = __DBL_MAX__; // trick: 二叉树当做是root(MAX)的左子树

  for(int i = length-1; i >= 0; i--){
    // 左子树结点小于根结点
    if(numbers[i] > root)
      return false;

    // 保持辅助栈的递增序列
    while(stackTree.size() > 0 && numbers[i] < stackTree.top()){
      root = stackTree.top();
      stackTree.pop();
    }
    
    stackTree.push(numbers[i]);
  }

  return true;
}

/*
 * 测试代码
 */
void Test(const char* testName, int sequence[], int length, bool expected)
{
  if(testName != nullptr)
    printf("%s begins: ", testName);

  if(is_postorder_iteratively(sequence, length) == expected)
    printf("passed.\n");
  else
    printf("failed.\n");
}

//            10
//         /      \
//        6        14
//       /\        /\
//      4  8     12  16
void Test1()
{
  int data[] = {4, 8, 6, 12, 16, 14, 10};
  Test("Test1", data, sizeof(data)/sizeof(int), true);
}

//           5
//          / \
//         4   7
//            /
//           6
void Test2()
{
  int data[] = {4, 6, 7, 5};
  Test("Test2", data, sizeof(data)/sizeof(int), true);
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
void Test3()
{
  int data[] = {1, 2, 3, 4, 5};
  Test("Test3", data, sizeof(data)/sizeof(int), true);
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
void Test4()
{
  int data[] = {5, 4, 3, 2, 1};
  Test("Test4", data, sizeof(data)/sizeof(int), true);
}

// 树中只有1个结点
void Test5()
{
  int data[] = {5};
  Test("Test5", data, sizeof(data)/sizeof(int), true);
}

void Test6()
{
  int data[] = {7, 4, 6, 5};
  Test("Test6", data, sizeof(data)/sizeof(int), false);
}

void Test7()
{
  int data[] = {4, 6, 12, 8, 16, 14, 10};
  Test("Test7", data, sizeof(data)/sizeof(int), false);
}

void Test8()
{
  Test("Test8", nullptr, 0, false);
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

  return 0;
}