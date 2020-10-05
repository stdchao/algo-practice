'''
  面试题20：表示数值的字符串
  题目：请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，
  字符串“+100”、“5e2”、“-123”、“3.1416”及“-1E-16”都表示数值，但“12e”、
  “1a3.14”、“1.2.3”、“+-5”及“12e+5.4”都不是
'''
def is_numeric(string):
  '''
  有限状态机
  '+-', 只能出现在字符串首元素，或者E/e后面
  '.', 只能出现一次，且不能出现在E/e后面
  'Ee', 只能出现一次，且其前后都需要有数字部分
  'digit', 数字部分
  '''
  # 判断输入有效
  if not string:
    return False
  
  string = string.strip()
  met_dot = met_e = met_digit = False

  for idx, char in enumerate(string):
    if char in ['+', '-']:
      if idx > 0 and string[idx-1] not in 'Ee':
        return False
    elif char == '.':
      if met_dot or met_e:
        return False
      met_dot = True
    elif char in ['E', 'e']:
      if met_e or not met_digit:
        return False
      met_e, met_digit = True, False
    elif char.isdigit():
      met_digit = True
    else:
      return False
  
  return met_digit

def Test(test, string, expected):
  print(test, is_numeric(string), expected)

if __name__ == "__main__":
  Test("Test1", "100", True)
  Test("Test2", "123.45e+6", True)
  Test("Test3", "+500", True)
  Test("Test4", "5e2", True)
  Test("Test5", "3.1416", True)
  Test("Test6", "600.", True)
  Test("Test7", "-.123", True)
  Test("Test8", "-1E-16", True)
  Test("Test9", "1.79769313486232E+308", True)

  Test("Test10", "12e", False)
  Test("Test11", "1a3.14", False)
  Test("Test12", "1+23", False)
  Test("Test13", "1.2.3", False)
  Test("Test14", "+-5", False)
  Test("Test15", "12e+5.4", False)
  Test("Test16", ".", False)
  Test("Test17", ".e1", False)
  Test("Test18", "e1", False)
  Test("Test19", "+.", False)
  Test("Test20", "", False)
  Test("Test21", None, False)

  Test("Test22", "2.e10", True)