'''
  面试题32（三）：之字形打印二叉树
  题目：请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺
  序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，
  其他行以此类推。
'''
class BinaryTreeNode(object):
  def __init__(self, value):
    self.value = value
    self.left = None
    self.right = None

def print_tree_by_zigzag(root):
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
      res.append([node.value]) # new line
    else:
      if level & 1:
        res[level].insert(0, node.value) # 奇数层采取从前插入
      else:
        res[level].append(node.value) # 偶数层采取从后插入
    
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

  print_tree_by_zigzag(node8)
