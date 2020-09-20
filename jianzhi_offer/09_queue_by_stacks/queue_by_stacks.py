'''
  面试题9：用两个栈实现队列
  题目：用两个栈实现一个队列。队列的声明如下，请实现它的两个函数appendTail
  和deleteHead，分别完成在队列尾部插入结点和在队列头部删除结点的功能。
'''
class CQueue(object):
  def __init__(self):
    self.stack1 = []
    self.stack2 = []
  
  def appendTail(self, value):
    self.stack1.append(value)

  def deleteHead(self):
    if not self.stack2:
      while self.stack1:
        self.stack2.append(self.stack1.pop())
    
    if not self.stack2:
      raise Exception('empty queue.')

    return self.stack2.pop()

def test(a, b):
  if a == b:
    print("passed.")
  else:
    print("failed.")

if __name__ == "__main__":
  queue = CQueue()
  
  queue.appendTail('a')
  queue.appendTail('b')
  queue.appendTail('c')

  head = queue.deleteHead()
  test(head, 'a')

  head = queue.deleteHead()
  test(head, 'b')

  queue.appendTail('d')
  head = queue.deleteHead()
  test(head, 'c')

  queue.appendTail('e')
  head = queue.deleteHead()
  test(head, 'd')

  head = queue.deleteHead()
  test(head, 'e')