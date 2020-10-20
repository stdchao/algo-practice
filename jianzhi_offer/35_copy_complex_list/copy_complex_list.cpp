/*
 * 面试题35：复杂链表的复制
 * 题目：请实现函数ComplexListNode* Clone(ComplexListNode* pHead)，
 * 复制一个复杂链表。在复杂链表中，每个结点除了有一个m_pNext指针指向下一个结点外，
 * 还有一个m_pSibling 指向链表中的任意结点或者nullptr。
 */
#include <map>

/* complex list related */
struct ComplexListNode
{
  /* data */
  int mValue;
  ComplexListNode* pNext;
  ComplexListNode* pSibling;
};

ComplexListNode* create_node(int value){
  ComplexListNode* pNode = new ComplexListNode();
  pNode->mValue = value;
  pNode->pNext = nullptr;
  pNode->pSibling = nullptr;

  return pNode;
}

void build_nodes(ComplexListNode* pNode, ComplexListNode* pNext, \
  ComplexListNode* pSibling){
  if(pNode == nullptr)
    return;

  pNode->pNext = pNext;
  pNode->pSibling = pSibling;
}

void print_list(ComplexListNode* pHead){
  if(pHead == nullptr){
    printf("empty list.\n");
    return;
  }
    
  ComplexListNode* pNode = pHead;
  while(pNode != nullptr){
    if(pNode->pSibling != nullptr){
      printf("%d(%d)->", pNode->mValue, pNode->pSibling->mValue);
    }else{
      printf("%d(null)->", pNode->mValue);
    }
    pNode = pNode->pNext;
  }

  printf("\n");
}

void destroy_list(ComplexListNode* pHead){
  ComplexListNode* pNode = pHead;
  while(pNode != nullptr){
    pHead = pHead->pNext;
    delete pNode;
    pNode = pHead;
  }
}

/* Solution 利用hash_map构建原始结点和拷贝结点的<key, value>对 */
ComplexListNode* copy_list(ComplexListNode* pHead){
  if(pHead == nullptr)
    return nullptr;
  
  // 哈希表，建立<node, copy_node>键值对
  std::map<ComplexListNode*, ComplexListNode*> nodeMap;
  ComplexListNode* pNode = pHead;
  while(pNode != nullptr){
    ComplexListNode* pCopyNode = new ComplexListNode();
    pCopyNode->mValue = pNode->mValue;
    
    nodeMap[pNode] = pCopyNode;
    pNode = pNode->pNext;
  }

  // 拷贝结点的连接
  pNode = pHead;
  while(pNode != nullptr){
    nodeMap[pNode]->pNext = nodeMap[pNode->pNext];
    nodeMap[pNode]->pSibling = nodeMap[pNode->pSibling];

    pNode = pNode->pNext;
  }

  return nodeMap[pHead];
}

/* SolutionV2 将拷贝结点穿插在原链表中，最后再抽取出来 */
ComplexListNode* compy_list_v2(ComplexListNode* pHead){
  if(pHead == nullptr)
    return nullptr;
  
  // 在原链表中穿插拷贝结点 A->A'->B->B'->C->C'->null
  ComplexListNode* pNode = pHead;
  while(pNode != nullptr){
    ComplexListNode* pCopyNode = new ComplexListNode();
    pCopyNode->mValue = pNode->mValue;
    pCopyNode->pNext = pNode->pNext;

    pNode->pNext = pCopyNode;
    pNode = pCopyNode->pNext;
  }

  // 遍历新的链表，拷贝原链表中的Sibling链接
  pNode = pHead;
  while(pNode != nullptr){
    ComplexListNode* pCopyNode = pNode->pNext;

    if(pNode->pSibling != nullptr)
      pCopyNode->pSibling = pNode->pSibling->pNext;

    pNode = pCopyNode->pNext;
  }

  // 从新链表中抽出拷贝结点，形成新链表
  ComplexListNode* pCopyHead = pHead->pNext;
  pNode = pHead;
  while(pNode != nullptr){
    ComplexListNode* pCopyNode = pNode->pNext;
    pNode->pNext = pCopyNode->pNext;

    if(pNode->pNext != nullptr)
      pCopyNode->pNext = pNode->pNext->pNext;
    
    pNode = pNode->pNext;
  }

  return pCopyHead;
}

/*
 * 测试代码
 */
void Test(const char* testName, ComplexListNode* pHead){
  if(testName != nullptr)
    printf("%s begin: ", testName);
  
  printf("the original list: \n");
  print_list(pHead);

  ComplexListNode* pCopyHead = compy_list_v2(pHead);
  destroy_list(pHead);

  printf("the copy list: \n");
  print_list(pCopyHead);
}

// 测试用例
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//  |       |      /|\             /|\
//  --------+--------               |
//          -------------------------
void Test1()
{
    ComplexListNode* pNode1 = create_node(1);
    ComplexListNode* pNode2 = create_node(2);
    ComplexListNode* pNode3 = create_node(3);
    ComplexListNode* pNode4 = create_node(4);
    ComplexListNode* pNode5 = create_node(5);

    build_nodes(pNode1, pNode2, pNode3);
    build_nodes(pNode2, pNode3, pNode5);
    build_nodes(pNode3, pNode4, nullptr);
    build_nodes(pNode4, pNode5, pNode2);

    Test("Test1", pNode1);
}

// m_pSibling指向结点自身
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//         |       | /|\           /|\
//         |       | --             |
//         |------------------------|
void Test2()
{
  ComplexListNode* pNode1 = create_node(1);
  ComplexListNode* pNode2 = create_node(2);
  ComplexListNode* pNode3 = create_node(3);
  ComplexListNode* pNode4 = create_node(4);
  ComplexListNode* pNode5 = create_node(5);

  build_nodes(pNode1, pNode2, nullptr);
  build_nodes(pNode2, pNode3, pNode5);
  build_nodes(pNode3, pNode4, pNode3);
  build_nodes(pNode4, pNode5, pNode2);

  Test("Test2", pNode1);
}

// m_pSibling形成环
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//          |              /|\
//          |               |
//          |---------------|
void Test3()
{
  ComplexListNode* pNode1 = create_node(1);
  ComplexListNode* pNode2 = create_node(2);
  ComplexListNode* pNode3 = create_node(3);
  ComplexListNode* pNode4 = create_node(4);
  ComplexListNode* pNode5 = create_node(5);

  build_nodes(pNode1, pNode2, nullptr);
  build_nodes(pNode2, pNode3, pNode4);
  build_nodes(pNode3, pNode4, nullptr);
  build_nodes(pNode4, pNode5, pNode2);

  Test("Test3", pNode1);
}

// 只有一个结点
void Test4()
{
  ComplexListNode* pNode1 = create_node(1);
  build_nodes(pNode1, nullptr, pNode1);

  Test("Test4", pNode1);
}

// 鲁棒性测试
void Test5()
{
  Test("Test5", nullptr);
}


int main(int argc, char** argv){
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  return 0;
}

