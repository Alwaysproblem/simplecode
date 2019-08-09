#!/bin/python3
#%%
import math
import os
import random
import re
import sys

# from itertools import permutations, combinations, accumulate
# from collections import Counter
# from functools import reduce

#%%
# from collections import Counter
# from itertools import combinations

# def sherlockAndAnagrams(s):
#     count = []
#     for i in range(1,len(s)+1):
#         a = ["".join(sorted(s[j:j+i])) for j in range(len(s)-i+1)]
#         b = Counter(a)
#         for j in b:
#             tmp = list(combinations(['a']*b[j], 2))
#             count.append(sum([len(tmp)]))
#     return sum(count)



#%%[markdown]
# Two string are anagrams if and only if for every letter occurring in any of them the number of its occurrences is equal in both the strings.
# 
# This definition is crucial and will lead to the solution. Since the only allowed letters are lowercase English letters, from $a$ to $z$, the alphabet size is constant and its size is $26$. This allows us to assign a constant size signature to each of the substring of $s$.
# 
# A signature of some string $w$ will be a tuple of $26$ elements where the -th element denotes the number of occurrences of the $i$-th letter of the alphabet in $w$.
# 
# So, for example, if $w$ then its signature is $[0,0,0,0,0,0,0,0,0,0,0,0,2,0,1,0,0,0,0,0,0,0,0,0,0,0]$, so the only non-zero elements are the ones corresponding to letter $m$ with value of 2 and letter $o$ with value of 1.
# 
# Notice, that any string that is an anagram of $"mom"$ will have the same signature as $"mom"$, and every string that is not an anagram of $"mom"$ will definitely have a different signature.
# 
# This concept of signatures allows the following approach.
# 
# Let's iterate over all substrings of $s$ and for each fixed substring let's compute its signature and add that signature to signatures hashmap, where $signatures[sig]$ denotes the number of substrings of $s$ with a signature $sig$.
# 
# Finally, the only remaining thing to do is to get the number of pairs of substrings of $s$ that are anagrams. It's easy to do having our hashmap. Notice that if there are $n$ substrings of $s$ with signature $sig$, then they can form $n\times(n-1) \div 2$ pairs of substrings with signature $sig$, so we can just iterate over all values in the hashmap and for each value $n$ add $n\times(n-1) \div 2$ to the final result.
# 
# The below, commented code, in Python, illustrates this exact approach.
# 
# The time complexity is $O(\lvert s^{3} \rvert )$ since we iterate over all $O(\lvert s^{2} \rvert )$ substrings of s and for each substring we compute its signature in $O(\lvert s \rvert )$  time. It's worth to mention that each operation on hashmap has constant running time since our signatures have a constant size, i.e. $26$ which is the size of our alphabet. Otherwise, if the alphabet size is not constant, this approach will have $O(\lvert s^{3} \rvert ) \times ALPHABET_SIZE$ time complexity.#%%
# mysolution:

#%%
# from collections import Counter
# # Complete the sherlockAndAnagrams function below.
# def sherlockAndAnagrams(s):
#     def findallsubstring(s):
#         sub = []
#         for ind in range(len(s)):
#             for indc in range(ind, len(s)):
#                 if s != s[ind:indc+1]:
#                     sub.append(s[ind:indc+1])
#         # print(set(sub))
#         return sub
#     sub = findallsubstring(s)
#     # print(sub)

#     a = Counter()
#     order = {chr(i + ord('a')): i for i in range(26)}
#     for i in sub:
#         aaa = [0] * 26
#         aa = Counter(i)
#         for c in aa.keys():
#             aaa[order[c]] += aa[c]
#         d = str(aaa)
#         if d in a:
#             a[d] += 1
#         else:
#             a[d] = 1

#     dd = sum(map(lambda x: x*(x - 1) / 2, [i for i in a.values() if i > 1]))
#     return int(dd)

from collections import Counter
# Complete the sherlockAndAnagrams function below.
def sherlockAndAnagrams(s):
    Count = 0
    def findallsubstring(s):
        sub = []
        for ind in range(len(s)):
            for indc in range(ind, len(s)):
                if s != s[ind: indc + 1]:
                    sub.append(''.join(sorted(s[ind: indc + 1])))
        # print(set(sub))
        return sub
    sub = findallsubstring(s)
    b = Counter(sub)
    for i in b:
        Count += b[i] * (b[i] - 1) / 2

    return int(Count)



if __name__ == '__main__':

    q = int(input())

    for q_itr in range(q):
        s = input()

        result = sherlockAndAnagrams(s)

        print(result)

