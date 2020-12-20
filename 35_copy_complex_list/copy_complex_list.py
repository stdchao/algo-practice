'''
面试题35：复杂链表的复制
题目：请实现函数ComplexListNode* Clone(ComplexListNode* pHead)，
复制一个复杂链表。在复杂链表中，每个结点除了有一个m_pNext指针指向下一个结点外，
还有一个m_pSibling 指向链表中的任意结点或者nullptr。
'''
class ComplexListNode(object):
  def __init__(self, value):
    self.value = value
    self.next = None
    self.sibling = None

def copy_complex_list(head):
  '''
  采用深度优先遍历与哈希表结合的方法
  '''
  def dfs(head):
    if head in visited:
      return visited[head]
    
    if not head:
      return None

    copy = ComplexListNode(head.value)
    visited[head] = copy
    copy.next = dfs(head.next)
    copy.sibling = dfs(head.sibling)

    return copy
  
  visited = {}
  return dfs(head)

if __name__ == "__main__":
  # 1(3)->2(5)->3(null)->4(2)->5(null)->null
  node1 = ComplexListNode(1)
  node2 = ComplexListNode(2)
  node3 = ComplexListNode(3)
  node4 = ComplexListNode(4)
  node5 = ComplexListNode(5)

  node1.next, node1.sibling = node2, node3
  node2.next, node2.sibling = node3, node5
  node3.next, node3.sibling = node4, None
  node4.next, node4.sibling = node5, node2
  
  print("input list", end=": ")
  head = node1
  while head:
    if head.sibling:
      print("%d(%d)" % (head.value, head.sibling.value), end="->")
    else:
      print("%d(null)" % (head.value), end="->")
    head = head.next
  print("null")

  print("copy  list", end=": ")
  head2 = copy_complex_list(node1)
  while head2:
    if head2.sibling:
      print("%d(%d)" % (head2.value, head2.sibling.value), end="->")
    else:
      print("%d(null)" % (head2.value), end="->")
    head2 = head2.next
  print("null")