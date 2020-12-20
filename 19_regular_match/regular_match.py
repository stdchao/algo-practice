'''
  面试题19：正则表达式匹配
  题目：请实现一个函数用来匹配包含'.'和'*'的正则表达式。模式中的字符'.'
  表示任意一个字符，而'*'表示它前面的字符可以出现任意次（含0次）。在本题
  中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"
  和"ab*ac*a"匹配，但与"aa.a"及"ab*a"均不匹配。
'''
def regular_match(string, pattern):
  # 字符串和模式任一为None
  if string == None or pattern == None:
    return False
  
  # 字符串和模式完全相同
  if string == pattern:
    return True

  # 字符串不为空，模式为空
  if pattern == '':
    return False
  
  # 字符串为空，模式不为空
  if string == '':
    if len(pattern) >= 2 and pattern[1] == '*':
      return regular_match(string, pattern[2:])
    else:
      return False
  
  # 模式第二个字符为'*'
  if len(pattern) >=2 and pattern[1] == '*':
    if string[0] == pattern[0] or pattern[0] == '.':
      return regular_match(string[1:], pattern[2:]) or \
        regular_match(string[1:], pattern) or regular_match(string, pattern[2:])
    else:
      return regular_match(string, pattern[2:])
  else:
    if string[0] == pattern[0] or pattern[0] == '.':
      return regular_match(string[1:], pattern[1:])
    else:
      return False

def regular_match_dp(string, pattern):
  '''
  动态规划实现正则式匹配
  参考https://github.com/hhzzxx957/Jianzhi-offer_python/blob/master/problems/jianzhi19.md
  '''
  # 判断输入有效
  if string == None or pattern == None:
    return False
  
  # 帮助空字符匹配
  string, pattern = '#' + string, '#' + pattern
  size_str, size_ptn = len(string), len(pattern)
  
  # dp[i][j] 代表前i长度的字符串与前j长度的正则式是否匹配
  dp = [[False] * size_ptn for _ in range(size_str)]
  dp[0][0] = True # 空字符串和空正则式匹配成功
  
  for i in range(size_str): # 从空字符串开始，因为需要考虑为'.*'或'a*'的正则式可以匹配
    for j in range(1, size_ptn): # 从长度为1的正则式开始，因为空正则式肯定不匹配非空字符串
        # 只需要考虑使dp[i][j]=true的逻辑分支
        if i == 0: # 空字符串
          dp[i][j] = j > 1 and pattern[j] == '*' and dp[i][j-2]
        elif pattern[j] in [string[i], '.']: # 字符串非空，正则式尾部匹配
          dp[i][j] = dp[i-1][j-1]
        elif pattern[j] == '*': # 字符串非空，正则式尾部为'*'
          dp[i][j] = (j > 1 and dp[i][j-2]) or \
                     (pattern[j-1] in [string[i], '.'] and dp[i-1][j]) # *取0个或多个
  return dp[-1][-1]

def Test(name, string, pattern, expected):
  if name:
    print(name, " begins: ", end=' ')
  
  if(regular_match_dp(string, pattern) == expected):
    print("passed.")
  else:
    print("failed.")

if __name__ == "__main__":
  Test("Test01", "", "", True)
  Test("Test02", "", ".*", True)
  Test("Test03", "", ".", False)
  Test("Test04", "", "c*", True)
  Test("Test05", "a", ".*", True)
  Test("Test06", "a", "a.", False)
  Test("Test07", "a", "", False)
  Test("Test08", "a", ".", True)
  Test("Test09", "a", "ab*", True)
  Test("Test10", "a", "ab*a", False)
  Test("Test11", "aa", "aa", True)
  Test("Test12", "aa", "a*", True)
  Test("Test13", "aa", ".*", True)
  Test("Test14", "aa", ".", False)
  Test("Test15", "ab", ".*", True)
  Test("Test16", "ab", ".*", True)
  Test("Test17", "aaa", "aa*", True)
  Test("Test18", "aaa", "aa.a", False)
  Test("Test19", "aaa", "a.a", True)
  Test("Test20", "aaa", ".a", False)
  Test("Test21", "aaa", "a*a", True)
  Test("Test22", "aaa", "ab*a", False)
  Test("Test23", "aaa", "ab*ac*a", True)
  Test("Test24", "aaa", "ab*a*c*a", True)
  Test("Test25", "aaa", ".*", True)
  Test("Test26", "aab", "c*a*b", True)
  Test("Test27", "aaca", "ab*a*c*a", True)
  Test("Test28", "aaba", "ab*a*c*a", False)
  Test("Test29", "bbbba", ".*a*a", True)
  Test("Test30", "bcbbabab", ".*a*a", False)
