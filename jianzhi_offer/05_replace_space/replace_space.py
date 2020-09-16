'''
  面试题5：替换空格
  题目：请实现一个函数，把字符串中的每个空格替换成"%20"。例如输入“We are happy.”，
  则输出“We%20are%20happy.”。
'''
def replace_space(strings):
  # 判断输入有效
  if not strings:
    return False
  
  return ''.join(list(map(lambda x: x if x != ' ' else '%20', strings)))

if __name__ == "__main__":
  strings = " hello   world "
  print("replace sapce:", strings, replace_space(strings))