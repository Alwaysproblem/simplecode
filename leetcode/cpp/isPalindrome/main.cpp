/*
 * @lc app=leetcode.cn id=125 lang=cpp
 *
 * [125] 验证回文串
 * title: valid-palindrome
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
  bool isPalindrome(string& s) {
    char r[s.size() + 1];
    int j;
    int i;
    for (i = 0, j = 0; j < s.size(); j++) {
      if (s[j] >= 'a' && s[j] <= 'z') {
        r[i] = s[j];
        i++;
      } else if (s[j] >= 'A' && s[j] <= 'Z') {
        r[i] = s[j] | ' ';  // note 'A' | ' ' = 'a'
        // r[i] = s[j] + ('a' - 'A');
        i++;
      } else if (s[j] >= '0' && s[j] <= '9') {
        r[i] = s[j];
        i++;
      }
    }
    r[i] = 0;
    string rs = &r[0];
    // fmt::print("{}\n", rs);
    int f = 0, b = rs.size() - 1;
    while (f < b) {
      if (rs[f] != r[b]) return false;
      f++;
      b--;
    }
    return true;
  }
};
// @lc code=end

int main() {
  string s = "0P";
  Solution sol;
  bool v = sol.isPalindrome(s);
  fmt::print("{}\n", v);
  return 0;
}
