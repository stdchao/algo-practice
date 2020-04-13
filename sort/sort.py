'''
# 排序算法Python实现
# 1. 冒泡排序, 时间O(n2), 空间O(1), 占用常数内存, 稳定排序
# 2. 选择排序, 时间O(n2), 空间O(1), 占用常数内存, 不稳定排序(如5,8,5,2,9)
# 3. 插入排序, 时间O(n2), 空间O(1), 占用常数内存, 稳定排序
# 4. 希尔排序, 时间O(nlogn), 空间O(1), 占用常数内存, 不稳定排序
# 5. 归并排序, 时间O(nlogn), 空间O(n), 占用额外内存, 稳定排序
# 6. 快速排序, 时间O(nlogn), 空间O(logn), 占用额外内存, 不稳定排序
# 7. 堆排序, 时间O(nlogn), 空间O(1), 占用常数内存, 不稳定排序
# 8. 排序, 时间O(n), 空间O(1), 占用额外内存, 稳定排序
# 9. 排序, 时间O(n), 空间O(1), 占用额外内存, 稳定排序
#10. 排序, 时间O(n), 空间O(1), 占用额外内存, 稳定排序
'''

def bubble_sort(nums):
  '''
  冒泡排序(升序)
  '''
  n = len(nums)
  for i in range(1, n):
    for j in range(0, n-i):
      # 遍历数组，相邻两位比较，大的数向后冒泡
      if nums[j] > nums[j+1]:
        nums[j], nums[j+1] = nums[j+1], nums[j]
  return nums

def select_sort(nums):
  '''
  选择排序(升序)
  '''
  n = len(nums)
  for i in range(0, n-1):
    min_index = i
    for j in range(i, n):
      # 遍历数组，寻找最小值位置
      if nums[min_index] > nums[j]:
        min_index = j
    if i != min_index:
      # 将最小值交换到位置i处
      nums[i], nums[min_index] = nums[min_index], nums[i]
  return nums
  
def insert_sort(nums):
  '''
  插入排序(升序)
  '''
  n = len(nums)
  for i in range(n):
    # 遍历未排序部分
    insert_num = nums[i]
    j = i - 1
    while j >= 0 and nums[j] > insert_num:
      # 遍历排序部分，寻找插入位置
      nums[j+1] = nums[j]
      j = j - 1 
    nums[j+1] = insert_num
  return nums

def shell_sort(nums):
  '''
  希尔排序, 是插入排序的改进版。因为插入排序在小规模数据或基本有序时十分高效，希尔排序就根据增量序列，
  如{1,3,7,2*k-1}，将数据分割为若干小数据，进行插入排序，提高效率。
  '''
  n = len(nums)
  gap = n // 3
  while gap > 0:
    # 构建增量序列
    for i in range(gap, n):
      # 对gap间隔的子序列，进行插值排序
      insert_value = nums[i]
      j = i - gap
      while j >= 0 and nums[j] > insert_value:
        nums[j+gap] = nums[j]
        j = j - gap
      nums[j+gap] = insert_value
    gap = gap // 3
  return nums

def merge_sort_recusive(nums):
  '''
  归并排序，递归实现
  '''
  # 退出递归条件，序列为空或只有1个元素
  if len(nums) < 2:
    return nums
  
  # 分割序列，并调用递归
  mid = len(nums) // 2
  left, right = merge_sort(nums[0:mid]), merge_sort(nums[mid:])

  # 合并序列，并返回
  merged = []
  while left and right:
    if left[0] < right[0]:
      merged.append(left.pop(0))
    else:
      merged.append(right.pop(0))
  while left:
    merged.append(left.pop(0))
  while right:
    merged.append(right.pop(0))
  return merged

def merge_sort(nums):
  '''
  递归排序，自底向上地实现迭代
  '''
  n = len(nums)
  interval = 1
  while interval < n:
    # 子数组的长度序列[1,2,4,8,...]
    res = []
    index = 0
    while index < n:
      # 遍历数组，找到相邻的两个子数组
      left = nums[index:index+interval]
      right = nums[index+interval:index+2*interval] # 切片时允许索引溢出

      # 合并两子数组，并放入重排的数组中
      while left and right:
        if left[0] < right[0]:
          res.append(left.pop(0))
        else:
          res.append(right.pop(0))
      while left:
        res.append(left.pop(0))
      while right:
        res.append(right.pop(0))
      
      index += 2*interval

    # 赋值重排后的数组
    nums = res
    interval <<= 1

  return nums

