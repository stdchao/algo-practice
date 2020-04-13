class TreeNode:
  def __init__(self, x):
    self.val = x
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
    
    res.append(node.val)
    travel(node.left)
    travel(node.right)
  
  travel(root)
  return res

def preorder_traversal(root):
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
      res.append(cur.val)
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
    res.append(node.val)
    travel(node.right)

  travel(root)
  return res

def inorder_traversal(root):
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
    res.append(cur.val)

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
    res.append(node.val)
  
  travel(root)
  return res

def postorder_traversal(root):
  '''
  二叉树的后续遍历，迭代实现:
    参考前序遍历思路，但不同的时，将左子节点压栈，迭代访问右子节点，最后结果反序
  '''
  res = []

  stack = [root]
  while stack:
    cur = stack.pop()

    while cur:
      res.append(cur.val)
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
    res[level].append(node.val)

    # 递归调用
    if node.left:
      travel(node.left, level+1)
    if node.right:
      travel(node.right, level+1)

  travel(root, 0)
  return res

def levelorder_travelsal(root):
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
    
    res[level].append(cur.val)
        
    if cur.left:
      queue.append((cur.left, level+1))
    if cur.right:
      queue.append((cur.right, level+1))
  
  return res

if __name__ == "__main__":
  root = TreeNode(1)
  root.left = TreeNode(2)
  root.right = TreeNode(3)
  root.left.left = TreeNode(4)
  root.left.right = TreeNode(5)
  root.right.left = TreeNode(6)

  # 前序遍历
  print('前序遍历，递归实现', preorder_traversal_recursive(root))
  print('前序遍历，迭代实现', preorder_traversal(root))

  # 中序遍历
  print('中序遍历，递归实现', inorder_traversal_recursive(root))
  print('中序遍历，迭代实现', inorder_traversal(root))

  # 后续遍历
  print('后续遍历，递归实现', postorder_traversal_recursive(root))
  print('后续遍历，迭代实现', postorder_traversal(root))

  # 层次遍历
  print('层次遍历，递归实现', levelorder_traversal_recursive(root))
  print('层次遍历，迭代实现', levelorder_travelsal(root))