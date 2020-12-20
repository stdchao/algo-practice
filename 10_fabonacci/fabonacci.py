'''
  面试题10：斐波那契数列
  题目：写一个函数，输入n，求斐波那契（Fibonacci）数列的第n项。
'''
def fabonacci_iterative(n):
  if n == 0:
    return 0
  
  if n == 1:
    return 1
  
  previous_two = 0
  previous_one = 1
  fabonacci_res = 0
  for i in range(2, n+1):
    fabonacci_res = previous_one + previous_two
    previous_two = previous_one
    previous_one = fabonacci_res

  return fabonacci_res

if __name__ == "__main__":
  for i in range(0, 11):
    print("fabonacci ", i, " = ", fabonacci_iterative(i))

  print("fabonacci ", 40, " = ", fabonacci_iterative(40))