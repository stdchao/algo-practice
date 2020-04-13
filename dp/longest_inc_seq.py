'''
# Leetcode 300. 最长递增子序列(LIS)的长度
# Leetcode 673. 最长递增子序列(LIS)的个数
'''
import sys
sys.path.append('..')

from roadmap_algo.utils.time import fn_timer

@fn_timer
def length_LIS(nums):
  '''
  动态规划，时间复杂度O(n^2)
    dp[i] 代表以nums[i]结尾的最长递增子序列的长度
    状态转移方程 dp[i] = max(dp[j] + 1 for j in range(i) if nums[i] > nums[j]）
  '''
  if not nums:
    return 0

  size = len(nums)
  # base case
  dp = [1] * size
  
  for i in range(size):
    for j in range(i):
      if nums[i] > nums[j]:
        dp[i] = max(dp[i], dp[j] + 1)

  return max(dp)

@fn_timer
def length_LIS_best(nums):
  '''
  贪心+二分查找思路，时间复杂度O(NlogN)
    保证最长递增子序列中的各位置元素始终最小
  '''
  # tail 用来存储保持各位置元素最小的LIS
  tail, res = [0] * len(nums), 0

  for num in nums:
    i, j = 0, res
    # 在tail中进行二分查找，找到当前元素num在tail中保持递增的位置
    while i < j:
      mid = (i + j) //2
      if tail[mid] < num:
        i = mid + 1
      else:
        j = mid
    # 找到位置i后，将num插入或替换
    tail[i] = num
    if j == res:
      res += 1
    #print('debug ', tail)

  return res

@fn_timer
def count_LTS(nums):
  '''
  动态规划，时间复杂度

  '''
  pass

if __name__ == "__main__":
  nums = [10,9,2,5,3,7,101,18]

  print('动态规划之最长子序列长度', length_LIS(nums))
  print('二分查找之最长子序列长度', length_LIS_best(nums))


  print('\n动态规划之最长子序列个数', count_LTS(nums))
