/*
 * 面试题11：旋转数组的最小数字
 * 题目：把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
 * 输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。例如数组
 * {3, 4, 5, 1, 2}为{1, 2, 3, 4, 5}的一个旋转，该数组的最小值为1。
 */
#include <cstdio>
#include <stdexcept>
using namespace std;

int min_in_array(int* numbers, int index1, int index2){
  // 按顺序遍历数组寻找最小值
  int min = numbers[index1];
  for(int i=index1+1; i<=index2; i++){
    if(min > numbers[i])
      min = numbers[i];
  }
  return min;
}

/*
 * 参数：
 *  numbers 数组指针
 *  length  数组长度
 * 返回值：
 *  min 最小值
 * 复杂度：
 *  时间 O(logn)
 *  空间 O(1)
 */
int min_in_rotated_array(int* numbers, int length){
  // 判断输入有效
  if(numbers == nullptr || length <= 0)
    throw runtime_error("input invalid.");

  // 算法: 旋转数组分为两段递增, 前段首元素(index1)大于等于后段尾元素(index2), 
  // 后段首元素为所求最小值
  int index1 = 0;
  int index2 = length - 1;

  // 初始值: 若数组未旋转，则直接返回初始值
  int indexMid = index1;

  // 算法：用二分法取数组中间数字，首先，对比前段首元素，若大则该数属于前段；
  // 若小则对比后段尾元素，若小则该数属于后段；继续二分查找
  while(numbers[index1] >= numbers[index2]){

    // 查找结束条件：前段首与后段尾相邻，则后段尾指向数组最小值
    if(index2 == index1 + 1){
      indexMid = index2;
      break;
    }

    indexMid = (index1 + index2) >> 1;
    if(numbers[index1] == numbers[index2] && numbers[indexMid] == numbers[index1])
      return min_in_array(numbers, index1, index2);

    // 缩小查找范围
    if(numbers[indexMid] >= numbers[index1])
      index1 = indexMid;
    else if(numbers[indexMid] <= numbers[index2])
      index2 = indexMid;
  }

  return numbers[indexMid];
}

/*
 * 测试代码
 */
void Test(int* numbers, int length, int expected){
  int res = 0;
  try{
    res = min_in_rotated_array(numbers, length);

    for(int i=0; i < length; i++){
      printf("%d ", numbers[i]);
    }

    if(res == expected)
      printf("passed.\n");
    else
      printf("failed.\n");

  }catch(exception e){
    if(numbers == nullptr)
      printf("passed.\n");
    else
      printf("failed.\n");
  }
}

int main(int argc, char* argv[]){
  // 测试用例: 典型输入，单调升序的数组的一个旋转
  int array1[] = {3, 4, 5, 1, 2};
  Test(array1, sizeof(array1)/sizeof(int), 1);

  // 测试用例: 有重复数字，并且重复的数字刚好是最小的数字
  int array2[] = {3, 4, 5, 1, 1, 2};
  Test(array2, sizeof(array2)/sizeof(int), 1);

  // 有重复数字，但重复的数字不是第一个数字和最后一个数字
  int array3[] = { 3, 4, 5, 1, 2, 2 };
  Test(array3, sizeof(array3) / sizeof(int), 1);

  // 有重复的数字，并且重复的数字刚好是第一个数字和最后一个数字
  int array4[] = { 1, 0, 1, 1, 1 };
  Test(array4, sizeof(array4) / sizeof(int), 0);

  // 单调升序数组，旋转0个元素，也就是单调升序数组本身
  int array5[] = { 1, 2, 3, 4, 5 };
  Test(array5, sizeof(array5) / sizeof(int), 1);

  // 数组中只有一个数字
  int array6[] = { 2 };
  Test(array6, sizeof(array6) / sizeof(int), 2);

  // 输入nullptr
  Test(nullptr, 0, 0);

  return 0;
}