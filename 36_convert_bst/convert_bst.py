'''
面试题36：二叉搜索树与双向链表
题目：输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。
要求不能创建任何新的结点，只能调整树中结点指针的指向。
'''
class BinaryTreeNode(object):
  def __init__(self, value):
    self.value = value
    self.left = None
    self.right = None

def convert_bst(root):
  def dfs(curr, head_tail):
    if not curr:
      return None
      
    # 先深度遍历左子树
    dfs(curr.left, head_tail)

    # 链接当前结点与前面结点左子树链表的尾部
    curr.left = head_tail[1]
    if head_tail[1]:
      head_tail[1].right = curr
    else:
      head_tail[0] = curr

    # 将目前链表的尾部更新为当前结点
    head_tail[1] = curr

    # 最后深度遍历右子树
    dfs(curr.right, head_tail)
  
  # 分布存储链表首结点，和目前生成链表的尾部结点
  head_tail = [None, None]
  dfs(root, head_tail)
  return head_tail[0]

if __name__ == "__main__":
  '''
  测试用例
            10
         /      \
        6        14
       /\        /\
      4  8     12  16
  '''
  node10 = BinaryTreeNode(10)
  node6 = BinaryTreeNode(6)
  node14 = BinaryTreeNode(14)
  node4 = BinaryTreeNode(4)
  node8 = BinaryTreeNode(8)
  node12 = BinaryTreeNode(12)
  node16 = BinaryTreeNode(16)

  node10.left, node10.right = node6, node14
  node6.left, node6.right = node4, node8
  node14.left, node14.right = node12, node16

  head = convert_bst(node10)
  print("left to right", end=": ")
  while head and head.right:
    print(head.value, end="->")
    head = head.right
  print(head.value)
  
  print("right to left", end=": ")
  while head and head.left:
    print(head.value, end="->")
    head = head.left
  print(head.value)
