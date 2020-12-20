'''
  面试题26：树的子结构
  题目：输入两棵二叉树A和B，判断B是不是A的子结构。
'''
class BinaryTreeNode(object):
  def __init__(self, value):
    self.value = value
    self.left = None
    self.right = None

def is_subtree(root1, root2):
  '''
  递归遍历root1，并逐步判断是否包含root2
  '''
  # 判断输入有效
  if not root1 or not root2:
    return False

  if check_subtree(root1, root2):
    return True
  
  return is_subtree(root1.left, root2) or is_subtree(root1.right, root2)

def check_subtree(root1, root2):
  '''
  递归判断，root2包含在root1中
  '''
  if not root2:
    return True
  
  if not root1:
    return False
  
  if root1.value == root2.value:
    return check_subtree(root1.left, root2.left) and \
      check_subtree(root1.right, root2.right)

  return False

if __name__ == "__main__":
  '''
  测试用例，树中结点含有分叉，树B不是树A的子结构
                  8                8
              /       \           / \
             8         7         9   2
           /   \
          9     3
               / \
              4   7
  '''
  node1 = BinaryTreeNode(8)
  node2 = BinaryTreeNode(8)
  node3 = BinaryTreeNode(7)
  node4 = BinaryTreeNode(9)
  node5 = BinaryTreeNode(3)
  node6 = BinaryTreeNode(4)
  node7 = BinaryTreeNode(7)
  
  node1.left, node1.right = node2, node3
  node2.left, node2.right = node4, node5
  node5.left, node5.right = node6, node7
  
  node8 = BinaryTreeNode(8)
  node9 = BinaryTreeNode(9)
  node10 = BinaryTreeNode(2)

  node8.left, node8.right = node9, node10
  
  if not is_subtree(node1, node8):
    print("passed.")
  else:
    print("failed.")

  node10.value = 3
  if is_subtree(node1, node8):
    print("passed.")
  else:
    print("failed.")