'''
二叉树的前中后序以及层次遍历的递归与迭代实现
'''
class BinaryTreeNode:
  def __init__(self, value):
    self.value = value
    self.left = None
    self.right = None

def preorder_traversal_recursive(root):
  '''
  二叉树的前序遍历，递归实现
  '''
  res = []

  def travel(node):
    if not node:
      return None
    
    res.append(node.value)
    travel(node.left)
    travel(node.right)
  
  travel(root)
  return res

def preorder_traversal_iterative(root):
  '''
  二叉树的前序遍历，迭代实现，用辅助栈完成:
    1. 对于每个节点，先查询其值，
    2. 然后将右子节点压栈，继续访问左子节点，重复第一步，直到左子节点为空
    3. 弹出栈顶节点，重复第一步
    4. 直到栈空
  '''
  res = []

  # 先初始化辅助栈
  stack = [root]
  while stack:
    cur = stack.pop()

    # 对每个节点，查询其值，右子节点压栈，然后继续访问左子节点，直至左子节点为空
    while cur:
      res.append(cur.value)
      if cur.right:
        stack.append(cur.right)
      cur = cur.left
  
  return res

def inorder_traversal_recursive(root):
  '''
  二叉树的中序遍历，递归实现
  '''
  res = []

  def travel(node):
    # 若树为空，直接return
    if not node:
      return None

    # 递归调用  
    travel(node.left)
    res.append(node.value)
    travel(node.right)

  travel(root)
  return res

def inorder_traversal_iterative(root):
  '''
  二叉树的中序遍历，迭代实现，用辅助栈完成:
    1. 对于每一个节点，深度遍历其左子节点，不断压栈，直到没有左子节点；
    2. 然后弹出栈顶节点，查询其值；
    3. 最后访问其右子节点，若存在则继续按照深度遍历其左子节点，重复第一步；若不存在，弹栈重复第二步。
    4. 直到栈空
  '''
  res = []
  
  cur, stack = root, []
  while cur or stack:
    # 对每个节点，采用深度优先遍历，不断对其左子节点压栈
    while cur:
      stack.append(cur)
      cur = cur.left

    # 弹出栈顶节点
    cur = stack.pop()
    res.append(cur.value)

    # 继续遍历栈顶节点的右子节点
    cur = cur.right

  return res

def postorder_traversal_recursive(root):
  '''
  二叉树的后续遍历，递归实现
  '''
  res = []

  def travel(node):
    if not node:
      return None
    
    travel(node.left)
    travel(node.right)
    res.append(node.value)
  
  travel(root)
  return res

def postorder_traversal_iterative(root):
  '''
  二叉树的后续遍历，迭代实现:
    参考前序遍历思路，但不同的时，将左子节点压栈，迭代访问右子节点，最后结果反序
  '''
  res = []

  stack = [root]
  while stack:
    cur = stack.pop()

    while cur:
      res.append(cur.value)
      if cur.left:
        stack.append(cur.left)
      cur = cur.right
  
  return res[::-1]

def levelorder_traversal_recursive(root):
  '''
  层次遍历，递归实现
  '''
  # 列表每个元素也是一个列表，存储处于同一层的所有节点
  res = []

  def travel(node, level):
    if not node:
      return None

    # 遍历新层时，添加空列表
    if len(res) == level:
      res.append([])
      
    # 当前节点放入层对应的维
    res[level].append(node.value)

    # 递归调用
    if node.left:
      travel(node.left, level+1)
    if node.right:
      travel(node.right, level+1)

  travel(root, 0)
  return res

def levelorder_travelsal_iterative(root):
  '''
  层次遍历，迭代实现，辅助队列实现:
    和递归思路完全一致
  '''
  from collections import deque

  res = []
  if not root:
    return res
  
  queue = deque([(root, 0)])
  while queue:
    cur, level = queue.popleft()
    
    if len(res) == level:
      res.append([])
    
    res[level].append(cur.value)
        
    if cur.left:
      queue.append((cur.left, level+1))
    if cur.right:
      queue.append((cur.right, level+1))
  
  return res

if __name__ == "__main__":
  '''
           10
     6          14
   4   8    12     16
  3 5 7 9  11 13 15  17
  '''
  node10 = BinaryTreeNode(10)
  node6 = BinaryTreeNode(6)
  node14 = BinaryTreeNode(14)
  node4 = BinaryTreeNode(4)
  node8 = BinaryTreeNode(8)
  node12 = BinaryTreeNode(12)
  node16 = BinaryTreeNode(16)
  node3 = BinaryTreeNode(3)
  node5 = BinaryTreeNode(5)
  node7 = BinaryTreeNode(7)
  node9 = BinaryTreeNode(9)
  node11 = BinaryTreeNode(11)
  node13 = BinaryTreeNode(13)
  node15 = BinaryTreeNode(15)
  node17 = BinaryTreeNode(17)

  node10.left, node10.right = node6, node14
  node6.left, node6.right = node4, node8
  node14.left, node14.right = node12, node16
  node4.left, node4.right = node3, node5
  node8.left, node8.right = node7, node9
  node12.left, node12.right = node11, node13
  node16.left, node16.right = node15, node17

  root = node10
  # 前序遍历
  print('前序遍历，递归实现', preorder_traversal_recursive(root))
  print('前序遍历，迭代实现', preorder_traversal_iterative(root))

  # 中序遍历
  print('中序遍历，递归实现', inorder_traversal_recursive(root))
  print('中序遍历，迭代实现', inorder_traversal_iterative(root))

  # 后续遍历
  print('后续遍历，递归实现', postorder_traversal_recursive(root))
  print('后续遍历，迭代实现', postorder_traversal_iterative(root))

  # 层次遍历
  print('层次遍历，递归实现', levelorder_traversal_recursive(root))
  print('层次遍历，迭代实现', levelorder_travelsal_iterative(root))
