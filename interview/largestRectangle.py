#!/bin/python3

import math
import os
import random
import re
import sys

# https://www.hackerrank.com/challenges/largest-rectangle/problem
class Stack(object):
    def __init__(self, data = None):
        if data == None:
            self.data = []
        else:
            self.data = data
    
    def push(self, data):
        self.data.append(data)

    def pop(self):
        return self.data.pop()

    @property
    def top(self):
        return self.data[-1]

    def isEmpty(self):
        return len(self.data) == 0

    def __repr__(self):
        return "Stack(" + ','.join(map(str, self.data)) + ")"


# Complete the largestRectangle function below.
def largestRectangle(h):
    s = Stack()
    max_area = 0
    ind = 0

    while ind < len(h):
        if s.isEmpty() or h[s.top] <= h[ind]:
            s.push(ind)
            ind += 1
        else:
            top = s.pop()
            left = 0 if s.isEmpty() else s.top + 1
            max_area = max(max_area, (ind - left) * h[top])

    while not s.isEmpty():
        top = s.pop()
        left = 0 if s.isEmpty() else s.top + 1
        max_area = max(max_area, (ind - left) * h[top])

    return max_area


if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    h = list(map(int, input().rstrip().split()))

    result = largestRectangle(h)

    print(result)

# Python3 program to find maximum  
# rectangular area in linear time 
  
# def max_area_histogram(histogram): 
      
#     # This function calulates maximum  
#     # rectangular area under given  
#     # histogram with n bars 
  
#     # Create an empty stack. The stack  
#     # holds indexes of histogram[] list.  
#     # The bars stored in the stack are 
#     # always in increasing order of  
#     # their heights. 
#     stack = list() 
  
#     max_area = 0 # Initalize max area 
  
#     # Run through all bars of 
#     # given histogram 
#     index = 0
#     while index < len(histogram): 
          
#         # If this bar is higher  
#         # than the bar on top 
#         # stack, push it to stack 
  
#         if (not stack) or (histogram[stack[-1]] <= histogram[index]): 
#             stack.append(index) 
#             index += 1
  
#         # If this bar is lower than top of stack, 
#         # then calculate area of rectangle with  
#         # stack top as the smallest (or minimum 
#         # height) bar.'i' is 'right index' for  
#         # the top and element before top in stack 
#         # is 'left index' 
#         else: 
#             # pop the top 
#             top_of_stack = stack.pop() 
  
#             # Calculate the area with  
#             # histogram[top_of_stack] stack 
#             # as smallest bar 
#             area = (histogram[top_of_stack] * 
#                    ((index - stack[-1] - 1)  
#                    if stack else index)) 
  
#             # update max area, if needed 
#             max_area = max(max_area, area) 
  
#     # Now pop the remaining bars from  
#     # stack and calculate area with  
#     # every popped bar as the smallest bar 
#     while stack: 
          
#         # pop the top 
#         top_of_stack = stack.pop() 
  
#         # Calculate the area with  
#         # histogram[top_of_stack]  
#         # stack as smallest bar 
#         area = (histogram[top_of_stack] * 
#               ((index - stack[-1] - 1)  
#                 if stack else index)) 
  
#         # update max area, if needed 
#         max_area = max(max_area, area) 
  
#     # Return maximum area under  
#     # the given histogram 
#     return max_area 
  
# Driver Code 
# hist = [6, 2, 5, 4, 5, 1, 6] 
# print("Maximum area is",  
#        max_area_histogram(hist)) 
  
# This code is contributed  
# by Jinay Shah 