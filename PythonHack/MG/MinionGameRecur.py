# #%%
# import re

# def findmatch(string, substr):
#     R = []
#     for ind in range(len(string)):
#         res = re.match(substr, string[ind:])
#         if res != None:
#             R.append(res)
#     return len(R)

#%%

# # S = "BANANA"

# # # V = "AEIOU"

# # reg = {}

# # def findallRecur(string, reg, V = "AEIOU"):
# #     if string == '':
# #         return
# #     elif len(string) == 1:
# #         if string not in reg.keys():
# #             reg[string] = None
# #         return
# #     else:
# #         for i in range(len(string)):
# #             h = string[:i]
# #             t = string[i:]
# #             n_ = [k for k in (h, t) if k != '' and k[0] not in V]

# #             if len(n_) == 0:
# #                 pass
# #             elif n_[0] == string and n_[0] in reg.keys():
# #                 pass
# #             else:
# #                 for item in n_:
# #                     if item not in reg.keys():
# #                         reg[item] = None
# #                     findallRecur(item, reg)

# # findallRecur(S, reg)
# # print(reg)
# # reg_r = reg
# #%%

# S = "BANANA"
# reg = {}

# K = "ANANA"

# def findallIter(string, reg, V = "AEIOU"):
#     for i in range(len(string)):
#         for k in range(i, len(string)):
#             if i == k :
#                 if string[i] not in reg.keys() and string[i] not in V:
#                     reg[string[i]] = findmatch(string, string[i])
#             else:
#                 for j in range(i, k):
#                     h = string[i:j]
#                     t = string[j:k+1]
#                     n_ = [k for k in (h, t) if k != '' and k[0] not in V]

#                     if len(n_) == 0:
#                         pass
#                     elif n_[0] == string and n_[0] in reg.keys():
#                         pass
#                     else:
#                         for item in n_:
#                             if item not in reg.keys():
#                                 reg[item] = findmatch(string, item)

# findallIter(K, reg, V = [chr(c) for c in range(ord("A"), ord("Z")) if chr(c) not in "AEIOU"])


# print(reg)
import re
from functools import partial

def findmatch(string, substr):
    R = []
    for ind in range(len(string)):
        res = re.match(substr, string[ind:])
        if res != None:
            R.append(res)
    return len(R)

def findallRecur(string, reg, X, V = "AEIOU"):
    if string == '':
        return
    elif len(string) == 1:
        if string not in reg.keys():
            reg[string] = findmatch(X, string)
        return
    else:
        for i in range(len(string)):
            h = string[:i]
            t = string[i:]
            n_ = [k for k in (h, t) if k != '' and k[0] not in V]

            if len(n_) == 0:
                pass
            elif n_[0] == string and n_[0] in reg.keys():
                pass
            else:
                for item in n_:
                    if item not in reg.keys() and item[0] not in V:
                        reg[item] = findmatch(X, item)
                    findallRecur(item, reg, X, V=V)

def minion_game(string):
    # your code goes here
    reg_s = {}
    reg_k = {}
    findallIter = partial(findallRecur, X = string)

    findallIter(string, reg_s)
    findallIter(string, reg_k, V=\
            [chr(c) for c in range(ord("A"), ord("Z")) if chr(c) not in "AEIOU"])

    print(f"reg_s is {reg_s}")
    print(f"reg_k is {reg_k}")
    
    sum_s = sum(reg_s.values())
    sum_k = sum(reg_k.values())

    if sum_k < sum_s:
        print(f"Stuart {sum_s}")
    elif sum_k > sum_s:
        print(f"Kevin {sum_k}")
    else:
        print("Draw")


if __name__ == '__main__':
    s = input()
    minion_game(s)