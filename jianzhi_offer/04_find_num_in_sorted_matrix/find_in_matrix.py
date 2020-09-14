'''
  面试题4：二维数组中的查找
  题目：在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按
  照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个
  整数，判断数组中是否含有该整数。

  二维数组示例
  1   2   8   9
  2   4   9   12
  4   7   10  13
  6   8   11  15
'''
def find_num_in_sorted_matrix(matrix, number):
  # 判断输入有效
  if not matrix and not len(matrix) and not len(matrix[0]):
    return False

  rows = len(matrix)
  cols = len(matrix[0])

  # 算法：从左下角，或右上角开始查找，每次排除一行或一列
  row = rows - 1
  col = 0
  while row >= 0 and col < cols:
    if matrix[row][col] == number:
      return True
    elif matrix[row][col] < number:
      col += 1
    else:
      row -= 1
  
  # 数字不存在数组中，返回false
  return False

if __name__ == "__main__":
  matrix = [
    [1, 2, 8, 9],
    [2, 4, 9 , 12],
    [4, 7, 10, 13],
    [6, 8, 11, 15]
  ]
  print("find number in matrix", matrix, 7, 
    find_num_in_sorted_matrix(matrix, 7))