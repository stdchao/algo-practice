/*
 * 面试题16：数值的整数次方
 * 题目：实现函数double Power(double base, int exponent)，求base的exponent
 * 次方。不得使用库函数，同时不需要考虑大数问题。
 */
#include <cstdio>
#include <stdexcept>
using namespace std;

double power_with_unsigned(double base, int exponent);

double power(double base, int exponent){
  if(base == 0.0 && exponent < 0)
    throw runtime_error("input invalid.\n");
  
  unsigned int absExponent = (unsigned int) exponent;
  if(exponent < 0){
    absExponent = (unsigned int) (-exponent);
  }

  double res = power_with_unsigned(base, absExponent);
  if(exponent < 0)
    res = 1.0 / res;
  
  return res;
}

double power_with_unsigned(double base, int exponent){
  // 算法 power(a, n) = power(a, n/2) * power(a, n/2) (n is even)
  // power(a, n) = power(a, n/2) * power(a, n/2) * a (n is odd)
  // 这里采用自顶向下的递归方法，也可以采用自底向上的迭代方法
  if(exponent == 0){
    return 1;
  }else if(exponent & 0x1){
    return base * power_with_unsigned(base, exponent-1);
  }else{
    double res = power_with_unsigned(base, exponent >> 1);
    return res * res;
  }
}

/*
 * 测试代码
 */
void Test(const char* testName, double base, int exponent, double expected)
{
  try{
    if(power(base, exponent) == expected)
      printf("%s passed.\n", testName);
    else
      printf("%s failed.\n", testName);
  }catch(exception &e){
    printf("%s except %s", testName, e.what());
  }
}

int main(int argc, char* argv[])
{
    // 底数、指数都为正数
    Test("Test1", 2, 3, 8);

    // 底数为负数、指数为正数
    Test("Test2", -2, 3, -8);

    // 指数为负数
    Test("Test3", 2, -3, 0.125);

    // 指数为0
    Test("Test4", 2, 0, 1);

    // 底数、指数都为0
    Test("Test5", 0, 0, 1);

    // 底数为0、指数为正数
    Test("Test6", 0, 4, 0);

    // 底数为0、指数为负数
    Test("Test7", 0, -4, 0);

    return 0;
}