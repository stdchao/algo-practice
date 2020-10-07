'''
  面试题21：调整数组顺序使奇数位于偶数前面
  题目：输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有
  奇数位于数组的前半部分，所有偶数位于数组的后半部分。
'''
def reorder_oddeven(numbers):
  # 判断输入有效
  if not numbers:
    return
  
  # 双指针
  begin_idx = 0
  end_idx = len(numbers) - 1
  while begin_idx < end_idx:
    # 从前往后寻找第一个偶数
    while begin_idx < end_idx and numbers[begin_idx] & 1 == 1:
      begin_idx += 1

    # 从后往前寻找第一个奇数
    while begin_idx < end_idx and numbers[end_idx] & 1 == 0:
      end_idx -= 1
    
    if begin_idx < end_idx:
      numbers[begin_idx], numbers[end_idx] = numbers[end_idx], numbers[begin_idx]

if __name__ == "__main__":
  numbers = [1, 2, 3, 4, 5, 6, 7]
  
  print("before reorder: ", numbers)
  reorder_oddeven(numbers)
  print("after reorder: ", numbers)
