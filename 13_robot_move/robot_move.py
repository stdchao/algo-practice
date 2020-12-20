'''
  面试题13：机器人的运动范围
  题目：地上有一个m行n列的方格。一个机器人从坐标(0, 0)的格子开始移动，它
  每一次可以向左、右、上、下移动一格，但不能进入行坐标和列坐标的数位之和
  大于k的格子。例如，当k为18时，机器人能够进入方格(35, 37)，因为3+5+3+7=18。
  但它不能进入方格(35, 38)，因为3+5+3+8=19。请问该机器人能够到达多少个格子？
'''
def get_digit_sum(number):
  sum = 0
  while number > 0:
    sum = sum + number % 10
    number = int(number / 10)
  return sum

def move_count_core(threshold, rows, cols, row, col, visited):
  count = 0

  if row >= 0 and row < rows and col >= 0 and col < cols and \
    get_digit_sum(row) + get_digit_sum(col) <= threshold and \
    not visited[row * cols + col]:
    visited[row * cols + col] = True
    count = 1 + move_count_core(threshold, rows, cols, row, col-1, visited) + \
      move_count_core(threshold, rows, cols, row-1, col, visited) + \
      move_count_core(threshold, rows, cols, row, col+1, visited) + \
      move_count_core(threshold, rows, cols, row+1, col, visited)

  return count

def move_count(threshold, rows, cols):
  if threshold < 0 or rows <= 0 or cols <= 0:
    return 0

  visited = [0] * (rows * cols)
  return move_count_core(threshold, rows, cols, 0, 0, visited)

def test(testName, threshold, rows, cols, expected):
  print(testName, move_count(threshold, rows, cols), expected)

if __name__ == "__main__":
  # 测试用例
  test("Test1", 5, 10, 10, 21)

  # 方格多行多列
  test("Test2", 15, 20, 20, 359)

  # 方格只有一行，机器人只能到达部分方格
  test("Test3", 10, 1, 100, 29)

  # 方格只有一行，机器人能到达所有方格
  test("Test4", 10, 1, 10, 10)

  # 方格只有一列，机器人只能到达部分方格
  test("Test5", 15, 100, 1, 79)

  # 方格只有一列，机器人能到达所有方格
  test("Test6", 15, 10, 1, 10)

  # 方格只有一行一列
  test("Test7", 15, 1, 1, 1)

  # 方格只有一行一列
  test("Test8", 0, 1, 1, 1)

  # 机器人不能进入任意一个方格
  test("Test9", -10, 10, 10, 0)
