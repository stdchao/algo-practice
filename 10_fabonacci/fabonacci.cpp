/*
 * 面试题10：斐波那契数列
 * 题目：写一个函数，输入n，求斐波那契（Fibonacci）数列的第n项。
 */
#include <cstdio>

long long fabonacci_recurssive(unsigned int n){
  // 递归结束条件
  if(n <= 0)
    return 0;

  if(n == 1)
    return 1;
  
  return fabonacci_recurssive(n-1) + fabonacci_recurssive(n-2);
}

long long fabonacci_iterative(unsigned int n){
  if(n <= 0)
    return 0;
  
  if(n <=1)
    return 1;

  long long previous_two = 0;
  long long previous_one = 1;
  long long fabonacci = 0;
  for(unsigned int i=2; i <= n; i++){
    fabonacci = previous_one + previous_two;

    previous_two = previous_one;
    previous_one = fabonacci;
  }

  return fabonacci;
}

/*
 * 测试代码
 */
void Test(int n, int excepted){
  if(fabonacci_recurssive(n) == excepted)
    printf("passed-fabonacci recurssive.\n");
  else
    printf("failed-fabonacci recurssive.\n");
  
  if(fabonacci_iterative(n) == excepted)
    printf("passed-fabonacci iterative.\n");
  else
    printf("failed-fabonacci iterative.\n");
}

// 测试用例
int main(int argc, char* argv[])
{
    Test(0, 0);
    Test(1, 1);
    Test(2, 1);
    Test(3, 2);
    Test(4, 3);
    Test(5, 5);
    Test(6, 8);
    Test(7, 13);
    Test(8, 21);
    Test(9, 34);
    Test(10, 55);

    Test(40, 102334155);

    return 0;
}