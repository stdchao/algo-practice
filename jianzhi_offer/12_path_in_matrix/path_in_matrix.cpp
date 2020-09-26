/*
 * 面试题12：矩阵中的路径
 * 题目：请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有
 * 字符的路径。路径可以从矩阵中任意一格开始，每一步可以在矩阵中向左、右、
 * 上、下移动一格。如果一条路径经过了矩阵的某一格，那么该路径不能再次进入
 * 该格子。例如在下面的3×4的矩阵中包含一条字符串“bfce”的路径（路径中的字
 * 母用下划线标出）。但矩阵中不包含字符串“abfb”的路径，因为字符串的第一个
 * 字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入这个格子。
 * 
 * A B T G
 * C F C S
 * J D E H
 */
#include <iostream>
#include <cstdio>
using namespace std;

// 函数声明
bool has_path_core(const char* matrix, int rows, int cols, const char* str,\
  int row, int col, int& pathLength, bool* visited);

/*
 * 参数：
 *  matrix 二维字符数组
 *  rows  行数
 *  cols  列数
 *  str 字符数组
 * 返回值：
 *  true 存在路径
 *  false 不存在路径
 * 复杂度：
 *  时间：
 *  空间：
 */
bool has_path(const char* matrix, int rows, int cols, const char* str){
  // 判断输入有效
  if(matrix == nullptr || rows < 1 || cols < 1 || str == nullptr)
    return false;

  // 标记已走过路径
  bool* visited = new bool[rows * cols]();
  
  int pathLength = 0;
  for(int row=0; row < rows; row++){
    for(int col=0; col < cols; col++){
      if(has_path_core(matrix, rows, cols, str, row, col, pathLength, visited))
        return true;
    }
  }

  // 释放内存
  delete[] visited;
  return false;
}

// 回溯法：遍历二维矩阵，递归实现
bool has_path_core(const char* matrix, int rows, int cols, const char* str, \
  int row, int col, int& pathLength, bool* visited){
  // 递归结束条件
  if(str[pathLength] == '\0')
    return true;

  bool hasPath = false;
  if(row >= 0 && row < rows && col >=0 && col < cols && \
    matrix[row * cols + col] == str[pathLength] && \
    !visited[row * cols + col]){
    ++ pathLength;
    visited[row * cols + col] = true;

    hasPath = has_path_core(matrix, rows, cols, str, row, col-1, pathLength, visited) ||\
      has_path_core(matrix, rows, cols, str, row-1, col, pathLength, visited) ||\
      has_path_core(matrix, rows, cols, str, row, col+1, pathLength, visited)||\
      has_path_core(matrix, rows, cols, str, row+1, col, pathLength, visited);
    
    // 回溯条件
    if(!hasPath){
      --pathLength;
      visited[row * cols + col] = false;
    }
  }

  return hasPath;
}

/*
 * 测试代码
 */
void Test(const char* testName, const char* matrix, int rows, int cols, \
  const char* str, bool expected){
  if(testName != nullptr)
    printf("%s begins: ", testName);

  if(has_path(matrix, rows, cols, str) == expected)
    printf("passed.\n");
  else
    printf("failed.\n");
}

/* 
 * 测试用例
 * //ABTG
 * //CFCS
 * //JDEH
 *
 * //BFCE
 */
void Test1(){
  const char* matrix = "ABTGCFCSJDEH";
  const char* str = "BFCE";
  Test("test1", matrix, 3, 4, str, true);
}

//ABCE
//SFCS
//ADEE

//SEE
void Test2()
{
    const char* matrix = "ABCESFCSADEE";
    const char* str = "SEE";

    Test("Test2", (const char*) matrix, 3, 4, str, true);
}

//ABTG
//CFCS
//JDEH

//ABFB
void Test3()
{
    const char* matrix = "ABTGCFCSJDEH";
    const char* str = "ABFB";

    Test("Test3", (const char*) matrix, 3, 4, str, false);
}

//ABCEHJIG
//SFCSLOPQ
//ADEEMNOE
//ADIDEJFM
//VCEIFGGS

//SLHECCEIDEJFGGFIE
void Test4()
{
    const char* matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
    const char* str = "SLHECCEIDEJFGGFIE";

    Test("Test4", (const char*) matrix, 5, 8, str, true);
}

//ABCEHJIG
//SFCSLOPQ
//ADEEMNOE
//ADIDEJFM
//VCEIFGGS

//SGGFIECVAASABCEHJIGQEM
void Test5()
{
    const char* matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
    const char* str = "SGGFIECVAASABCEHJIGQEM";

    Test("Test5", (const char*) matrix, 5, 8, str, true);
}

//ABCEHJIG
//SFCSLOPQ
//ADEEMNOE
//ADIDEJFM
//VCEIFGGS

//SGGFIECVAASABCEEJIGOEM
void Test6()
{
    const char* matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
    const char* str = "SGGFIECVAASABCEEJIGOEM";

    Test("Test6", (const char*) matrix, 5, 8, str, false);
}

//ABCEHJIG
//SFCSLOPQ
//ADEEMNOE
//ADIDEJFM
//VCEIFGGS

//SGGFIECVAASABCEHJIGQEMS
void Test7()
{
    const char* matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
    const char* str = "SGGFIECVAASABCEHJIGQEMS";

    Test("Test7", (const char*) matrix, 5, 8, str, false);
}

//AAAA
//AAAA
//AAAA

//AAAAAAAAAAAA
void Test8()
{
    const char* matrix = "AAAAAAAAAAAA";
    const char* str = "AAAAAAAAAAAA";

    Test("Test8", (const char*) matrix, 3, 4, str, true);
}

//AAAA
//AAAA
//AAAA

//AAAAAAAAAAAAA
void Test9()
{
    const char* matrix = "AAAAAAAAAAAA";
    const char* str = "AAAAAAAAAAAAA";

    Test("Test9", (const char*) matrix, 3, 4, str, false);
}

//A

//A
void Test10()
{
    const char* matrix = "A";
    const char* str = "A";

    Test("Test10", (const char*) matrix, 1, 1, str, true);
}

//A

//B
void Test11()
{
    const char* matrix = "A";
    const char* str = "B";

    Test("Test11", (const char*) matrix, 1, 1, str, false);
}

void Test12()
{
    Test("Test12", nullptr, 0, 0, nullptr, false);
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
    Test8();
    Test9();
    Test10();
    Test11();
    Test12();

    return 0;
}
