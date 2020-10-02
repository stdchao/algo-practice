'''
  面试题18（二）：删除链表中重复的结点
  题目：在一个排序的链表中，如何删除重复的结点？例如，在图3.4（a）中重复
  结点被删除之后，链表如图3.4（b）所示。
'''
class ListNode(object):
  def __init__(self, value):
    self.value = value
    self.next = None

def delete_dup_list_node(head_node):
  if not head_node:
    return

  pre_head = ListNode(-1)
  pre_head.next = head_node

  pre_node = pre_head
  while head_node:
    value = head_node.value
    next_node = head_node.next
    if next_node and next_node.value == value:
      while head_node and head_node.value == value:
        head_node = head_node.next
      
      pre_node.next = head_node
    else:
      pre_node = head_node
      head_node = next_node
  
  return pre_head.next

if __name__ == "__main__":
  node1 = ListNode(1)
  node2 = ListNode(1)
  node3 = ListNode(3)
  node4 = ListNode(3)
  node5 = ListNode(4)
  node6 = ListNode(4)
  node7 = ListNode(5)

  node1.next = node2
  node2.next = node3
  node3.next = node4
  node4.next = node5
  node5.next = node6
  node6.next = node7

  head_node = delete_dup_list_node(node1)

  while head_node:
    print(head_node.value, end=" ")
    head_node = head_node.next
  print("\n")