'''
  面试题18（一）：在O(1)时间删除链表结点
  题目：给定单向链表的头指针和一个结点指针，定义一个函数在O(1)时间删除该结点。
'''

class ListNode(object):
  '''
  链表结点
  '''
  def __init__(self, value):
    self.value = value
    self.next = None

def print_list(head_node):
  '''
  顺序打印
  '''
  p_node = head_node
  while p_node != None:
    print("%d" % (p_node.value), end="\t")
    p_node = p_node.next
  print("\n")

def delete_list_node(head_node, delete_node):
  '''
  时间复杂度 O(1)
  '''
  if not head_node or not delete_list_node:
    raise Exception("input invalid.")

  # 技巧：用一个pre_head接在原链表的头部
  pre_head = ListNode(-1)
  pre_head.next = head_node

  if delete_node.next:
    # 不是尾结点
    delete_node.value = delete_node.next.value
    delete_node.next = delete_node.next.next

  else:
    # 是尾结点
    node = pre_head
    while node.next != delete_node:
      node = node.next
    
    if node.next == delete_node:
      node.next = None

  return pre_head.next

'''
测试代码
'''
def test1():
  # 创建链表 1->2->3->4->5
  node1 = ListNode(1)
  node2 = ListNode(2)
  node3 = ListNode(3)
  node4 = ListNode(4)
  node5 = ListNode(5)
  node1.next = node2
  node2.next = node3
  node3.next = node4
  node4.next = node5
  head_node = node1
  # 顺序打印
  print_list(head_node)
  # 删除结点
  head_node = delete_list_node(head_node, node3)
  # 顺序打印
  print_list(head_node)
  print("test1 end")

def test2():
  # 创建链表 1->2->3->4->5
  node1 = ListNode(1)
  node2 = ListNode(2)
  node3 = ListNode(3)
  node4 = ListNode(4)
  node5 = ListNode(5)
  node1.next = node2
  node2.next = node3
  node3.next = node4
  node4.next = node5
  head_node = node1
  # 顺序打印
  print_list(head_node)
  # 删除结点
  head_node = delete_list_node(head_node, node1)
  # 顺序打印
  print_list(head_node)
  print("test2 end")

def test3():
  # 创建链表 1->2->3->4->5
  node1 = ListNode(1)
  node2 = ListNode(2)
  node3 = ListNode(3)
  node4 = ListNode(4)
  node5 = ListNode(5)
  node1.next = node2
  node2.next = node3
  node3.next = node4
  node4.next = node5
  head_node = node1
  # 顺序打印
  print_list(head_node)
  # 删除结点
  head_node = delete_list_node(head_node, node5)
  # 顺序打印
  print_list(head_node)
  print("test3 end")

def test4():
  head_node = ListNode(1)
  print_list(head_node)
  head_node = delete_list_node(head_node, head_node)
  print_list(head_node)
  print("test4 end")

def test5():
  head_node = delete_list_node(None, None)
  print("test5 end")

if __name__ == "__main__":
  try:
    test1()
    test2()
    test3()
    test4()
    test5()
  except Exception as e:
    print("except", e)