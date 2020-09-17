'''
  面试题6：从尾到头打印链表
  题目：输入一个链表的头结点，从尾到头反过来打印出每个结点的值。
'''

class ListNode(object):
  '''
  链表结点
  '''
  def __init__(self, value):
    self.value = value
    self.next = None

def print_list_in_reversed(head_node):
  # 算法：利用栈辅助
  stacks = []

  # 先遍历链表，依次压栈，直到遍历结束
  p_node = head_node
  while p_node != None:
    stacks.append(p_node)
    p_node = p_node.next
  
  # 再依次出栈，输出，直到栈空
  while stacks:
    node = stacks.pop()
    print("%d" % node.value, end="\t")

if __name__ == "__main__":
  # 创建链表 1->2->3->4->5
  zero_node = ListNode(0)
  head_node = zero_node

  for i in range(1, 6):
    head_node.next = ListNode(i)
    head_node = head_node.next
  
  head_node = zero_node.next

  # 顺序打印
  p_node = head_node
  while p_node != None:
    print("%d" % (p_node.value), end="\t")
    p_node = p_node.next
  print("\n")

  # 倒序打印
  print_list_in_reversed(head_node)
  print("\n")