'''
  面试题24：反转链表
  题目：定义一个函数，输入一个链表的头结点，反转该链表并输出反转后链表的头结点。
'''
class ListNode(object):
  def __init__(self, value):
    self.value = value
    self.next = None
  
def reverse_list(head_node):
  pre_node, cur_node = None, head_node
  while cur_node:
    next_node = cur_node.next
    cur_node.next = pre_node
    pre_node, cur_node = cur_node, next_node
  return pre_node

if __name__ == "__main__":
  # 创建链表
  zero_node = ListNode(0)
  head_node = zero_node

  for i in range(1, 6):
    head_node.next = ListNode(i)
    head_node = head_node.next
  
  head_node = zero_node.next

  # 打印链表
  while head_node:
    print(head_node.value, end="->")
    head_node = head_node.next
  print("null")

  # 反转链表
  head_node = zero_node.next
  head_node = reverse_list(head_node)

  # 打印链表
  while head_node:
    print(head_node.value, end="->")
    head_node = head_node.next
  print("null")