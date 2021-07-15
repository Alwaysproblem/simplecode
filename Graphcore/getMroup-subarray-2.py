from statistics import mean, stdev
from math import fabs
from typing import List
from copy import deepcopy

def variances(former: List[int], latter: List[int], num_group: int):
    former_mean = (sum(former) + sum(latter)) / num_group
    latter_mean = (1 -  1 / num_group) * (sum(former) + sum(latter))
    return fabs(sum(former) - former_mean) + fabs(sum(latter) - latter_mean) - len(former)

def citation(*group):
    sum_over_group = []
    for g in group:
        sum_over_group.append(sum(g))
    return stdev(sum_over_group) if len(sum_over_group) > 1 else 0


def find_opt(arr, num_group):

    res_set = []

    def divide_and_conquer_helper(arr, num_group, res):
        if not arr or not num_group:
            return

        if num_group == 1:
            res.append(arr.copy())
            res_set.append(deepcopy(res))
            res.pop()
            return

        scores_for_all = [ (i, variances(arr[:i], arr[i:], num_group)) for i in range(1, len(arr))]
        miniumn_score = min([ score for _, score in scores_for_all ])
        scores_for_min = [ (sep, score) for sep, score in scores_for_all if score == miniumn_score]

        for sep, _ in scores_for_min:
            res.append(arr[:sep])
            divide_and_conquer_helper(arr[sep:], num_group - 1, res)
            res.pop()

    divide_and_conquer_helper(arr, num_group, [])
    return res_set


if __name__ == '__main__':
    arr = [1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1200, 0, 0, 0, 0, 0, 0, 34, 56, 74, 39, 26, 49]
    # arr = [10, 5, 5, 40, 20, 10, 10]
    # arr = [1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1]

    res = find_opt(arr, 4)
    print(*res, sep='\n')