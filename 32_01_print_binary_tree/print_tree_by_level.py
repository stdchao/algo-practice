'''
  面试题32（一）：不分行从上往下打印二叉树
  题目：从上往下打印出二叉树的每个结点，同一层的结点按照从左到右的顺序打印。
'''
class BinaryTreeNode(object):
  def __init__(self, value):
    self.value = value
    self.left = None
    self.right = None

def print_tree_by_level(root):
  '''
  利用collection.deque队列的先进先出特性，实现二叉树的层次遍历
  '''
  if not root:
    return
  
  from collections import deque
  deque_tree = deque()
  deque_tree.append(root)

  print("the tree is: ")
  while deque_tree:
    node = deque_tree.popleft()
    print(node.value, end=' ')

    if node.left:
      deque_tree.append(node.left)
    
    if node.right:
      deque_tree.append(node.right)
  print("")

if __name__ == "__main__":
  '''
  测试用例
        8
    4     12
  1   6  10  14
  '''
  node8 = BinaryTreeNode(8)
  node4 = BinaryTreeNode(4)
  node12 = BinaryTreeNode(12)
  node1 = BinaryTreeNode(1)
  node6 = BinaryTreeNode(6)
  node10 = BinaryTreeNode(10)
  node14 = BinaryTreeNode(14)

  node8.left, node8.right = node4, node12
  node4.left, node4.right = node1, node6
  node12.left, node12.right = node10, node14

  print_tree_by_level(node8)
  