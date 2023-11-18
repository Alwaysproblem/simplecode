/*
 * @lc app=leetcode.cn id=69 lang=cpp
 *
 * [69] x 的平方根
 * title: sqrtx
 */

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/sqrtx/solutions/238553/x-de-ping-fang-gen-by-leetcode-solution/
// @lc code=start
class Solution {
 public:
  int mySqrt_simple(int x) {
    if (x == 0) {
      return 0;
    }
    int ans = exp(0.5 * log(x));
    return ((long long)(ans + 1) * (ans + 1) <= x ? ans + 1 : ans);
  }

  int mySqrt_binsearch(int x) {
    long long left = 0, right = x, mid = 0;
    while (left <= right) {
      mid = left + (right - left) / 2;
      if (mid * mid > x) {
        right = mid - 1;
      } else if (mid * mid < x) {
        left = mid + 1;
      } else {
        return mid;
      }
    }

    return (left + right) / 2;
  }

  int mySqrt_newton(int x) {
    if (!x) return 0;
    double C = x;
    double x0 = x;
    double xi = 0;
    while (1) {
      xi = 0.5 * (x0 + C / x0);
      if (fabs(xi - x0) < 1e-7) break;
      x0 = xi;
    }
    return (int)xi;
  }

  int mySqrt_newton_back(int x) {
    long long r = x;
    while (r * r > x) r = (r + x / r) / 2;
    return r;
  }

  int mySqrt(int x) { return mySqrt_newton_back(x); }
};
// @lc code=end

int main() {
  int x = 2147395599;
  Solution sol;
  auto v = sol.mySqrt(x);
  fmt::print("{}\n", v);
  return 0;
}
