'''
  面试题30：包含min函数的栈
  题目：定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的min函数。
  在该栈中，调用min、push及pop的时间复杂度都是O(1)。
'''
class StackWithMin(object):
  def __init__(self):
    self.stack = []
    self.min_stack = []

  def push(self, x):
    self.stack.append(x)

    if not self.min_stack or self.min_stack[-1] > x:
      self.min_stack.append(x)
  
  def pop(self):
    assert self.stack and self.min_stack

    if self.stack.pop() == self.min_stack[-1]:
      self.min_stack.pop()
  
  def top(self):
    assert self.stack

    return self.stack[-1]

  def min(self):
    assert self.stack and self.min_stack
    
    return self.min_stack[-1]

if __name__ == "__main__":
  stack = StackWithMin()

  print(stack.push(3), stack.min(), 3)
  print(stack.push(4), stack.min(), 3)
  print(stack.push(2), stack.min(), 2)
  print(stack.push(3), stack.min(), 2)
  print(stack.pop(), stack.min(), 2)
  print(stack.pop(), stack.min(), 3)
  print(stack.pop(), stack.min(), 3)
  print(stack.push(0), stack.min(), 0)