
def canJump(nums) -> bool:
    maxs = 0
    n = len(nums)

    for i in range(n - 1):
        if maxs < i:
            return False
        maxs = max(maxs, nums[i] + i)

        if maxs >= n - 1:
            return True

    return maxs >= n - 1

print(canJump([2,3,1,1,4]))