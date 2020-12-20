'''
  面试题31：栈的压入、弹出序列
  题目：输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是
  否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1、2、3、4、
  5是某栈的压栈序列，序列4、5、3、2、1是该压栈序列对应的一个弹出序列，
  但4、3、5、1、2就不可能是该压栈序列的弹出序列。
'''
def is_pop_order(pushed, popped):
  stack = []
  idx = 0
  for num in pushed:
    stack.append(num)

    while stack and stack[-1] == popped[idx]:
      stack.pop()
      idx += 1
  
  return not stack

if __name__ == "__main__":
  pushed = [1, 2, 3, 4, 5]
  popped = [4, 5, 3, 2, 1]
  
  if is_pop_order(pushed, popped):
    print("passed.")
  else:
    print("failed.")