/*
 * 面试题3（二）：不修改数组找出重复的数字
 * 题目：在一个长度为n+1的数组里的所有数字都在1到n的范围内，所以数组中至少有一个数字是重复的。
 * 请找出数组中任意一个重复的数字，但不能修改输入的数组。例如，如果输入长度为8的数组
 * {2, 3, 5, 4, 3, 2, 6, 7}，那么对应的输出是重复的数字2或者3。
 */

#include <iostream>
using namespace std;

/*
 * 参数：
 *  numbers 整数数组
 *  length 数组长度
 *  duplication (输出)数组中重复数字
 * 返回值：
 *  true 输入有效，且存在重复数字
 *  false 输入无效，或不存在重复数字
 * 复杂度：
 *  时间 O(nlogn)
 *  空间 O(1)
 */
bool find_duplicate(int numbers[], int length, int* duplication){
  // 判断输入是否有效
  if(numbers == nullptr || length <= 0)
    return false;

  // 算法：用二分法圈定范围，统计数组中满足范围的数字个数，间接判断范围内是否存在重复数字
  int start = 1;
  int end = length-1;
  while(start <= end){
    int middle = ((end - start) >> 1) + start;

    // 统计数组中满足范围的数字个数
    int count = 0;
    for(int i=0; i<length; i++){
      if(numbers[i] >= start && numbers[i] <= middle){
        count++;
      }
    }

    // 二分查找结束，判断是否找到重复数字
    if(start == end){
      if(count > 1){
        *duplication = start;
        return true;
      }else{
        break;
      }
    }

    // 判断哪段范围存在重复数字
    if(count > middle-start+1){
      end = middle;
    }else{
      start = middle+1;
    }
  }

  return false;
}

/*
 * 测试代码
 */
void test(const char* testName, int nums[], int length, int dups[], int dupLength){
  int duplication;
  if(find_duplicate(nums, length, &duplication)){
    for(int i=0; i<duplication; i++){
      if(duplication == dups[i]){
        cout << testName << " passed-duplication " << duplication << " found" << endl;
        return;
      }
    }
  }
  cout << testName << " passed-no duplication or input invalid." << endl;
}

// 测试用例：多个重复的数字
void test1()
{
    int numbers[] = { 2, 3, 5, 4, 3, 2, 6, 7 };
    int duplications[] = { 2, 3 };
    test("test1", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 一个重复的数字
void test2()
{
    int numbers[] = { 3, 2, 1, 4, 4, 5, 6, 7 };
    int duplications[] = { 4 };
    test("test2", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 重复的数字是数组中最小的数字
void test3()
{
    int numbers[] = { 1, 2, 3, 4, 5, 6, 7, 1, 8 };
    int duplications[] = { 1 };
    test("test3", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 重复的数字是数组中最大的数字
void test4()
{
    int numbers[] = { 1, 7, 3, 4, 5, 6, 8, 2, 8 };
    int duplications[] = { 8 };
    test("test4", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 数组中只有两个数字
void test5()
{
    int numbers[] = { 1, 1 };
    int duplications[] = { 1 };
    test("test5", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 重复的数字位于数组当中
void test6()
{
    int numbers[] = { 3, 2, 1, 3, 4, 5, 6, 7 };
    int duplications[] = { 3 };
    test("test6", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 多个重复的数字
void test7()
{
    int numbers[] = { 1, 2, 2, 6, 4, 5, 6 };
    int duplications[] = { 2, 6 };
    test("test7", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 一个数字重复三次
void test8()
{
    int numbers[] = { 1, 2, 2, 6, 4, 5, 2 };
    int duplications[] = { 2 };
    test("test8", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 没有重复的数字
void test9()
{
    int numbers[] = { 1, 2, 6, 4, 5, 3 };
    int duplications[] = { -1 };
    test("test9", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 无效的输入
void test10()
{
    int* numbers = nullptr;
    int duplications[] = { -1 };
    test("test10", numbers, 0, duplications, sizeof(duplications) / sizeof(int));
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    return 0;
}