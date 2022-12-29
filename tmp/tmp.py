# import math
# from typing import List

# def isPrime(n): 
#   if n <= 1: 
#     return False
#   for i in range(2, int(math.sqrt(n)) + 1): 
#     if n % i == 0: 
#         return False
#   return True

# def findColor(arr: List[int], K: int):
#     if 1 in arr: return 1
#     table = { i: 0 for i in range(100) if isPrime(i) }

#     cunt = 0
#     for a in arr:
#         for t in table:
#             if a % t == 0:
#                 if table[t] == 0:
#                     cunt += 1
#                 table[t] += 1
#     return cunt

# if __name__ == '__main__':
#     print(findColor([4, 8, 12], 4))

def removeKDigits(num, k):
    n = len(num)
    if n <= k: return num
    stack = []
    for i in num:
        if not stack:
            stack.append(i)
            continue
        if k>0:
            while k>0 and stack:
                if stack[-1]>i:
                    stack.pop()
                    k-=1
                else:
                    break
        stack.append(i)
    if k!=0:
        return ''.join(stack[:-k])
    return ''.join(stack)

if __name__ == '__main__':
    minNum = removeKDigits('2615371',4)
    print(minNum)

# def removeKMinNumber(num, k):
#     if k == 0:
#         return num
#     if k == len(num):
#         return 0
#     StringBuffer nums = new StringBuffer().append(num);
#     Stack<Character> stack = new Stack<>();

#     for (int j = 0; j < nums.length(); j++) {
#         while (!stack.isEmpty() && stack.peek() > nums.charAt(j) && k>0){
#             stack.pop();
#             k--;
#         }
#         stack.push(nums.charAt(j));
#     }
#     nums.delete(0,nums.length());
#     while (!stack.isEmpty())
#         nums.insert(0,stack.pop());
#     return Integer.parseInt(nums.toString());