def quick_sort_recursive(nums, left=None, right=None):
  '''
  快速排序，效率最高的排序算法
  '''
  left = 0 if left == None else left
  right = len(nums) - 1 if right == None else right

  # 退出递归条件
  if left >= right:
    return nums

  # 选取一个基准值pivot，对[left:right]做分割，
  # 使[left:partition] < pivot < [partition:right]
  pivot = left
  partition = pivot
  index = pivot + 1
  while index <= right:
    if nums[index] < nums[pivot]:
      partition += 1
      nums[partition], nums[index] = nums[index], nums[partition]
    index += 1
  nums[pivot], nums[partition] = nums[partition], nums[pivot]

  # 以partition分割数组，并递归调用
  quick_sort_recursive(nums, left, partition-1)
  quick_sort_recursive(nums, partition+1, right)
  
def quick_sort(nums):
  '''
  快速排序，迭代实现；将递归转换为迭代的一般思路，是用辅助栈来完成
  '''
  # 辅助栈，存放区间左右边界索引(left, right)
  stack = [(0, len(nums)-1)]
  while stack:
    left, right = stack.pop(-1)

    # 选基准pivot，并交换到left位置(也可直接选择left作为pivot)
    pivot = (left + right) // 2
    nums[left], nums[pivot] = nums[pivot], nums[left]
    pivot = left

    # 寻找分割partition
    partition = left
    index = left + 1
    while index <= right:
      if nums[index] < nums[pivot]:
        partition += 1
        nums[partition], nums[index] = nums[index], nums[partition]
      index += 1
    nums[partition], nums[left] = nums[left], nums[partition]

    # 将(left, partition-1), (partition+1, right)
    if left < partition - 1:
      stack.append((left, partition-1))
    if partition + 1 < right:
      stack.append((partition+1, right))
  return nums

def heapify(nums, size, i):
  '''
  堆化，下沉操作，使以i为根节点的二叉树，满足最大堆性质;
  '''
  left_child = 2*i + 1
  right_child = 2*i + 2

  # 寻找父节点，左右子节点最大的值
  largest = i
  if left_child < size and nums[largest] < nums[left_child]:
    largest = left_child
  if right_child < size and nums[largest] < nums[right_child]:
    largest = right_child
  
  if largest != i:
    nums[i], nums[largest] = nums[largest], nums[i]
    heapify(nums, size, largest)
  
def heap_sort(nums):
  '''
  堆排序
  '''
  n = len(nums)
  # 自底向上建堆
  index = n // 2
  while index >= 0:
    heapify(nums, n, index)
    index -= 1
  
  # 交换堆顶和堆尾元素，size-1，然后重排下堆
  tail = n - 1
  while tail > 0:
    nums[0], nums[tail] = nums[tail], nums[0]
    heapify(nums, tail, 0)
    tail -= 1

  return nums

def count_sort(nums):
  '''
  计数排序，
  '''
  pass

if __name__ == "__main__":
  import random
  nums = [random.randint(0, 9) for _ in range(10)]
  print('nums before:', nums)

  nums1 = nums.copy()
  bubble_sort(nums1)
  print('bubble sort:', nums1)

  nums2 = nums.copy()
  select_sort(nums2)
  print('select sort:', nums2)

  nums3 = nums.copy()
  insert_sort(nums3)
  print('insert sort:', nums3)

  nums4 = nums.copy()
  shell_sort(nums4)
  print(' shell sort:', nums4)

  nums5 = nums.copy()
  nums5 = merge_sort(nums5)
  print(' merge sort:', nums5)

  nums6 = nums.copy()
  quick_sort(nums6)
  print(' quick sort:', nums6)

  nums7 = nums.copy()
  heap_sort(nums7)
  print('  heap sort:', nums7)

  print(' nums after:', nums)