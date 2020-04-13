class Heap():
  '''
  heap: 堆数据结构，不完全二叉树，堆顶为最大值或最小值
  总结:
    插入是上浮操作，删除是下沉操作；
    建堆，可以基于已有数组进行自底向上(mid->1)的下沉操作，也可以基于空数组不断插入元素(1->n)的上浮操作
  '''
  def __init__(self):
    self.heapList = [0] # 保证根节点索引从1开始
    self.heapsize = 0

  def max_heapify(self, i):
    '''
    max_heapify: 使heapList[i]在最大堆中，逐级下沉，维持最大堆性质
    时间复杂度: log(n)
    总结:
      也可以用迭代实现
    '''
    left = 2 * i
    right = 2 * i + 1

    largest = i
    if left <= self.heapsize and self.heapList[left] > self.heapList[largest]:
      largest = left
    
    if right <= self.heapsize and  self.heapList[right] > self.heapList[largest]:
      largest = right
    
    if largest != i:
      tmp = self.heapList[i]
      self.heapList[i] = self.heapList[largest]
      self.heapList[largest] = tmp
      # 继续下沉，
      self.max_heapify(largest)
    
  def build_max_heap(self, l):
    '''
    build_max_heap: 给定数组l，自底向上的，将其转换为最大堆
    时间复杂度: n
    '''
    self.heapList = [0] + l
    self.heapsize = len(l)

    mid = self.heapsize // 2
    while mid > 0:
      self.max_heapify(mid)
      mid = mid - 1
    
  def heap_sort(self, l):
    '''
    heap_sort: 堆排序算法，先构建最大堆，然后取出堆顶元素，
    时间复杂度: nlog(n)
    '''
    self.build_max_heap(l)
    while self.heapsize > 1:
      tmp = self.heapList[self.heapsize]
      self.heapList[self.heapsize] = self.heapList[1]
      self.heapList[1] = tmp

      self.heapsize = self.heapsize - 1
      self.max_heapify(1)

  def heap_maximum(self):
    '''
    heap_maximum: 返回堆顶元素值
    '''
    return self.heapList[1]

  def heap_extract_max(self):
    '''
    heap_extract_max: 弹出最大堆的堆顶元素，然后将堆尾元素放在堆顶，下沉操作
    '''
    pass

  def heap_increase_key(self, i, key):
    '''
    heap_increase_key: 增大元素i的值，上浮操作，维持最大堆性质
    '''
    pass

  def max_heap_insert(self, key):
    '''
    max_heap_insert: 在堆尾插入新元素，上浮操作
    '''
    pass

if __name__ == '__main__':
  A = [5, 3, 17, 10, 84, 19, 22, 9]
  print('raw: A', A)

  heap_A = Heap()
  heap_A.build_max_heap(A)
  print('build max heap: ', heap_A.heapList)

  heap_A.heap_sort(A)
  print('heap sort:', heap_A.heapList)
