/*
 * @lc app=leetcode.cn id=372 lang=cpp
 *
 * [372] 超级次方
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
  const int base = 1337;
  int mypow(int a, int k) {
    // 对因子求模
    a %= base;
    int res = 1;
    for (int _ = 0; _ < k; _++) {
      // 这里有乘法，是潜在的溢出点
      res *= a;
      // 对乘法结果求模
      res %= base;
    }
    return res;
  }

  int superPow(int a, vector<int>& b) {
    if (b.empty()) return 1;
    if (a == 0) return 0;

    int last = b.back();
    b.pop_back();

    int m1 = mypow(superPow(a, b), 10);
    int m2 = mypow(a, last);

    return (m1 * m2) % base;
  }
};
// @lc code=end

int main() {
  int a = 2147483647;
  vector<int> b = {2, 0, 0};
  Solution sol;
  int v = sol.superPow(a, b);
  fmt::print("{}\n", v);
  return 0;
}
