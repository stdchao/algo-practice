'''
# 动态规划之斐波那契数列问题
'''

import time
from functools import wraps

# 执行时间装饰器
def fn_timer(function):
  @wraps(function)
  def function_timer(*args, **kwargs):
    t0 = time.time()
    result = function(*args, **kwargs)
    t1 = time.time()
    print ("Running %s: %.3f seconds" %
        (function.__name__, t1-t0)
        )
    return result
  return function_timer

@fn_timer
def fibonacci_recursive(n):
  '''
  暴力递归法，时间复杂度O(2^n)
  '''
  if n < 1:
    return 0

  def recursive(n):
    # base case
    if n == 1 or n == 2:
      return 1
    return recursive(n-2) + recursive(n-1)

  return recursive(n)

@fn_timer
def fibonacci_memory(n):
  '''
  带备忘录的递归法，时间复杂度O(n)
  '''
  if n < 1:
    return 0

  # 备忘录
  memo = [0] * (n+1)

  def recursive(n):
    # base case
    if n == 1 or n == 2:
      return 1
    if not memo[n]:
      memo[n] = recursive(n-2) + recursive(n-1)
    return memo[n]

  return recursive(n)

@fn_timer
def fibonacci_dp(n):
  '''
  动态规划法，自底向上，时间复杂度O(n)。严格来讲不算动态规划，因为不涉及最优子结构
  '''
  if n < 1:
    return 0

  dp = [0] * (n+1)
  dp[1] = dp[2] = 1
  for i in range(3, n+1):
    dp[i] = dp[i-2] + dp[i-1]
  return dp[n]

@fn_timer
def fibonacci_best(n):
  '''
  最佳实践，在动态规划方法中，状态转移方程只跟前两个状态有关，所以不需要存储整个DP表
  '''
  if n < 1:
    return 0
  elif n < 3:
    return 1
  
  pre = cur = 1
  for _ in range(3, n+1):
    pre, cur = cur, pre + cur
  return cur

if __name__ == "__main__":
  for N in [0, 10, 30]:
    print('Test N: ', N)
    print('暴力递归法', fibonacci_recursive(N))
    print('带备忘录的递归法', fibonacci_memory(N))
    print('动态规划法', fibonacci_dp(N))
    print('最佳实践', fibonacci_best(N))
