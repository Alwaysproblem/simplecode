/*
 * @lc app=leetcode.cn id=438 lang=cpp
 *
 * [438] 找到字符串中所有字母异位词
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
  vector<int> findAnagrams(string s, string p) {
    if (!s.size() || !p.size()) return vector<int>();
    if (s.size() < p.size()) return vector<int>();
    unordered_map<char, int> need{}, window{};
    for (char t : p) need[t]++;
    int left = 0, right = 0;
    char c = '0', d = '0';
    int start = 0, valid = 0;
    vector<int> starts{};
    while (right < s.size()) {
      c = s[right];
      right++;

      if (need.count(c)) {
        window[c]++;
        if (need[c] == window[c]) valid++;
      }

      // fmt::print("({}, {})\n", left, right);

      while (left < right && right - left == p.size()) {
        if (valid == need.size()) {
          start = left;
          starts.push_back(start);
        }

        d = s[left];
        left++;
        if (need.count(d)) {
          if (need[d] == window[d]) valid--;
          window[d]--;
        }
      }
    }
    return starts;
  }
};
// @lc code=end

int main() {
  Solution sol;
  string s = "abab", p = "ab";
  vector<int> v = sol.findAnagrams(s, p);
  fmt::print("{}\n", v);
  return 0;
}
