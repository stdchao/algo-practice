'''
  面试题34：二叉树中和为某一值的路径
  题目：输入一棵二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所
  有路径。从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。
'''
class BinaryTreeNode(object):
  def __init__(self, value):
    self.value = value
    self.left = None
    self.right = None

def find_path_in_tree(root, target):
  '''
  深度优先遍历
  '''
  def dfs(root, target, path, res):
    if not root:
      return
    
    # 将当前结点加入路径，计算与目标值差距，作为新的目标值
    target -= root.value
    
    # 当该结点是叶子结点
    if not root.left and not root.right and target == 0:
      res.append(path + [root.value])
    
    # 若不是叶子结点，遍历包含该结点的所有其他路径
    dfs(root.left, target, path + [root.value], res)
    dfs(root.right, target, path + [root.value], res)
  
  res = []
  dfs(root, target, [], res)
  return res

if __name__ == "__main__":
  node10 = BinaryTreeNode(10)
  node5 = BinaryTreeNode(5)
  node12 = BinaryTreeNode(12)
  node4 = BinaryTreeNode(4)
  node7 = BinaryTreeNode(7)

  node10.left, node10.right = node5, node12
  node5.left, node5.right = node4, node7

  print("two paths of sum 22 should be found.")
  res = find_path_in_tree(node10, 22)
  print(res)