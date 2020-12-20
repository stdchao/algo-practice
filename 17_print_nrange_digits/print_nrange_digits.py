'''
  面试题17：打印1到最大的n位数
  题目：输入数字n，按顺序打印出从1最大的n位十进制数。比如输入3，则
  打印出1、2、3一直到最大的3位数即999。需要考虑大数情况。
'''
def print_nrange_digits(n_digits):
  if n_digits < 0:
    return

  number_str = '0' * n_digits
  for i in range(10):
    number_str = str(i) + number_str[1:]
    print_nrange_digits_recursive(number_str, 0)

def print_nrange_digits_recursive(number_str, index):
  '''
  用递归法打印字符串
  '''
  # 递归结束条件
  if index == len(number_str) - 1:
    print_string(number_str)
    return

  for i in range(10):
    number_str = number_str[:index+1] + str(i) + number_str[index+2:]
    print_nrange_digits_recursive(number_str, index+1)

def print_string(number_str):
  '''
  打印字符串，忽略字符串前面的'0'
  '''
  is_begin_zero = True
  
  for number_c in number_str:
    if is_begin_zero and not number_c == '0':
      is_begin_zero = False
    
    if not is_begin_zero:
      print(number_c, end='')

  print("", end=' ')

if __name__ == "__main__":
  print_nrange_digits(3)