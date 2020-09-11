'''
Leetcode 5.最长回文子串
'''
def longest_palindrome(s):
  '''
  经典动态规划
  '''
  max_len = 0
  max_start = 0
  max_end = 0

  size = len(s)

  # 初始化状态转移方程，都为False
  dp = [[False for _ in range(size)] for _ in range(size)]
  for i in range(size):
    dp[i][i] = True
  
  # 自底向上的构建[i, j]的循环方式，外层循环控制右边界，内层循环在右边界内遍历不同长度窗口
  for r in range(1, size):
    for l in range(r):
      if s[l] == s[r]:
        # [l, r] 分为2个元素，或3个及以上元素的两种情况
        if r - l == 1 or dp[l+1][r-1]:
          dp[l][r] = True
          if r - l > max_len:
            max_len = r - l
            max_start = l
            max_end = r
  
  return s[max_start:max_end+1]

if __name__ == "__main__":
  test_str = 'daadbababd'
  lgst_str = longest_palindrome(test_str)
  print("%s is a longest palindrom in %s" % (lgst_str, test_str))