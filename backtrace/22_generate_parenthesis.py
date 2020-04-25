'''
Leetcode 22. 括号生成
'''
def generate_parenthesis(n):
  def backtrace(s, left, right):
    print('debug backtrace', s, left, right)
    if len(s) == 2*n:
      res.append(s)
      return
    
    if left < n:
      backtrace(s + '(', left+1, right)
    
    if right < left:
      backtrace(s + ')', left, right+1)

  res = []
  backtrace('', 0, 0)
  return res

if __name__ == "__main__":
  result = generate_parenthesis(3)
  print(result)