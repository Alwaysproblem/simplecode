/*
 * @lc app=leetcode.cn id=567 lang=cpp
 *
 * [567] 字符串的排列
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
  bool checkInclusion(string s1, string s2) {
    if (!s2.size()) return false;
    if (!s1.size()) return false;
    if (s1.size() > s2.size()) return false;
    unordered_map<char, int> need{}, window{};
    for (char i : s1) need[i]++;
    int left = 0, right = 0;
    char c = 0, d = 0;
    bool res = false;
    int valid = 0;
    while (right < s2.size()) {
      c = s2[right];
      right++;

      if (need.count(c)) {
        window[c]++;
        if (need[c] == window[c]) valid++;
      }

      // fmt::print("({}, {})", left, right);

      while (right - left >= s1.size()) {
        if (valid == need.size()) return true;
        d = s2[left];
        left++;
        if (need.count(d)) {
          window[d]--;
          if (need[d] == window[d]) valid--;
        }
      }
    }

    return false;
  }
};
// @lc code=end

int main() {
  Solution sol;
  string s = "ab", t = "eidboaoo";
  bool v = sol.checkInclusion(s, t);
  fmt::print("{}\n", v);
  return 0;
}
