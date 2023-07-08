/*
 * @lc app=leetcode.cn id=76 lang=cpp
 *
 * [76] 最小覆盖子串
 */
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
 public:
  string minWindow(string s, string t) {
    if (s.size() == 0 || t.size() == 0) return "";
    unordered_map<char, int> need{}, window{};
    const int INTMAX = s.size() + 1;
    for (char c : t) need[c]++;
    int left = 0, right = 0;
    char c = 0;
    char d = 0;
    int start = 0, len = INTMAX;
    int valid = 0;
    while (right < s.size()) {
      c = s[right];
      right++;

      // window.add(right)
      if (need.count(c)) {
        window[c]++;
        if (window[c] == need[c]) valid++;
      }

      // fmt::print("({}, {})\n", left, right);

      while (valid == need.size()) {
        if (len > right - left) {
          start = left;
          len = right - left;
        }
        d = s[left];
        left++;
        // window.remove(left);
        if (need.count(d)) {
          if (window[d] == need[d]) valid--;
          window[d]--;
        }
      }
    }
    // fmt::print("len: {} start: {}\n", len, start);
    return len == INTMAX ? "" : s.substr(start, len);
  }
};
// @lc code=end

int main() {
  Solution sol;
  // string s = "b", t = "b";
  // string s = "abc", t = "b";
  // string s = "ADOBECODEBANC", t = "ABC";
  // string s = "bba", t = "ab";
  string s = "aa", t = "aa";
  string v = sol.minWindow(s, t);
  fmt::print("{}\n", v);
  return 0;
}
