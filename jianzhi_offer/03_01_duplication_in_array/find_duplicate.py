''' 
面试题3（一）：找出数组中重复的数字
题目：在一个长度为n的数组里的所有数字都在0到n-1的范围内。数组中某些数字是重复的，
但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
例如，如果输入长度为7的数组{2, 3, 1, 0, 2, 5, 3}，那么对应的输出是重复的数字2或者3。
'''

def find_duplicate(numbers):
  # 判断输入有效
  size = len(numbers)
  
  if size <= 0:
    return False
  
  for num in numbers:
    if num < 0 or num >= size:
      return False

  # 算法：根据数组下标定位对应元素
  for i in range(size):
    while numbers[i] != i:
      # 遇到重复元素，返回重复元素
      if numbers[i] == numbers[numbers[i]]:
        return numbers[i]
      
      # 未遇到重复元素，交换位置
      tmp = numbers[i]
      numbers[i] = numbers[tmp]
      numbers[tmp] = tmp
  
  # 无重复元素
  return False

if __name__ == "__main__":
  nums = [2, 3, 1, 0, 2, 5, 3]
  print('find duplicate:', nums, find_duplicate(nums))