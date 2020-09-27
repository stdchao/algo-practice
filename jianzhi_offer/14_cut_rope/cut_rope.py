'''
  面试题14：剪绳子
  题目：给你一根长度为n绳子，请把绳子剪成m段（m、n都是整数，n>1并且m≥1）。
  每段的绳子的长度记为k[0]、k[1]、……、k[m]。k[0]*k[1]*…*k[m]可能的最大乘
  积是多少？例如当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此
  时得到最大的乘积18。
'''
def cut_rope_dp(length):
  if length < 2:
    return 0
  elif length == 2:
    return 1
  elif length == 3:
    return 2
  
  products = [0] * (length + 1)
  products[1] = 1
  products[2] = 2
  products[3] = 3

  for i in range(4, length+1):
    max = 0
    for j in range(1, int(i/2)+1):
      product = products[j] * products[i-j]
      if max < product:
        max = product
    products[i] = max
  
  return products[length]

def cut_rope_gd(length):
  if length < 2:
    return 0
  elif length == 2:
    return 1
  elif length == 3:
    return 2
  
  max = 1
  while length > 4:
    max = max * 3
    length = length - 3 
  
  if length == 4:
    max = max * 4
  elif length == 3:
    max = max * 3
  elif length == 2:
    max = max * 2

  return max

if __name__ == "__main__":
  print("rope ", 1, " max product ", cut_rope_dp(1), cut_rope_gd(1), 0)
  print("rope ", 2, " max product ", cut_rope_dp(2), cut_rope_gd(2), 1)
  print("rope ", 3, " max product ", cut_rope_dp(3), cut_rope_gd(3), 2)
  print("rope ", 4, " max product ", cut_rope_dp(4), cut_rope_gd(4), 4)
  print("rope ", 5, " max product ", cut_rope_dp(5), cut_rope_gd(5), 6)
  print("rope ", 6, " max product ", cut_rope_dp(6), cut_rope_gd(6), 9)
  print("rope ", 7, " max product ", cut_rope_dp(7), cut_rope_gd(7), 12)
  print("rope ", 8, " max product ", cut_rope_dp(8), cut_rope_gd(8), 18)
  print("rope ", 9, " max product ", cut_rope_dp(9), cut_rope_gd(9), 27)
  print("rope ", 10, " max product ", cut_rope_dp(10), cut_rope_gd(10), 36)
  print("rope ", 50, " max product ", cut_rope_dp(50), cut_rope_gd(50), 86093442)
