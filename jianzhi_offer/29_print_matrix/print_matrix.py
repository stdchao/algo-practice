'''
  面试题29：顺时针打印矩阵
  题目：输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。
'''
def print_matrix(numbers):
  if not numbers or not len(numbers) or not len(numbers[0]):
    return
  
  top, bottom, left, right = 0, len(numbers)-1, 0, len(numbers[0])-1
  
  count = len(numbers) * len(numbers[0])
  while count > 0:
    # top
    for i in range(left, right+1):
      print(numbers[top][i], end='->')
      count -= 1
    top += 1

    # right
    if top > bottom:
      break
    
    for i in range(top, bottom+1):
      print(numbers[i][right], end='->')
      count -= 1
    right -= 1

    # bottom
    if left > right:
      break
    
    for i in range(right, left-1, -1):
      print(numbers[bottom][i], end='->')
      count -= 1
    bottom -= 1

    # left
    if top > bottom:
      break
    
    for i in range(bottom, top-1, -1):
      print(numbers[i][left], end='->')
      count -= 1
    left += 1
  
  print("end")

if __name__ == "__main__":
  numbers = [
    [1, 2, 3, 4, 5], 
    [6, 7, 8, 9, 10],
    [11, 12, 13, 14, 15],
    [16, 17, 18, 19, 20]
  ]
  print_matrix(numbers)

  numbers = [[1, 2, 3, 4, 5]]
  print_matrix(numbers)

  numbers = [[1], [2], [3], [4], [5]]
  print_matrix(numbers)

  numbers = [
    [1, 2, 3, 4, 5],
    [6, 7, 8, 9, 10]
  ]
  print_matrix(numbers)
