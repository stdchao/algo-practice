'''
 * 面试题12：矩阵中的路径
 * 题目：请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有
 * 字符的路径。路径可以从矩阵中任意一格开始，每一步可以在矩阵中向左、右、
 * 上、下移动一格。如果一条路径经过了矩阵的某一格，那么该路径不能再次进入
 * 该格子。例如在下面的3×4的矩阵中包含一条字符串“bfce”的路径（路径中的字
 * 母用下划线标出）。但矩阵中不包含字符串“abfb”的路径，因为字符串的第一个
 * 字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入这个格子。
 * 
 * A B T G
 * C F C S
 * J D E H
'''

def has_path_core(matrix, rows, cols, row, col, path, visited):
  '''
  回溯法：遍历矩阵寻找字符串路径
  '''
  if not path:
    return True
  
  index = row * cols + col
  if row >= 0 and row < rows and col >=0 and col < cols and \
    matrix[row][col] == path[0] and not visited[index]:
    visited[index] = True

    if has_path_core(matrix, rows, cols, row, col-1, path[1:], visited) or \
      has_path_core(matrix, rows, cols, row-1, col, path[1:], visited) or \
      has_path_core(matrix, rows, cols, row, col+1, path[1:], visited) or \
      has_path_core(matrix, rows, cols, row+1, col, path[1:], visited):
      return True
    
    visited[index] = False
  return False

def has_path(matrix, path):
  if not matrix or not len(matrix[0]) or not str:
    return False
  
  rows = len(matrix)
  cols = len(matrix[0])
  visited = [0] * (rows * cols)

  for row in range(rows):
    for col in range(cols):
      if has_path_core(matrix, rows, cols, row, col, path, visited):
        return True

  return False

if __name__ == "__main__":
  '''
  测试用例
  //ABTG
  //CFCS
  //JDEH
  '''
  matrix = [['A', 'B', 'T', 'G'], ['C', 'F', 'C', 'S'], ['J', 'D', 'E', 'H']]
  path = 'BFCE'
  if has_path(matrix, path):
    print("passed.")
  else:
    print("failed.")

  '''
  //ABCE
  //SFCS
  //ADEE
  '''
  matrix = [['A', 'B', 'C', 'E'], ['S', 'F', 'C', 'S'], ['A', 'D', 'E', 'E']]
  path = 'SEE'
  if has_path(matrix, path):
    print("passed.")
  else:
    print("failed.")

  '''
  //ABTG
  //CFCS
  //JDEH
  '''
  matrix = [['A', 'B', 'T', 'G'], ['C', 'F', 'C', 'S'], ['J', 'D', 'E', 'H']]
  path = 'ABFB'
  if has_path(matrix, path):
    print("passed.")
  else:
    print("failed.")