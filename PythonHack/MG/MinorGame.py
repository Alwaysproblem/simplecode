# import re

# def findmatch(string, substr):
#     R = []
#     for ind in range(len(string)):
#         p = re.compile(substr)
#         # res = re.match(substr, string[ind:])
#         res = p.match(string[ind:])
#         if res != None:
#             R.append(res)
#     return len(R)

# def findallIter(string, reg, V = "AEIOU"):
#     for i in range(len(string)):
#         for k in range(i, len(string)):
#             if i == k :
#                 if string[i] not in reg.keys() and string[i] not in V:
#                     reg[string[i]] = findmatch(string, string[i])
#             else:
#                 for j in range(i, k):
#                     h = string[i:j]
#                     t = string[j:k + 1]
#                     n_ = [k for k in (h, t) if k != '' and k[0] not in V]

#                     if len(n_) == 0:
#                         pass
#                     elif n_[0] == string and n_[0] in reg.keys():
#                         pass
#                     else:
#                         for item in n_:
#                             if item not in reg.keys():
#                                 reg[item] = findmatch(string, item)

# def minion_game(string):
#     # your code goes here
#     reg_s = {}
#     reg_k = {}
#     findallIter(string, reg_s)
#     findallIter(string, reg_k, V=\
#             [chr(c) for c in range(ord("A"), ord("Z")) if chr(c) not in "AEIOU"])

#     print(f"reg_s is {reg_s}")
#     print(f"reg_k is {reg_k}")

#     sum_s = sum(reg_s.values())
#     sum_k = sum(reg_k.values())

#     if sum_k < sum_s:
#         print(f"Stuart {sum_s}")
#     elif sum_k > sum_s:
#         print(f"Kevin {sum_k}")
#     else:
#         print("Draw")


# if __name__ == '__main__':
#     s = input()
#     minion_game(s)


def minion_game(s):
    vowels = 'AEIOU'

    kevsc = 0
    stusc = 0

    for i in range(len(s)):
        if s[i] in vowels:
            kevsc += (len(s)-i)
        else:
            stusc += (len(s)-i)

    if kevsc > stusc:
        print("Kevin", kevsc)
    elif kevsc < stusc:
        print("Stuart", stusc)
    else:
        print("Draw")


if __name__ == '__main__':
    s = input()
    minion_game(s)