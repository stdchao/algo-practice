/*
 * 面试题30：包含min函数的栈
 * 题目：定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的min函数。
 * 在该栈中，调用min、push及pop的时间复杂度都是O(1)。
 */
 #include <cstdio>
 #include "min_in_stack.h"

 void Test(const char* testName, const StackWithMin<int>& stack, int expected){
   if(testName != nullptr)
    printf("%s begins: ", testName);
  
  if(stack.min() == expected)
    printf("passed.\n");
  else
    printf("failed.\n");
 }

 int main(int argc, char** argv){
   StackWithMin<int> stack;

   stack.push(3);
   Test("test1", stack, 3);

   stack.push(4);
   Test("test2", stack, 3);

   stack.push(2);
   Test("test3", stack, 2);

   stack.push(3);
   Test("test4", stack, 2);

   stack.pop();
   Test("test5", stack, 2);

   stack.pop();
   Test("test6", stack, 3);

   stack.pop();
   Test("test7", stack, 3);

   stack.push(0);
   Test("test8", stack, 0);

   return 0;
 }