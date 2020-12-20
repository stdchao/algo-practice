/*
 * 面试题31：栈的压入、弹出序列
 * 题目：输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是
 * 否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1、2、3、4、
 * 5是某栈的压栈序列，序列4、5、3、2、1是该压栈序列对应的一个弹出序列，
 * 但4、3、5、1、2就不可能是该压栈序列的弹出序列。
 */
#include <cstdio>
#include <stdexcept>
#include <stack>
using namespace std;

bool is_pop_order(const int* pPush, const int* pPop, int length){
  // 判断输入有效
  if(pPush == nullptr || pPop == nullptr || length <= 0)
    throw runtime_error("input invalid.");
  
  // 算法：用辅助栈来模拟压栈和弹栈，循环压栈序列，依次压栈
  // 然后比较栈顶元素是否与弹栈序列首元素，相同则弹栈，继续比较栈顶与弹栈序列下个元素
  // 循环结束，最终若辅助栈不为空，则表示压栈序列和弹栈序列不匹配
  stack<int> stackData;
  int pushIdx = 0;
  int popIdx = 0;
  while(pushIdx < length){
    stackData.push(pPush[pushIdx++]);

    while(stackData.size() > 0 && stackData.top() == pPop[popIdx]){
      stackData.pop();
      popIdx++;
    }
  }

  if(stackData.size() == 0){
    return true;
  }

  return false;
}

/*
 * 测试代码
 */
// ====================测试代码====================
void Test(const char* testName, const int* pPush, const int* pPop, int nLength, bool expected)
{
  if(testName != nullptr)
      printf("%s begins: ", testName);

  if(is_pop_order(pPush, pPop, nLength) == expected)
      printf("Passed.\n");
  else
      printf("failed.\n");
}

void Test1()
{
  const int nLength = 5;
  int push[nLength] = {1, 2, 3, 4, 5};
  int pop[nLength] = {4, 5, 3, 2, 1};
  
  Test("Test1", push, pop, nLength, true);
}

void Test2()
{
  const int nLength = 5;
  int push[nLength] = {1, 2, 3, 4, 5};
  int pop[nLength] = {3, 5, 4, 2, 1};
  
  Test("Test2", push, pop, nLength, true);
}

void Test3()
{
  const int nLength = 5;
  int push[nLength] = {1, 2, 3, 4, 5};
  int pop[nLength] = {4, 3, 5, 1, 2};
  
  Test("Test3", push, pop, nLength, false);
}

void Test4()
{
  const int nLength = 5;
  int push[nLength] = {1, 2, 3, 4, 5};
  int pop[nLength] = {3, 5, 4, 1, 2};
  
  Test("Test4", push, pop, nLength, false);
}

// push和pop序列只有一个数字
void Test5()
{
  const int nLength = 1;
  int push[nLength] = {1};
  int pop[nLength] = {2};

  Test("Test5", push, pop, nLength, false);
}

void Test6()
{
  const int nLength = 1;
  int push[nLength] = {1};
  int pop[nLength] = {1};

  Test("Test6", push, pop, nLength, true);
}

void Test7()
{
  Test("Test7", nullptr, nullptr, 0, false);
}

int main(int argc, char* argv[])
{
  try{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
  }catch(exception &e){
    printf("%s", e.what());
  }
  

  return 0;
}
