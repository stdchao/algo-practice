/*
 * 面试题19：正则表达式匹配
 * 题目：请实现一个函数用来匹配包含'.'和'*'的正则表达式。模式中的字符'.'
 * 表示任意一个字符，而'*'表示它前面的字符可以出现任意次（含0次）。在本题
 * 中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"
 * 和"ab*ac*a"匹配，但与"aa.a"及"ab*a"均不匹配。
 */
#include <iostream>
#include <cstdio>
#include <cstring>
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
    }
    return regular_match_core(str, pattern+2);

  }else{
    if(*str == *pattern || (*str != '\0' && *pattern == '.')){
      return regular_match_core(str+1, pattern+1);
    }
    return false;
  }
}

/* 
 * Solution 动态规划，实现自底向上的正则匹配
 * dp[i][j] 代表的是长度i的str与长度j的ptn是否匹配
 * p[j-1] == '*'
 * -> p[j-2] == s[i-1] or p[j-2] == '.' -> dp[i][j] = dp[i][j-2] 0个
 *                          || dp[i-1][j-2] 1个|| dp[i-1][j] 多个
 *                                      -> dp[i][j] = dp[i][j-2]
 * p[j-1] != '*'
 * -> p[j-1] == s[i-1] or p[j-1] == '.' -> dp[i][j] = dp[i-1][j-1]
 *                                      -> dp[i][j] = false
 * 
 */
bool regular_match_dp(const char* str, const char* pattern){
  // 判断输入有效
  if(str == nullptr || pattern == nullptr)
    return false;

  int size_str = strlen(str); // 字符串长度，不计入'\0'
  int size_ptn = strlen(pattern);
  bool dp[size_str+1][size_ptn+1]; // dp[i][j] 代表的是长度i的str与长度j的ptn是否匹配
  memset(dp, false, sizeof(dp));
  dp[0][0] = true; // 空字符串与空模式，匹配成功

  for(int i = 0; i <= size_str; i++){ // 从空字符开始，为了'.*'这样的模式
    for(int j = 1; j <= size_ptn; j++){ // 从长度为1开始，因为字符不为空，模式为空，必然不匹配
      if(i == 0 && j == 1){ // 字符串为空，模式串长度为1
        dp[i][j] = false;
      }
      
      if(i > 0 && j == 1){ // 字符串不为空，模式串长度为1
        if(pattern[j-1] == str[i-1] || pattern[j] == '.'){
          dp[i][j] = dp[i-1][j-1];
        }else{
          dp[i][j] = false;
        }
      }

      if(i > 0 && j > 1 && pattern[j-1] == '*'){ // 字符串不为空，模式串长度大于1
        if(pattern[j-2] == str[i-1] || pattern[j-2] == '.'){
          dp[i][j] = dp[i][j-2] || dp[i-1][j-2] || dp[i-1][j];
        }else{
          dp[i][j] = dp[i][j-2];
        }
      }else{
        if(pattern[j-1] == str[i] || pattern[j-1] == '.'){
          dp[i][j] = dp[i-1][j-1];
        }else{
          dp[i][j] = false;
        }
      }
    }
  }

  return dp[size_str][size_ptn];
}


/*
 * 测试代码
 */
void Test(const char* testName, const char* string, const char* pattern, bool expected)
{
  if(testName != nullptr)
    printf("%s begins: ", testName);

  if(regular_match_dp(string, pattern) == expected)
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

  Test("test31", "", "*", false);
  return 0;
}



