'''
  面试题27：二叉树的镜像
  题目：请完成一个函数，输入一个二叉树，该函数输出它的镜像。
'''
class BinaryTreeNode(object):
  def __init__(self, value):
    self.value = value
    self.left = None
    self.right = None

def print_tree(root):
  if not root:
    print("null", end='\t')
    return
  
  print(root.value, end="\t")
  print_tree(root.left)
  print_tree(root.right)

def mirror_recursively(root):
  if not root:
    return None
  
  root.left, root.right = root.right, root.left
  mirror_recursively(root.left)
  mirror_recursively(root.right)

  return root

def mirror_iteratively(root):
  if not root:
    return None
  
  stack = [root]
  while stack:
    node = stack.pop()
    node.left, node.right = node.right, node.left

    if node.left:
      stack.append(node.left)
    
    if node.right:
      stack.append(node.right)
    
  return root


if __name__ == "__main__":
  '''
        1
      /   \
     2     3
    / \   / \
   4   5 6   7
  '''
  node1 = BinaryTreeNode(1)
  node2 = BinaryTreeNode(2)
  node3 = BinaryTreeNode(3)
  node4 = BinaryTreeNode(4)
  node5 = BinaryTreeNode(5)
  node6 = BinaryTreeNode(6)
  node7 = BinaryTreeNode(7)

  node1.left, node1.right = node2, node3
  node2.left, node2.right = node4, node5
  node3.left, node3.right = node6, node7

  print_tree(node1)

  print('mirror iteratively:')
  node1 = mirror_iteratively(node1)
  print_tree(node1)

  print('mirror recursively:')
  node1 = mirror_recursively(node1)
  print_tree(node1)

