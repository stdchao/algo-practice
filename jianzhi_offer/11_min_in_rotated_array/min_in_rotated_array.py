'''
  面试题11：旋转数组的最小数字
  题目：把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
  输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。例如数组
  {3, 4, 5, 1, 2}为{1, 2, 3, 4, 5}的一个旋转，该数组的最小值为1。
'''
def min_in_array(numbers):
  res = numbers[0]
  for num in numbers[1:]:
    if res > num:
      res = num
  return res

def min_in_rotated_array(numbers):
  if not numbers:
    raise Exception("input invalid.")

  # 算法：旋转数组分为两段递增，index1，index2指向首数组首位
  index1 = 0
  index2 = len(numbers) - 1
  indexMid = index1

  # 二分查找：
  while numbers[index1] >= numbers[index2]:
    # 查找结束条件
    if index1 + 1 == index2:
      indexMid = index2
      break

    indexMid = (index1 + index2) >> 1
    # 特殊情况
    if numbers[index1] == numbers[indexMid] and numbers[indexMid] == numbers[index2]:
      return min_in_array(numbers[index1:index2+1])

    # 缩小查找范围
    if numbers[indexMid] >= numbers[index1]:
      index1 = indexMid
    elif numbers[indexMid] <= numbers[index2]:
      index2 = indexMid

  return numbers[indexMid]

if __name__ == "__main__":
  nums = [3, 4, 5, 1, 2]
  print(nums, ", min: ", min_in_rotated_array(nums))

  nums = [3, 4, 5, 1, 1, 2]
  print(nums, ", min: ", min_in_rotated_array(nums))

  nums = [3, 4, 5, 1, 2, 2]
  print(nums, ", min: ", min_in_rotated_array(nums))

  nums = [1, 0, 1, 1, 1]
  print(nums, ", min: ", min_in_rotated_array(nums))

  nums = [1, 2, 3, 4, 5]
  print(nums, ", min: ", min_in_rotated_array(nums))

  nums = [2]
  print(nums, ", min: ", min_in_rotated_array(nums))

  nums = []
  try:
    print(nums, ", min: ", min_in_rotated_array(nums))
  except Exception as e:
    print(e)