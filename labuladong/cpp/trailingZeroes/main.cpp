#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int trailingZeroes(int n) {
    int res = 0;
    for (int d = n; d / 5 > 0; d = d / 5) {
      res += d / 5;
    }
    return res;
  }
};

int main() {
  int n = 5;
  Solution sol;
  int v = sol.trailingZeroes(n);
  fmt::print("{}\n", v);
  return 0;
}
