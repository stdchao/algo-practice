'''
  面试题8：二叉树的下一个结点
  题目：给定一棵二叉树和其中的一个结点，如何找出中序遍历顺序的下一个结点？
  树中的结点除了有两个分别指向左右子结点的指针以外，还有一个指向父结点的指针。
'''
class BinaryTreeNode(object):
  def __init__(self, value):
    self.value = value
    self.parent = None
    self.left = None
    self.right = None

'''
辅助函数
'''
def connect_node(parent, left, right):
  # 连接结点
  if not parent:
    return
  
  parent.left = left
  if left:
    left.parent = parent

  parent.right = right
  if right:
    right.parent = parent

def print_binary_tree(root):
  # 中序遍历
  if not root:
    return
  
  print_binary_tree(root.left)
  print(root.value, end="\t")
  print_binary_tree(root.right)

def get_next(node):
  # 判断输入有效
  if not node:
    return
  
  next = None
  if node.right:
    # 算法: s1.如存在右子树，则寻找右子树的最左叶子结点
    current = node.right
    while current.left != None:
      current = current.left
    next = current

  elif node.parent:
    # 算法: s2.不存在右子树，则判断结点是其父结点的左子树还是右子树
    current = node
    parent = current.parent
    while parent != None and current == parent.right:
      current = parent
      parent = current.parent
    next = parent

  return next

if __name__ == "__main__":
  '''
  测试用例

  /        a
  /   b         c
  /d     e    f   g
  /     h  i
  '''
  node_a = BinaryTreeNode('a')
  node_b = BinaryTreeNode('b')
  node_c = BinaryTreeNode('c')
  node_d = BinaryTreeNode('d')
  node_e = BinaryTreeNode('e')
  node_f = BinaryTreeNode('f')
  node_g = BinaryTreeNode('g')
  node_h = BinaryTreeNode('h')
  node_i = BinaryTreeNode('i')

  connect_node(node_a, node_b, node_c)
  connect_node(node_b, node_d, node_e)
  connect_node(node_e, node_h, node_i)
  connect_node(node_c, node_f, node_g)

  print_binary_tree(node_a)
  print("\n")

  print('node a next is node ', get_next(node_a).value)
  print('node b next is node ', get_next(node_b).value)
  print('node c next is node ', get_next(node_c).value)
  print('node d next is node ', get_next(node_d).value)
  print('node e next is node ', get_next(node_e).value)
  print('node f next is node ', get_next(node_f).value)
  print('node g next is node ', get_next(node_g))
  print('node h next is node ', get_next(node_h).value)
  print('node i next is node ', get_next(node_i).value)
