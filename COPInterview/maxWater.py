class Solution:
    def maxWater(self , arr ):
        # write code here
        n = len(arr) - 1
        i, j = 0, n
        left, right = arr[0], arr[n]
        sum_val = 0
        while i < j:
            if left < right:
                i += 1
                if left >= arr[i]:
                    sum_val += (left - arr[i])
                else:
                    left = arr[i]
            else:
                j -= 1
                if right >= arr[j]:
                    sum_val += (right - arr[j])
                else:
                    right = arr[j]
        return sum_val

if __name__ == "__main__":
    print(Solution().maxWater([3,1,2,5,2,4]))