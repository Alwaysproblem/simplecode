from copy import deepcopy

def DFS_search(arr, num_groups):

    res_set = []

    def brutal_search_helper(arr, num_groups, res):
        if not arr or not num_groups:
            return

        if num_groups == 1:
            res.append(arr.copy())
            res_set.append(deepcopy(res))
            res.pop()
            return


        for i in range(1, len(arr)):
            first_group = arr[:i].copy()
            res.append(first_group)
            brutal_search_helper(arr[i:], num_groups - 1, res)
            res.pop()

    brutal_search_helper(arr, num_groups, [])
    return res_set

# TODO: need to implement non-recursive version for python 


if __name__ == '__main__':

    a = [1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1200, 1, 1, 1, 1, 1, 1, 34, 56, 74, 39, 26, 49]
    r = DFS_search(a, 4)

    with open("out", 'w') as f:
        print(*r, file=f, sep='\n')