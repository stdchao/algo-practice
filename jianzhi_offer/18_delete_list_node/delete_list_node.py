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
  算法: 将delete_node的(value, next)替换成delete_node.next的(value, next),
      然后释放delete_node.next
  时间复杂度: O(1)
  '''
  if not head_node or not delete_node:
    raise Exception("input invalid.")

  if delete_node.next:
    # 删除的不是尾结点
    node = delete_node.next
    delete_node.value = node.value
    delete_node.next = node.next
    node = None

  elif head_node == delete_node:
    # 删除的是尾结点，且也是头结点，即链表只有一个元素
    head_node = None
    delete_node = None

  else:
    # 删除的是尾结点，且链表包含至少两个元素
    node = head_node
    while node.next != delete_node:
      node = node.next
    
    if node.next == delete_node:
      node.next = None
      delete_node = None

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
  delete_list_node(head_node, node3)
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
  delete_list_node(head_node, node1)
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
  delete_list_node(head_node, node5)
  # 顺序打印
  print_list(head_node)
  print("test3 end")

def test4():
  head_node = ListNode(1)
  print_list(head_node)
  # 测试没通过，因为这里head_node只有一个元素，属于传值，不是传引用
  delete_list_node(head_node, head_node)
  print_list(head_node)
  print("test4 end")

def test5():
  delete_list_node(None, None)

if __name__ == "__main__":
  test1()
  test2()
  test3()
  test4()
  try:
    test5()
  except Exception as e:
    print("except", e)
  

  

