'''
  面试题16：数值的整数次方
  题目：实现函数double Power(double base, int exponent)，求base的exponent
  次方。不得使用库函数，同时不需要考虑大数问题。
'''
def power(base, exponent):
  # 判断输入有效
  if base == 0. and exponent < 0:
    raise Exception("input invalid.")

  # 为了简便，先计算power(base, absExponent)
  absExponent = abs(exponent)

  # 算法：power(base, n) = power(base, n/2) * power(base, n/2) (n is even)
  # power(base, n) = power(base, n/2) * power(base, n/2) * base (n is odd)
  # 这里采用自底向上的迭代方法，也可以采用自顶向下的递归方法
  res = 1
  while absExponent:
    if absExponent & 1:
      res *= base
    base *= base
    absExponent = absExponent >> 1

  if exponent < 0:
    res = 1.0/res
  
  return res

if __name__ == "__main__":
  # 底数、指数都为正数
  print("Test1", power(2, 3), 8)

  # 底数为负数、指数为正数
  print("Test2", power(-2, 3), -8)

  #指数为负数
  print("Test3", power(2, -3), 0.125)

  # 指数为0
  print("Test4", power(2, 0), 1)

  # 底数、指数都为0
  print("Test5", power(0, 0), 1)

  # 底数为0、指数为正数
  print("Test6", power(0, 4), 0)

  # 底数为0、指数为负数
  try:
    print("Test7", power(0, -4), 0)
  except Exception as e:
    print(e)
