/* 
  面试题3（一）：找出数组中重复的数字
  题目：在一个长度为n的数组里的所有数字都在0到n-1的范围内。数组中某些数字是重复的，
  但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
  例如，如果输入长度为7的数组{2, 3, 1, 0, 2, 5, 3}，那么对应的输出是重复的数字2或者3。
*/
#include <iostream>
#include <cstdio>
using namespace std;

/*
 * 参数：
 *  numbers 整数数组
 *  length  数组长度
 *  duplication （输出）数组中重复数字
 * 返回值：
 *  true 输入有效，且存在重复数字
 *  false 输入无效，或不存在重复数字
 */
bool find_duplicate(int numbers[], int length, int* duplication){
  // 判断无效输入
  if(numbers == nullptr || length <= 0){
    return false;
  }

  for(int i=0; i<length; i++){
    if(numbers[i] < 0 || numbers[i] > length - 1){
      return false;
    }
  }

  // 算法：根据数组下标定位对应的元素
  for(int i =0; i<length; i++){
    while(numbers[i] != i){
      // 遇到重复元素，返回true
      if(numbers[i] == numbers[numbers[i]]){
        *duplication = numbers[i];
        return true;
      }

      // 未遇到重复元素，交换位置
      int tmp = numbers[i];
      numbers[i] = numbers[tmp];
      numbers[tmp] = tmp;
    }
  }

  // 无重复元素，返回false
  return false;
}

/*
 * 测试代码
 */

int contains(int numbers[], int length, int number){
  // 数组是否包含某数字
  for(int i=0; i<length; i++){
    if(numbers[i] == number){
      return true;
    }
  }
  return false;
}

void test(char const* testName, int numbers[], int nLength, int expected[], int eLength, bool valid){
  // 输入测试用例，判断find_duplicate是否正确
  printf("%s begins: ", testName);

  int duplication;
  bool res = find_duplicate(numbers, nLength, &duplication);

  if(res == valid){
    if(res){
      if(contains(expected, eLength, duplication)){
        printf("Passed-duplication %d found.\n", duplication);
      }else{
        printf("Failed.\n");
      } 
    }else{
      printf("Passed-no duplication or input invalid.\n");
    }
  }else{
    printf("Failed.\n");
  }
}

int main() {
  // 测试用例01: 重复数字是数组中最小的数
  char const* testName = "Test1";
  int numbers[] = { 2, 1, 3, 1, 4 };
  int duplications[] = { 1 };
  test(testName, numbers, sizeof(numbers) / sizeof(int), 
      duplications, sizeof(duplications) / sizeof(int), true);
  
  // 测试用例02: 重复数字是数组中最大的数
  char const* testName2 = "Test2";
  int numbers2[] = { 2, 4, 3, 1, 4 };
  int duplications2[] = { 4 };
  test(testName2, numbers2, sizeof(numbers2) / sizeof(int), 
      duplications2, sizeof(duplications2) / sizeof(int), true);
  
  // 测试用例03: 数组存在多个重复数字
  char const* testName3 = "Test3";
  int numbers3[] = { 2, 4, 2, 1, 4 };
  int duplications3[] = { 2, 4 };
  test(testName3, numbers3, sizeof(numbers3) / sizeof(int), 
      duplications3, sizeof(duplications3) / sizeof(int), true);

  // 测试用例04: 数组不存在重复数字
  char const* testName4 = "Test4";
  int numbers4[] = { 2, 1, 3, 0, 4 };
  int duplications4[] = { -1 };
  test(testName4, numbers4, sizeof(numbers4) / sizeof(int), 
      duplications4, sizeof(duplications4) / sizeof(int), false);

  // 测试用例05: 数组不存在重复数字(数组内数字超范围)
  char const* testName5 = "Test5";
  int numbers5[] = { 2, 1, 3, 5, 4 };
  int duplications5[] = { -1 };
  test(testName5, numbers5, sizeof(numbers5) / sizeof(int), 
      duplications5, sizeof(duplications5) / sizeof(int), false);

  // 测试用例06: 数组为空
  char const* testName6 = "Test6";
  int *numbers6 = nullptr;
  int duplications6[] = { -1 };
  test(testName6, numbers6, 0,
      duplications6, sizeof(duplications6) / sizeof(int), false);
  
  return 0;
}