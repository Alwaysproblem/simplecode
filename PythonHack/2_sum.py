# def twoSum(nums, target):
#     """
#     :type nums: List[int]
#     :type target: int
#     :rtype: List[int]
#     """
#     from collections import Counter
#     ind_dic = {}
#     if len(set(nums)) != len(nums):
#         pans = Counter(nums).most_common(1)[0][0]
#         if pans*2 == target:
#             fi = nums.index(pans)
#             nums[fi] = ''
#             return [fi, nums.index(pans)]
#         else:
#             for ne in range(len(nums)):
#                 if nums[ne] == pans:
#                     nums[ne] = ''
#             find_ans = nums

#     elif len(set(nums)) == len(nums):
#         find_ans = nums
#     else:
#         pass
    
#     for i, n in enumerate(find_ans):
#         ind_dic[n] = i
#     for c in find_ans:
#         if c != '':
#             if target - c in ind_dic and ind_dic[c] != ind_dic[target - c]:
#                 return [ind_dic[c], ind_dic[target - c]]
    
#     return "None"
#     60 ms


# find the two number that sum up to target sum

def twoSum(nums, target):
    # 96 ms
    """
    :type nums: List[int]
    :type target: int
    :rtype: List[int]
    """
    ind_dic = {}

    for i, n in enumerate(nums):
        if ind_dic.get(n) is None:
            ind_dic[n] = [i]
        else:
            ind_dic[n].append(i)
    
    for c in nums:
        if len(ind_dic[c]) > 1 and c * 2 == target:
            return [ind_dic[c][0], ind_dic[c][1]]

        elif target - c in ind_dic and ind_dic[c] != ind_dic[target - c]:
            return [ind_dic[c][0], ind_dic[target - c][0]]



def main():
    nums = [230,863,916,585,981,404,316,785,88,12,70,435,384,778,887,755,740,337,86,92,325,422,815,650,920,125,277,336,221,847,168,23,677,61,400,136,874,363,394,199,863,997,794,587,124,321,212,957,764,173,314,422,927,783,930,282,306,506,44,926,691,568,68,730,933,737,531,180,414,751,28,546,60,371,493,370,527,387,43,541,13,457,328,227,652,365,430,803,59,858,538,427,583,368,375,173,809,896,370,789]
    # 542
    tar = int(input("target:"))
    ans = twoSum(nums, tar)
    print(ans)

if __name__ == '__main__':
    main()