'''
  面试题23：链表中环的入口结点
  题目：一个链表中包含环，如何找出环的入口结点？例如，在图3.8的链表中，
  环的入口结点是结点3。
'''
class ListNode(object):
  def __init__(self, value):
    self.value = value
    self.next = None

def find_entry_in_loop(head_node):
  # 判断输入有效
  if not head_node:
    return None

  # 算法：用快慢指针能否相遇来判断是否有环，并找到环中某个结点
  meet_node = None

  slow_node = head_node.next
  if not slow_node:
    return None
  
  fast_node = slow_node.next
  while fast_node and slow_node:
    if fast_node == slow_node:
      meet_node = fast_node
      break
    
    slow_node = slow_node.next
    fast_node = fast_node.next
    if fast_node:
      fast_node = fast_node.next
  
  if not meet_node:
    return None
  
  # 算法：通过meet_node计算环中结点数目N
  nodes_in_loop = 1
  cur_node = meet_node
  while cur_node.next != meet_node:
    cur_node = cur_node.next
    nodes_in_loop += 1
  
  # 算法：再次用快慢指针，从头结点开始，快指针先走N步，再同步移动，直到相遇
  slow_node, fast_node = head_node, head_node

  while nodes_in_loop:
    fast_node = fast_node.next
    nodes_in_loop -= 1
  
  while slow_node != fast_node:
    slow_node = slow_node.next
    fast_node = fast_node.next
  
  return fast_node

if __name__ == "__main__":
  node1 = ListNode(1)
  entry_node = find_entry_in_loop(node1)
  print("list 1, entry_node is ", entry_node.value if entry_node else 0)

  node1.next = node1

  entry_node = find_entry_in_loop(node1)
  print("list 1->1, entry_node is ", entry_node.value if entry_node else 0)

  node2 = ListNode(2)
  node3 = ListNode(3)
  node4 = ListNode(4)
  node5 = ListNode(5)
  node1.next = node2
  node2.next = node3
  node3.next = node4
  node4.next = node5
  
  entry_node = find_entry_in_loop(node1)
  print("list 1->2->3->4->5, entry_node is ", \
    entry_node.value if entry_node else 0)

  node5.next = node3
  entry_node = find_entry_in_loop(node1)
  print("list 1->2->3->4->5->3, entry_node is ", \
    entry_node.value if entry_node else 0)

  node5.next = node5
  entry_node = find_entry_in_loop(node1)
  print("list 1->2->3->4->5->5, entry_node is ", \
    entry_node.value if entry_node else 0)

  node5.next = node1
  entry_node = find_entry_in_loop(node1)
  print("list 1->2->3->4->5->1, entry_node is ", \
    entry_node.value if entry_node else 0)

  entry_node = find_entry_in_loop(None)
  print("list None, entry_node is ", \
    entry_node.value if entry_node else 0)