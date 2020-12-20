/*
 * 面试题20：表示数值的字符串
 * 题目：请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，
 * 字符串“+100”、“5e2”、“-123”、“3.1416”及“-1E-16”都表示数值，但“12e”、
 * “1a3.14”、“1.2.3”、“+-5”及“12e+5.4”都不是
 */
#include <iostream>
#include <cstdio>
using namespace std;

bool scanUnsignedInteger(const char** str);
bool scanInteger(const char** str);

/* Solution 数字形式A.BeC 整数部分，小数部分，以及指数部分 */
bool is_number(const char* str){
  if(str == nullptr)
    return false;

  // 判断整数部分
  bool numeric = scanInteger(&str);
  
  // 判断小数部分
  if(*str == '.'){
    ++str;

    // 下面一行代码用||的原因：
    // 1. 小数可以没有整数部分，例如.123等于0.123；
    // 2. 小数点后面可以没有数字，例如233.等于233.0；
    // 3. 当然小数点前面和后面可以有数字，例如233.666
    numeric = scanUnsignedInteger(&str) || numeric;
  }

  // 判断指数部分
  if(*str == 'E' || *str == 'e'){
    ++str;

    // 下面一行代码用&&的原因：
    // 1. 当e或E前面没有数字时，整个字符串不能表示数字，例如.e1、e1；
    // 2. 当e或E后面没有整数时，整个字符串不能表示数字，例如12e、12e+5.4
    numeric = numeric && scanInteger(&str);
  }

  return numeric && *str == '\0';
  
}

/* 判断是无符号整数 */
bool scanUnsignedInteger(const char** str){
  const char* before = *str;
  while(**str != '\0' && **str >= '0' && **str <= '9')
    ++(*str);

  return *str > before;
}

/* 判断是有符号整数 */
bool scanInteger(const char** str){
  const char* before = *str;
  if(**str == '+' || **str == '-')
    ++(*str);
  return scanUnsignedInteger(str);
}

/* 
 * 测试代码 
 */
void Test(const char* testName, const char* str, bool expected){
  if(testName != nullptr)
    printf("%s begins: ", testName);

  if(is_number(str) == expected)
    printf("passed.\n");
  else
    printf("failed.\n");
}

int main(int argc, char* argv[])
{
  Test("Test1", "100", true);
  Test("Test2", "123.45e+6", true);
  Test("Test3", "+500", true);
  Test("Test4", "5e2", true);
  Test("Test5", "3.1416", true);
  Test("Test6", "600.", true);
  Test("Test7", "-.123", true);
  Test("Test8", "-1E-16", true);
  Test("Test9", "1.79769313486232E+308", true);

  printf("\n\n");

  Test("Test10", "12e", false);
  Test("Test11", "1a3.14", false);
  Test("Test12", "1+23", false);
  Test("Test13", "1.2.3", false);
  Test("Test14", "+-5", false);
  Test("Test15", "12e+5.4", false);
  Test("Test16", ".", false);
  Test("Test17", ".e1", false);
  Test("Test18", "e1", false);
  Test("Test19", "+.", false);
  Test("Test20", "", false);
  Test("Test21", nullptr, false);

  Test("Test22", "2.e10", true);
  return 0;
}