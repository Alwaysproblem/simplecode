#include <fmt/format.h>
#include <fmt/ranges.h>

#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  long trailingZeroes(long n) {
    long res = 0;
    for (long d = n; d / 5 > 0; d = d / 5) {
      res += d / 5;
    }
    return res;
  }

  long left_bound(int target) {
    long lo = 0, hi = LONG_MAX - 1, mid = 0;
    while (lo <= hi) {
      mid = lo + (hi - lo) / 2;
      if (trailingZeroes(mid) == target) {
        hi = mid - 1;
      } else if (trailingZeroes(mid) < target) {
        lo = mid + 1;
      } else if (trailingZeroes(mid) > target) {
        hi = mid - 1;
      }
    }
    return lo;
  }

  long right_bound(int target) {
    long lo = 0, hi = LONG_MAX - 1, mid = 0;
    while (lo <= hi) {
      mid = lo + (hi - lo) / 2;
      if (trailingZeroes(mid) == target) {
        lo = mid + 1;
      } else if (trailingZeroes(mid) < target) {
        lo = mid + 1;
      } else if (trailingZeroes(mid) > target) {
        hi = mid - 1;
      }
    }
    return hi;
  }

  int preimageSizeFZF(int K) {
    fmt::print("{}\n", right_bound(K));
    fmt::print("{}\n", left_bound(K));
    return (int)(right_bound(K) - left_bound(K) + 1);
  }
};

int main() {
  int k = 0;
  Solution sol;
  int v = sol.preimageSizeFZF(k);
  fmt::print("{}\n", v);
  return 0;
}
