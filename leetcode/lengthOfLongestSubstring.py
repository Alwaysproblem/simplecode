from collections import defaultdict

def lengthOfLongestSubstring(s: str) -> int:
    l = 0
    r = 0
    ans = 0
    counter = defaultdict(int)

    for c in s:
        while counter[c] != 0:
            counter[s[l]] -= 1
            l += 1
        r += 1
        counter[c] += 1

        ans = max(ans, r - l)
    return ans


print(lengthOfLongestSubstring("pwwkew"))
