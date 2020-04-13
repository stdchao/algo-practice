'''
# Leetcode 322. 零钱兑换
'''

import time
from functools import wraps

def fn_timer(function):
  @wraps(function)
  def function_timer(*args, **kwargs):
    t0 = time.time()
    result = function(*args, **kwargs)
    t1 = time.time()
    print('Running %s: %.3f seconds' % (function.__name__, t1 - t0))
    return result
  return function_timer

@fn_timer
def coin_change_recursive(coins, amount):
  '''
  暴力递归法，对于amount的问题，递归地选择一枚coin后，变成amount-coin的子问题加1
    时间复杂度为O(k^n)
  '''

  def recursive(amount):
    # base case
    if amount < 0:
      return -1
    if amount == 0:
      return 0
    
    res = float('inf')
    for coin in coins:
      # 子问题无解
      tmp = recursive(amount - coin)
      if tmp == -1:
        continue
      res = min(res, recursive(amount-coin)+1)
    # 若无解返回-1
    return res if res != float('inf') else -1
  
  return recursive(amount)

@fn_timer
def coin_change_memory(coins, amount):
  '''
  带备忘录的递归法，时间复杂度为O(kn)
  '''
  memory = [0] * (amount+1)

  def recursive(amount):
    # base case
    if amount < 0:
      return -1
    elif amount == 0:
      return 0
    elif memory[amount]:
      return memory[amount]
    
    res = float('inf')
    for coin in coins:
      tmp = recursive(amount - coin)
      # 若子问题无解
      if tmp == -1:
        continue
      res = min(res, tmp + 1)
    
    # 若问题无解，则返回-1
    memory[amount] = res if res != float('inf') else -1
    return  memory[amount]

  return recursive(amount)

@fn_timer
def coin_change_dp(coins, amount):
  '''
  动态规划法，时间复杂度为O(nk)
    状态转移方程：dp[amount] = min(dp[amount - coin] + 1 for coin in coins)
    
  '''
  if amount < 0:
    return -1
  if amount == 0:
    return 0
  
  dp = [0] * (amount+1)
  for i in range(1, amount+1):
    dp[i] = float('inf')
    for coin in coins:
      if i < coin or dp[i-coin] == -1:
        continue
      dp[i] = min(dp[i], dp[i-coin] + 1)
    dp[i] = dp[i] if dp[i] != float('inf') else -1

  return dp[amount]

if __name__ == "__main__":
  test_coins = [[1, 2, 5], [2]]
  test_amount = [13, 3]

  for coins, amount in zip(test_coins, test_amount):
    print('Test case:',coins, amount)
    print('暴力递归法', coin_change_recursive(coins, amount))
    print('带备忘录的递归法', coin_change_memory(coins, amount))
    print('动态规划法', coin_change_dp(coins, amount))
