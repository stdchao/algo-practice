'''
  面试题32（二）：分行从上到下打印二叉树
  题目：从上到下按层打印二叉树，同一层的结点按从左到右的顺序打印，每一层打印到一行。
'''
class BinaryTreeNode(object):
  def __init__(self, value):
    self.value = value
    self.left = None
    self.right = None

def print_tree_by_line(root):
  if not root:
    print("empty tree.")
    return
  
  from collections import deque
  dequeTree = deque()
  dequeTree.append((0, root))

  res = []
  while dequeTree:
    level, node = dequeTree.popleft()
    if level >= len(res):
      # new line
      res.append([node.value])
    else:
      res[level].append(node.value)

    if node.left:
      dequeTree.append((level+1, node.left))

    if node.right:
      dequeTree.append((level+1, node.right))

  for line in res:
    print(line)

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

  print_tree_by_line(node8)
