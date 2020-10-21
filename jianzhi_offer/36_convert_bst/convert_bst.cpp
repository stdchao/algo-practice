/*
 * 面试题36：二叉搜索树与双向链表
 * 题目：输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。
 * 要求不能创建任何新的结点，只能调整树中结点指针的指向。
 */
#include <stack>

/* 二叉搜索树相关 */
struct BinaryTreeNode
{
  double mValue;
  BinaryTreeNode* pLeft;
  BinaryTreeNode* pRight;
};

BinaryTreeNode* create_node(double value){
  BinaryTreeNode* pNode = new BinaryTreeNode();
  pNode->mValue = value;
  pNode->pLeft = nullptr;
  pNode->pRight = nullptr;

  return pNode;
}

void connect_node(BinaryTreeNode* pNode, BinaryTreeNode* pLeft, BinaryTreeNode* pRight){
  if(pNode == nullptr)
    return;

  pNode->pLeft = pLeft;
  pNode->pRight = pRight;
}

void print_tree(BinaryTreeNode* pRoot){
  if(pRoot == nullptr){
    printf("empty tree.\n");
    return;
  }

  if(pRoot->pLeft != nullptr)
    print_tree(pRoot->pLeft);
  
  printf("%.2lf->", pRoot->mValue);
  
  if(pRoot->pRight != nullptr)
    print_tree(pRoot->pRight);
}

/* Solution 在中序遍历的过程中实现双向链表的转化，采用迭代方式实现 */
BinaryTreeNode* convert_bst(BinaryTreeNode* pRoot){
  if(pRoot == nullptr)
    return nullptr;
  
  // 存储前后两个结点
  std::stack<BinaryTreeNode*> stackTree;
  BinaryTreeNode* pNode = pRoot;
  BinaryTreeNode* pPre = nullptr;
  BinaryTreeNode* pHead = nullptr;
  while(pNode != nullptr || stackTree.size() > 0){
    while(pNode != nullptr){
      stackTree.push(pNode);
      pNode = pNode->pLeft;
    }

    // 此时pNode为按中序遍历的访问结点
    pNode = stackTree.top();
    stackTree.pop();
    
    // 该结点若不是头结点，则让上个结点的右指针指向当前结点
    if(pPre != nullptr)
      pPre->pRight = pNode;
    else
      pHead = pNode;

    // 然后让该结点的左指针指向上个结点
    pNode->pLeft = pPre;

    // 判断该结点是否是最后一个结点
    if(pNode->pRight == nullptr && stackTree.size() == 0)
      pNode->pRight = nullptr;
    
    pPre = pNode;
    pNode = pNode->pRight;
  }

  return pHead;
}

/* Solution 按照中序遍历的顺序，采用递归方法实现 */
void convert_bst_core(BinaryTreeNode* pNode, BinaryTreeNode** pLastNode){
  if(pNode == nullptr)
    return;

  BinaryTreeNode* pCurrent = pNode;
  
  // 先递归遍历左子树
  if(pCurrent->pLeft != nullptr)
    convert_bst_core(pCurrent->pLeft, pLastNode);

  // 对于当前结点，连接左子树组成链表的尾部元素
  pCurrent->pLeft = *pLastNode;
  if(*pLastNode != nullptr)
    (*pLastNode)->pRight = pCurrent;

  // 对于右子树来说，前面组成链表的尾部元素更新为当前结点
  *pLastNode = pCurrent;

  // 最后递归遍历右子树
  if(pCurrent->pRight != nullptr)
    convert_bst_core(pCurrent->pRight, pLastNode);
}

BinaryTreeNode* convert_bst_recursively(BinaryTreeNode* pRoot){
  if(pRoot == nullptr)
    return nullptr;
  
  BinaryTreeNode* pLastNode = nullptr;
  convert_bst_core(pRoot, &pLastNode);

  // 根据尾部pLastNode, 找回链表头部
  BinaryTreeNode* pHead = pLastNode;
  while(pHead != nullptr && pHead->pLeft != nullptr)
    pHead = pHead->pLeft;
  
  return pHead;
}

/* 
 * 测试代码
 */
void PrintDoubleLinkedList(BinaryTreeNode* pHead)
{
  BinaryTreeNode* pNode = pHead;

  printf("left to right: ");
  while(pNode != nullptr)
  {
      printf("%.2lf->", pNode->mValue);
      if(pNode->pRight == nullptr)
        break;
      pNode = pNode->pRight;
  }

  printf("\nright to left: ");
  while(pNode != nullptr)
  {
      printf("%.2lf->", pNode->mValue);
      if(pNode->pLeft == nullptr)
        break;
      pNode = pNode->pLeft;
  }
  printf("\n");
}

void DestroyList(BinaryTreeNode* pHead)
{
  BinaryTreeNode* pNode = pHead;
  while(pNode != nullptr)
  {
      BinaryTreeNode* pNext = pNode->pRight;

      delete pNode;
      pNode = pNext;
  }
}

void Test(const char* testName, BinaryTreeNode* pRoot)
{
  if(testName != nullptr)
      printf("%s begins: ", testName);

  print_tree(pRoot);
  printf("\n");

  BinaryTreeNode* pHead = convert_bst_recursively(pRoot);

  PrintDoubleLinkedList(pHead);
}

//            10
//         /      \
//        6        14
//       /\        /\
//      4  8     12  16
void Test1()
{
  BinaryTreeNode* pNode10 = create_node(10);
  BinaryTreeNode* pNode6 = create_node(6);
  BinaryTreeNode* pNode14 = create_node(14);
  BinaryTreeNode* pNode4 = create_node(4);
  BinaryTreeNode* pNode8 = create_node(8);
  BinaryTreeNode* pNode12 = create_node(12);
  BinaryTreeNode* pNode16 = create_node(16);

  connect_node(pNode10, pNode6, pNode14);
  connect_node(pNode6, pNode4, pNode8);
  connect_node(pNode14, pNode12, pNode16);

  Test("Test1", pNode10);

  DestroyList(pNode4);
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
void Test2()
{
  BinaryTreeNode* pNode5 = create_node(5);
  BinaryTreeNode* pNode4 = create_node(4);
  BinaryTreeNode* pNode3 = create_node(3);
  BinaryTreeNode* pNode2 = create_node(2);
  BinaryTreeNode* pNode1 = create_node(1);

  connect_node(pNode5, pNode4, nullptr);
  connect_node(pNode4, pNode3, nullptr);
  connect_node(pNode3, pNode2, nullptr);
  connect_node(pNode2, pNode1, nullptr);

  Test("Test2", pNode5);

  DestroyList(pNode1);
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
void Test3()
{
  BinaryTreeNode* pNode1 = create_node(1);
  BinaryTreeNode* pNode2 = create_node(2);
  BinaryTreeNode* pNode3 = create_node(3);
  BinaryTreeNode* pNode4 = create_node(4);
  BinaryTreeNode* pNode5 = create_node(5);

  connect_node(pNode1, nullptr, pNode2);
  connect_node(pNode2, nullptr, pNode3);
  connect_node(pNode3, nullptr, pNode4);
  connect_node(pNode4, nullptr, pNode5);

  Test("Test3", pNode1);

  DestroyList(pNode1);
}

// 树中只有1个结点
void Test4()
{
  BinaryTreeNode* pNode1 = create_node(1);
  Test("Test4", pNode1);

  DestroyList(pNode1);
}

// 树中没有结点
void Test5()
{
  Test("Test5", nullptr);
}

int main(int argc, char* argv[])
{
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();

  return 0;
}
