def Subset(nums: list):
    if len(nums) == 0:
        return [set()]
    if len(nums) == 1:
        return [set(), set([nums[0]])]
    k = nums.pop()
    res = Subset(nums)

    res_ = []
    for i in res:
        co = i.copy()
        co.add(k)
        res_.append(co)
    
    # res_.append(set([k]))
    # res_.append(set())
    res_ += res

    return res_


Subset([1,2,3])