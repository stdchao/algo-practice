'''
  面试题22：链表中倒数第k个结点
  题目：输入一个链表，输出该链表中倒数第k个结点。为了符合大多数人的习惯，
  本题从1开始计数，即链表的尾结点是倒数第1个结点。例如一个链表有6个结点，
  从头结点开始它们的值依次是1、2、3、4、5、6。这个链表的倒数第3个结点是
  值为4的结点。
'''
class ListNode(object):
  def __init__(self, value):
    self.value = value
    self.next = None

  def connect(self, next_node):
    self.next = next_node
  
def print_list(head_node):
  if not head_node:
    return
  
  while head_node:
    print(head_node.value, end='\t')
    head_node = head_node.next
  print("")

def find_k_node_from_end(head_node, k):
  # 判断输入有效
  if not head_node or k <= 0:
    return None
  
  # 前后双指针，初始化为头结点
  ahead_node, behind_node = head_node, head_node

  # 前指针先走k-1步，指向第k-1个结点
  while ahead_node and k > 1:
    ahead_node = ahead_node.next
    k -= 1

  # 链表长度小于k
  if not ahead_node:
    return None
  
  # 前后开始同步走，直到前指针为尾结点
  while ahead_node.next:
    ahead_node = ahead_node.next
    behind_node = behind_node.next

  return behind_node

if __name__ == "__main__":
  node1 = ListNode(1)
  node2 = ListNode(2)
  node3 = ListNode(3)
  node4 = ListNode(4)
  node5 = ListNode(5)

  node1.connect(node2)
  node2.connect(node3)
  node3.connect(node4)
  node4.connect(node5)

  head_node = node1
  print_list(head_node)
  print(2, 'node from end is', find_k_node_from_end(head_node, 2).value)
  print(1, 'node from end is', find_k_node_from_end(head_node, 1).value)
  print(5, 'node from end is', find_k_node_from_end(head_node, 5).value)
