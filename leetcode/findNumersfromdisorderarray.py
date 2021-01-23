def find(arr, target):
  if len(arr) == 0:
    return -1
  if len(arr) == 1:
    if arr[0] != target:
      return -1
    else:
      return 0

  l = 0
  r = len(arr) - 1
  mid = (l + r) // 2
  
  while l <= r:
    if arr[mid] == target:
      return mid
    
    if arr[l] <= arr[mid]:
      if arr[l] <= target < arr[mid]:
      	r = mid
      else:
      	l = mid + 1
    
    elif arr[r] > arr[mid]: 
      if arr[mid] <= target <= arr[r]:
        l = mid + 1
      else:
        r = mid
    
    mid = (l + r) // 2
    
  return -1

if __name__ == "__main__":
    print(find([5,6,7,8,1,2,3,4,6], 8))
