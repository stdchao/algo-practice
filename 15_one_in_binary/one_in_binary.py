'''
  面试题15：二进制中1的个数
  题目：请实现一个函数，输入一个整数，输出该数二进制表示中1的个数。例如
  把9表示成二进制是1001，有2位是1。因此如果输入9，该函数输出2。
'''

def one_in_binary(number):
  # 算法：利用”做n与n-1与运算，得到n去掉最右边的1“这个性质，避免了循环n所有二进制位
  count = 0
  while number:
    count += 1
    number = (number - 1) & number
  return count

if __name__ == "__main__":
  # 输入0，期待的输出是0
  print('%#x' % 0, 0, one_in_binary(0))
  
  # 输入1，期待的输出是1
  print('%#x' % 1, 1, one_in_binary(1))

  #输入10，期待的输出是2
  print('%#x' % 10, 2, one_in_binary(10))

  #输入0x7FFFFFFF，期待的输出是31
  print('%#x' % 0x7FFFFFFF, 31, one_in_binary(0x7FFFFFFF))

  #输入0xFFFFFFFF（负数），期待的输出是32
  print('%#x' % 0xFFFFFFFF, 32, one_in_binary(0xFFFFFFFF))

  #输入0x80000000（负数），期待的输出是1
  print('%#x' % 0x80000000, 1, one_in_binary(0x80000000))