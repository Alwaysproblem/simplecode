# Python program to find maximum contiguous subarray 
# Function to find the maximum contiguous subarray 
from math import inf 
def maxSubArraySum(a, size): 

    max_so_far = -inf - 1
    max_ending_here = [0] * (size + 1)

    optsuffix = [0] * (size + 1)

    for i in range(0, size): 
        max_ending_here[i + 1] = max_ending_here[i] + a[i]

        # if max_so_far < max_ending_here:
        #     max_so_far = max_ending_here
   
        if max_ending_here[i + 1] <= 0: 
            max_ending_here[i + 1] = a[i]
            optsuffix[i + 1] = i + 1
        else:
            optsuffix[i + 1] = optsuffix[i]
    
    print(optsuffix)
    print(max_ending_here)
    return max_so_far

# Driver function to check the above function  
# a = [-13, -3, -25, -20, -3, -16, -23, -12, -5, -22, -15, -4, -7] 
a = list(map(int, input().split()))
print("Maximum contiguous sum is", maxSubArraySum(a, len(a))) 
   
#This code is contributed by _Devesh Agrawal_ 