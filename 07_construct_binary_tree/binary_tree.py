'''
  面试题7：重建二叉树
  题目：输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历
  和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2, 4, 7, 3, 5, 6, 8}
  和中序遍历序列{4, 7, 2, 1, 5, 3, 8, 6}，则重建出图2.6所示的二叉树并输出它的头结点。
'''
class BinaryTreeNode(object):
  def __init__(self, value):
    self.value = value
    self.left = None
    self.right = None
  
def print_binary_tree(root):
  if not root:
    return 
  
  print(root.value, end="\t")
  print_binary_tree(root.left)
  print_binary_tree(root.right)

def construct_binary_tree(preorder, inorder):
  # 判断输入有效
  if not preorder or not inorder or len(preorder) != len(inorder):
    raise Exception("input invalid.")
  
  # 算法: s1.在前序数组中找出根结点
  root = BinaryTreeNode(preorder[0])

  # 递归结束条件
  if len(preorder) == 1:
    if len(inorder) == 1 and preorder[0] == inorder[0]:
      return root
    else:
      raise Exception("input unmatch.")

  # 算法: s2.在中序数组中找到根结点
  idx = 0
  while inorder[idx]:
    if inorder[idx] == root.value:
      break
    idx += 1

  if inorder[idx] != root.value:
    raise Exception("input unmatch.")

  # 算法: s3.划分左右子树，递归调用
  left_size = idx
  if left_size > 0:
    root.left = construct_binary_tree( \
      preorder[1:left_size+1], inorder[0:left_size])
  
  right_size = len(inorder) - left_size - 1
  if right_size > 0:
    root.right = construct_binary_tree( \
      preorder[left_size+1:len(preorder)], inorder[left_size+1:len(inorder)])
  
  return root

if __name__ == "__main__":
  preorder = [1, 2, 4, 7, 3, 5, 6, 8]
  inorder = [4, 7, 2, 1, 5, 3, 8, 6]

  root = construct_binary_tree(preorder, inorder)

  print_binary_tree(root)