/*
 * 面试题19：正则表达式匹配
 * 题目：请实现一个函数用来匹配包含'.'和'*'的正则表达式。模式中的字符'.'
 * 表示任意一个字符，而'*'表示它前面的字符可以出现任意次（含0次）。在本题
 * 中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"
 * 和"ab*ac*a"匹配，但与"aa.a"及"ab*a"均不匹配。
 */
#include <iostream>
#include <cstdio>
using namespace std;

/*
 * Solution 有限状态机FSM，实现字符串与正则式匹配
 * 1. 若str与pattern同为'\0'，即匹配成功; 若str不为'\0', pattern为'\0'，即匹配失败
 * 2. 若pattern+1为'*', 则有两种情况
 * 2.1 若str与pattern相同, 或pattern为'.', 则进入下一个状态(str+1, pattern+2), 
 *  或者保持当前状态(str+1, pattern), 或者忽略当前状态(str, pattern+2)
 * 2.2 否则, 直接忽略当前状态(str, pattern+2)
 * 3. 若pattern+1不为'*', 也有两种情况
 * 3.1 若str与pattern相同，或pattern为'.', 则进入下一个状态(str+1, pattern+1),
 * 3.2 否则，即匹配失败
 */
bool regular_match_core(const char* str, const char* pattern);

bool regular_match(const char* str, const char* pattern){
  // 判断输入有效
  if(str == nullptr || pattern == nullptr)
    return false;
  
  return regular_match_core(str, pattern);
}

bool regular_match_core(const char* str, const char* pattern){
  // 递归结束条件
  if(*str == '\0' && *pattern == '\0')
    return true;

  if(*str != '\0' && *pattern == '\0')
    return false;

  // 判断pattern+1是否为*
  if(*(pattern + 1) == '*'){
    if(*str == *pattern || (*str != '\0' && *pattern == '.')){
      return regular_match_core(str+1, pattern+2) ||
        regular_match_core(str+1, pattern) || regular_match_core(str, pattern+2);
    }else{
      return regular_match_core(str, pattern+2);
    }
  }else{
    if(*str == *pattern || (*str != '\0' && *pattern == '.')){
      return regular_match_core(str+1, pattern+1);
    }
    return false;
  }
}

/*
 * 测试代码
 */
void Test(const char* testName, const char* string, const char* pattern, bool expected)
{
  if(testName != nullptr)
    printf("%s begins: ", testName);

  if(regular_match(string, pattern) == expected)
    printf("Passed.\n");
  else
    printf("FAILED.\n");
}

int main(int argc, char* argv[])
{
  Test("Test01", "", "", true);
  Test("Test02", "", ".*", true);
  Test("Test03", "", ".", false);
  Test("Test04", "", "c*", true);
  Test("Test05", "a", ".*", true);
  Test("Test06", "a", "a.", false);
  Test("Test07", "a", "", false);
  Test("Test08", "a", ".", true);
  Test("Test09", "a", "ab*", true);
  Test("Test10", "a", "ab*a", false);
  Test("Test11", "aa", "aa", true);
  Test("Test12", "aa", "a*", true);
  Test("Test13", "aa", ".*", true);
  Test("Test14", "aa", ".", false);
  Test("Test15", "ab", ".*", true);
  Test("Test16", "ab", ".*", true);
  Test("Test17", "aaa", "aa*", true);
  Test("Test18", "aaa", "aa.a", false);
  Test("Test19", "aaa", "a.a", true);
  Test("Test20", "aaa", ".a", false);
  Test("Test21", "aaa", "a*a", true);
  Test("Test22", "aaa", "ab*a", false);
  Test("Test23", "aaa", "ab*ac*a", true);
  Test("Test24", "aaa", "ab*a*c*a", true);
  Test("Test25", "aaa", ".*", true);
  Test("Test26", "aab", "c*a*b", true);
  Test("Test27", "aaca", "ab*a*c*a", true);
  Test("Test28", "aaba", "ab*a*c*a", false);
  Test("Test29", "bbbba", ".*a*a", true);
  Test("Test30", "bcbbabab", ".*a*a", false);

  return 0;
}



