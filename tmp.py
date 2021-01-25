def CountSort(nums):

    # if min(nums) > 0:
    #     cnt_list = [0] * max(nums)
    # else:
    cnt_list = [0] * (abs(max(nums)) + abs(min(nums)) + 1)
    delta = min(nums)
    res = []

    for i in nums:
        cnt_list[i - delta] += 1
    
    for idx, cnt in enumerate(cnt_list):
        if cnt != 0:
            res += [idx + delta] * cnt
    
    return res

if __name__ == '__main__':
    print(CountSort([1,1,1,1,1,1,11,]))