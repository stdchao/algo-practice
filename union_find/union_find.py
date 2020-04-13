class unionFind:
  '''
  并查集，用数组模拟树结构，应用动态连通性问题
  '''
  def __init__(self, n):
    '''
    初始化并查集，n代表结点数
    '''
    self.count = n # 连通分量
    self.parent = [i for i in range(n)] # 数组模拟的树，存放对应结点的父结点
    self.size = [1 for _ in range(n)] # 以结点为根结点的树的大小，用来平衡树
  
  def find(self, p):
    '''
    寻找结点p的根结点
    '''
    while self.parent[p] != p:
      # 顺便对树进行路径压缩
      self.parent[p] = self.parent[self.parent[p]]
      p = self.parent[p]
    return p

  def union(self, p, q):
    '''
    连接结点p, q
    '''
    rootP = self.find(p)
    rootQ = self.find(q)
    if rootP == rootQ:
      # p, q 的根结点相同，代表已连通，无需操作
      return
    
    # 为使树平衡，尽量将小的树合并到大的树下
    if self.size[rootP] >= self.size[rootQ]:
      self.parent[rootQ] = rootP
      self.size[rootP] += self.size[rootQ]
    else:
      self.parent[rootP] = rootQ
      self.size[rootQ] += self.size[rootP]
    
    self.count -= 1
  
  def connected(self, p, q):
    '''
    判断结点p, q是否连接
    '''
    return self.find(p) == self.find(q)
  
  def getCount(self):
    '''
    返回连通分量
    '''
    return self.count


if __name__ == "__main__":
  uf = unionFind(10)
  print(uf.getCount())

  uf.union(0, 3)
  uf.union(1, 3)
  print(uf.connected(0, 3), uf.getCount(), uf.connected(0, 9))