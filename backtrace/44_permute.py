'''
Leetcode 44. 全排列
'''
def permute(nums):
  def backtrace(sol, nums):
    if not nums:
      res.append(sol)
      return

    for i in range(len(nums)):
      backtrace(sol + [nums[i]], nums[:i] + nums[i+1:])

  res = []
  backtrace([], nums)
  return res

if __name__ == "__main__":
  res = permute([1, 2, 3])
  print(res)