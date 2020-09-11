def subsets(nums):
  res = [[]]

  for num in nums:
    addset = []
    for subset in res:
      addset.append(subset + [num])
    res += addset
  return res
  
if __name__ == "__main__":
  res = subsets([1,2,3])
  print(res)