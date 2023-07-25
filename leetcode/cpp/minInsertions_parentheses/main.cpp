/*
 * @lc app=leetcode.cn id=1541 lang=cpp
 *
 * [1541] 平衡括号字符串的最少插入次数
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
  int minInsertions(string s) {
    int res = 0, need = 0;

    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '(') {
        need += 2;
        if (need % 2 == 1) {
          res++;
          need--;
        }
      }

      if (s[i] == ')') {
        need--;
        if (need == -1) {
          res++;
          need = 1;
        }
      }
    }

    return res + need;
  }
};
// @lc code=end

int main() {
  string s = "))())(";
  Solution sol;
  int v = sol.minInsertions(s);
  fmt::print("{}\n", v);
  return 0;
}
