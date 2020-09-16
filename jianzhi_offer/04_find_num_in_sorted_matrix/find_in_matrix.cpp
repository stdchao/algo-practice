/*
 * 面试题4：二维数组中的查找
 * 题目：在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按
 * 照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个
 * 整数，判断数组中是否含有该整数。
 * 
 * 二维数组示例
 * //  1   2   8   9
 * //  2   4   9   12
 * //  4   7   10  13
 * //  6   8   11  15
 */

#include <iostream>
#include <cstdio>
using namespace std;

/*
 * 参数：
 *  matrix 二维数组指针
 *  rows  行数
 *  cols  列数
 *  number 待查找的数字
 * 返回值：
 *  true 输入有效，且数字在二维数组中
 *  false 输入无效，或数组不存在二维数组中
 * 复杂度：
 *  时间 O(logmn)
 *  空间 O(logmn)
 */
bool find_num_in_sorted_matrix(int *matrix, int rows, int cols, int number){
  // 判断输入有效
  if(matrix == nullptr || rows <= 0 || cols <= 0)
    return false;
    
  int row = 0;
  int col = cols - 1;
  // 算法：从右上角，或左下角开始查找，每次可以排除一行或一列，达到效率最大化
  while(row < rows && col >= 0 ){
    if(matrix[row * cols + col] == number){
      return true;
    }else if(matrix[row * cols + col] > number){
      --col;
    }else{
      ++row;
    }
  }
  return false;
}

/*
 * 测试代码
 */
void test(const char* testName, int* matrix, int rows, int cols, int number, bool expect){
  printf("%s begins: ", testName);
  
  bool res = find_num_in_sorted_matrix(matrix, rows, cols, number);
  if(res == expect){
    if(res){
      printf("passed-number found in matrix.\n");
    }else{
      printf("passed-input invalid or number not found.\n");
    }
  }else{
    printf("failed.\n");
  }
}

// 测试用例
//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数在数组中
void Test1()
{
    int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    test("Test1", (int*)matrix, 4, 4, 7, true);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数不在数组中
void Test2()
{
    int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    test("Test2", (int*)matrix, 4, 4, 5, false);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数是数组中最小的数字
void Test3()
{
    int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    test("Test3", (int*)matrix, 4, 4, 1, true);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数是数组中最大的数字
void Test4()
{
    int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    test("Test4", (int*)matrix, 4, 4, 15, true);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数比数组中最小的数字还小
void Test5()
{
    int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    test("Test5", (int*)matrix, 4, 4, 0, false);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数比数组中最大的数字还大
void Test6()
{
    int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    test("Test6", (int*)matrix, 4, 4, 16, false);
}

// 鲁棒性测试，输入空指针
void Test7()
{
    test("Test7", nullptr, 0, 0, 16, false);
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
    return 0;
}