'''
  面试题3（二）：不修改数组找出重复的数字
  题目：在一个长度为n+1的数组里的所有数字都在1到n的范围内，所以数组中至少有一个数字是重复的。
  请找出数组中任意一个重复的数字，但不能修改输入的数组。例如，如果输入长度为8的数组
  {2, 3, 5, 4, 3, 2, 6, 7}，那么对应的输出是重复的数字2或者3。
'''

def find_duplicate(numbers):
  # 判断无效输入
  if not numbers or not len(numbers):
    return False

  # 算法：二分法确定范围，统计数组中满足范围的数字个数，判断范围内是否存在重复数字
  start, end = 1, len(numbers) - 1
  while start <= end:
    middle = ((end - start) >> 1) + start

    # 统计满足范围的数字个数
    count = 0
    for num in numbers:
      if num >= start and num <= middle:
        count += 1
    
    # 判断二分法结束
    if start == end:
      if count > 1:
        return start
      else:
        break
    
    # 判断范围内是否有重复数字，并更新范围
    if count > middle - start + 1:
      end = middle
    else:
      start = middle + 1

  # 数组无重复数字，返回false
  return False

if __name__ == "__main__":
  nums = [ 2, 3, 5, 4, 3, 2, 6, 7]
  print('find duplicate:', nums, find_duplicate(nums))