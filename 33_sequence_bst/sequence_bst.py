'''
  面试题33：二叉搜索树的后序遍历序列
  题目：输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
  如果是则返回true，否则返回false。假设输入的数组的任意两个数字都互不相同。
'''
def is_postorder_bst(postorder):
  # 判断输入有效
  if not postorder:
    return False

  root, stack = float('inf'), []
  for i in range(len(postorder)-1, -1, -1):
    if postorder[i] > root: # 左子树都小于root
      return False
    while stack and postorder[i] < stack[-1]: # stack空的时候代表右半个树走完了
      root = stack.pop() # 更新root
    stack.append(postorder[i])

  return True
  
if __name__ == "__main__":
  '''
          10
     6          14
   4   8    12     16
  3 5 7 9  11 13 15  17

  后序 3 [5 4] 7 [9 8 6] 11 [13 12] 15 [17 16 14 10]
  前序 [10 6 4 3] 5 [8 7] 9 [14 12 11] 13 [16 15] 17
  '''
  postorders = [3, 5, 4, 7, 9, 8, 6, 11, 13, 12, 15, 17, 16, 14, 10]
  
  if is_postorder_bst(postorders):
    print("passed.")
  else:
    print("failed.")