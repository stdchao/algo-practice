/*
 * 面试题21：调整数组顺序使奇数位于偶数前面
 * 题目：输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有
 * 奇数位于数组的前半部分，所有偶数位于数组的后半部分。
 */
#include <iostream>
#include <cstdio>
using namespace std;

void reorder(int* numbers, unsigned int length, bool (*func)(int));
bool is_even(int n);

/* Solution 双指针，时间复杂度O(n) */
void reorder_oddeven(int* numbers, unsigned int length){
  reorder(numbers, length, is_even);
}

void reorder(int* numbers, unsigned int length, bool (*func)(int)){
  // 判断输入有效
  if(numbers == nullptr || length == 0)
    return;
  
  int* begin = numbers;
  int* end = numbers + length - 1;
  while(begin < end){
    // 从前向后寻找第一个偶数
    while(begin < end && !func(*begin))
      begin++;

    // 从后向前寻找第一个奇数
    while(begin < end && func(*end))
      end--;

    // 置换两个数
    if(begin < end){
      int temp = *begin;
      *begin = *end;
      *end = temp;
    }
  }
}

bool is_even(int n){
  return (n & 1) == 0;
}

/*
 * 测试代码
 */
void print_array(int* numbers, unsigned int length){
  if(length == 0){
    printf("empty array.\n");
    return;
  }

  for(int i = 0; i < length; i++)
    printf("%d\t", numbers[i]);
  printf("\n");
}

void Test(const char* testName, int* numbers, int length){
  if(testName != nullptr)
    printf("%s begins: ", testName);
  
  print_array(numbers, length);
  reorder_oddeven(numbers, length);
  print_array(numbers, length);
}

// 测试用例
void Test1(){
  int numbers[] = {1, 2, 3, 4, 5, 6, 7};
  Test("Test1", numbers, sizeof(numbers)/sizeof(int));
}

void Test2()
{
  int numbers[] = {2, 4, 6, 1, 3, 5, 7};
  Test("Test2", numbers, sizeof(numbers)/sizeof(int));
}

void Test3()
{
  int numbers[] = {1, 3, 5, 7, 2, 4, 6};
  Test("Test3", numbers, sizeof(numbers)/sizeof(int));
}

void Test4()
{
  int numbers[] = {1};
  Test("Test4", numbers, sizeof(numbers)/sizeof(int));
}

void Test5()
{
  int numbers[] = {2};
  Test("Test5", numbers, sizeof(numbers)/sizeof(int));
}

void Test6()
{
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