'''
  面试题25：合并两个排序的链表
  题目：输入两个递增排序的链表，合并这两个链表并使新链表中的结点仍然是按照递增排序的。
  例如输入图3.11中的链表1和链表2，则合并之后的升序链表如链表3所示。
'''
class ListNode(object):
  def __init__(self, value):
    self.value = value
    self.next = None
  
  def print_list(self):
    head = self
    print("list is", end=": ")
    while head:
      print(head.value, end="->")
      head = head.next
    print("null.")

def merge_sorted(head1, head2):
  # 技巧：创建一个哨兵结点作为头结点
  head = ListNode(0)
  cur = head
  while head1 and head2:
    if head1.value <= head2.value:
      cur.next = head1
      head1 = head1.next
    else:
      cur.next = head2
      head2 = head2.next
    cur = cur.next
  
  if not head1:
    cur.next = head2
  elif not head2:
    cur.next = head1
  
  return head.next

if __name__ == "__main__":
  node1 = ListNode(1)
  node2 = ListNode(3)
  node3 = ListNode(5)
  node1.next = node2
  node2.next = node3

  node4 = ListNode(2)
  node5 = ListNode(4)
  node6 = ListNode(6)
  node4.next = node5
  node5.next = node6

  node1.print_list()
  node4.print_list()

  head = merge_sorted(node1, node4)
  head.print_list()
  