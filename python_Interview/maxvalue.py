#
# 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
#
# 最大数
# @param nums int整型一维数组 
# @return string字符串
#
#
# [30,1]
# "301"
# [2,20,23,4,8]
# "8423220"
# 给定一个数组N 进行拼接 得到数字 最大

from typing import List
from functools import cmp_to_key


def key_func(x: str, y:str) -> int:
  if x + y > y + x:
    return -1
  if x + y < y + x:
    return 1
  return 0

class Solution:
  def solve(self , nums: List[int]) -> str:
    # write code here
    nums_str = [ str(i) for i in nums]
    if len(nums_str) == 1:
      return nums_str[0]
    nums_str.sort(key=cmp_to_key(key_func))
    return nums_str


if __name__ == '__main__':
  nums = [30, 1]
  # nums = [2,20,23,4,8]
  solution = Solution()
  ret = solution.solve(nums)
  print(ret)
