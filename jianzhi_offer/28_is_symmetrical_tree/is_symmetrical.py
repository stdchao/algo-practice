'''
  面试题28：对称的二叉树
  题目：请实现一个函数，用来判断一棵二叉树是不是对称的。如果一棵二叉树和
  它的镜像一样，那么它是对称的。
'''
class BinaryTreeNode(object):
  def __init__(self, value):
    self.value = value
    self.left = None
    self.right = None
  
def is_symmetrical(root):
  if not root:
    return True
  
  return is_symmetrical_core(root.left, root.right)

def is_symmetrical_core(root1, root2):
  if not root1 and not root2:
    return True
  
  if not root1 or not root2:
    return False
  
  if root1.value != root2.value:
    return False

  return is_symmetrical_core(root1.left, root2.right) and \
    is_symmetrical_core(root1.right, root2.left)

if __name__ == "__main__":
  '''
//            8
//        6      6
//       5 7    7 5
  '''
  node1 = BinaryTreeNode(8)
  node2 = BinaryTreeNode(6)
  node3 = BinaryTreeNode(6)
  node4 = BinaryTreeNode(5)
  node5 = BinaryTreeNode(7)
  node6 = BinaryTreeNode(7)
  node7 = BinaryTreeNode(5)

  node1.left, node1.right = node2, node3
  node2.left, node2.right = node4, node5
  node3.left, node3.right = node6, node7

  if is_symmetrical(node1):
    print("passed.")
  else:
    print("failed.")

  node3.value = 9
  if not is_symmetrical(node1):
    print("passed.")
  else:
    print("failed.")
