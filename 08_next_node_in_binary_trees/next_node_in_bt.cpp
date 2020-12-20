/*
 *  面试题8：二叉树的下一个结点
 *  题目：给定一棵二叉树和其中的一个结点，如何找出中序遍历顺序的下一个结点？
 *  树中的结点除了有两个分别指向左右子结点的指针以外，还有一个指向父结点的指针。
 */
#include <iostream>
#include <cstdio>

/*
 * 定义二叉树结点
 */
struct BinaryTreeNode{
  int value;
  BinaryTreeNode* pParent;
  BinaryTreeNode* pLeft;
  BinaryTreeNode* pRight;
};

/*
 * 辅助函数：
 *  创建二叉树结点
 *  连接二叉树结点
 *  按中序遍历打印二叉树
 *  销毁二叉树
 */
BinaryTreeNode* create_node(int value){
  BinaryTreeNode* pNode = new BinaryTreeNode();
  pNode->value = value;
  pNode->pParent = nullptr;
  pNode->pLeft = nullptr;
  pNode->pRight = nullptr;

  return pNode;
}

void connect_node(BinaryTreeNode* pParent, BinaryTreeNode* pLeft, BinaryTreeNode* pRight){
  if(pParent != nullptr){
    pParent->pLeft = pLeft;
    if(pLeft != nullptr)
      pLeft->pParent = pParent;

    pParent->pRight = pRight;
    if(pRight != nullptr)
      pRight->pParent = pParent;
  }
}

void print_binary_tree(BinaryTreeNode* pRoot){
  if(pRoot != nullptr){
    print_binary_tree(pRoot->pLeft);
    printf("%d ", pRoot->value);
    print_binary_tree(pRoot->pRight);
  }
}

void destroy_binary_tree(BinaryTreeNode* pRoot){
  if(pRoot != nullptr){
    BinaryTreeNode* pLeft = pRoot->pLeft;
    BinaryTreeNode* pRight = pRoot->pRight;

    delete pRoot;
    pRoot = nullptr;

    destroy_binary_tree(pLeft);
    destroy_binary_tree(pRight);
  }
}

/*
 * 参数
 *  pNode 二叉树的一个结点
 * 返回值：
 *  中序遍历的情况下，二叉树的下一个结点
 * 复杂度：
 *  时间
 *  空间
 */
BinaryTreeNode* get_next(BinaryTreeNode* pNode){
  // 判断输入有效
  if(pNode == nullptr)
    return nullptr;
  
  BinaryTreeNode* pNext = nullptr;
  if(pNode->pRight != nullptr){
    // 算法: s1.如果存在右子树，寻找右子树中最左边叶子结点
    BinaryTreeNode* pRight = pNode->pRight;
    while(pRight->pLeft != nullptr)
      pRight = pRight->pLeft;
    
    pNext = pRight;
    
  }else if(pNode->pParent != nullptr){
    // 算法: s2.如果不存在右子树，则判断是处在父结点的左子树还是右子树上
    // 若是在左子树，则父结点即为下一个结点；若在右子树，向上遍历找到一个，
    // 找到一个是其父结点的左子结点的结点，那么其父结点为下一个结点
    BinaryTreeNode* pCurrent = pNode;
    BinaryTreeNode* pParent = pNode->pParent;
    while(pParent != nullptr && pCurrent == pParent->pRight){
      pCurrent = pParent;
      pParent = pCurrent->pParent;
    }

    pNext = pParent;
  }

  return pNext;
}

/*
 * 测试代码
 */
void Test(const char* testName, BinaryTreeNode* pNode, BinaryTreeNode* expected){
  if(testName != nullptr)
    printf("%s begins:", testName);

  BinaryTreeNode* pNext = get_next(pNode);
  if(pNext == expected)
    printf("passed.\n");
  else
    printf("failed.\n");
}

// 测试用例
//            8
//        6      10
//       5 7    9  11
void Test1_7()
{
    BinaryTreeNode* pNode8 = create_node(8);
    BinaryTreeNode* pNode6 = create_node(6);
    BinaryTreeNode* pNode10 = create_node(10);
    BinaryTreeNode* pNode5 = create_node(5);
    BinaryTreeNode* pNode7 = create_node(7);
    BinaryTreeNode* pNode9 = create_node(9);
    BinaryTreeNode* pNode11 = create_node(11);

    connect_node(pNode8, pNode6, pNode10);
    connect_node(pNode6, pNode5, pNode7);
    connect_node(pNode10, pNode9, pNode11);

    print_binary_tree(pNode8);

    Test("Test1", pNode8, pNode9);
    Test("Test2", pNode6, pNode7);
    Test("Test3", pNode10, pNode11);
    Test("Test4", pNode5, pNode6);
    Test("Test5", pNode7, pNode8);
    Test("Test6", pNode9, pNode10);
    Test("Test7", pNode11, nullptr);

    destroy_binary_tree(pNode8);
}

//            5
//          4
//        3
//      2
void Test8_11()
{
    BinaryTreeNode* pNode5 = create_node(5);
    BinaryTreeNode* pNode4 = create_node(4);
    BinaryTreeNode* pNode3 = create_node(3);
    BinaryTreeNode* pNode2 = create_node(2);

    connect_node(pNode5, pNode4, nullptr);
    connect_node(pNode4, pNode3, nullptr);
    connect_node(pNode3, pNode2, nullptr);

    print_binary_tree(pNode5);

    Test("Test8", pNode5, nullptr);
    Test("Test9", pNode4, pNode5);
    Test("Test10", pNode3, pNode4);
    Test("Test11", pNode2, pNode3);

    destroy_binary_tree(pNode5);
}

//        2
//         3
//          4
//           5
void Test12_15()
{
    BinaryTreeNode* pNode2 = create_node(2);
    BinaryTreeNode* pNode3 = create_node(3);
    BinaryTreeNode* pNode4 = create_node(4);
    BinaryTreeNode* pNode5 = create_node(5);

    connect_node(pNode2, nullptr, pNode3);
    connect_node(pNode3, nullptr, pNode4);
    connect_node(pNode4, nullptr, pNode5);

    print_binary_tree(pNode2);

    Test("Test12", pNode5, nullptr);
    Test("Test13", pNode4, pNode5);
    Test("Test14", pNode3, pNode4);
    Test("Test15", pNode2, pNode3);

    destroy_binary_tree(pNode2);
}

void Test16()
{
    BinaryTreeNode* pNode5 = create_node(5);

    print_binary_tree(pNode5);

    Test("Test16", pNode5, nullptr);

    destroy_binary_tree(pNode5);
}

int main(int argc, char* argv[])
{
    Test1_7();
    Test8_11();
    Test12_15();
    Test16();
}