#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int countPrimes(int n) {
    vector<bool> isPrime(n, true);
    int res = 0;
    for (int i = 2; i * i < n; i++) {
      if (isPrime[i]) {
        for (int j = i * i; j < n; j += i) {
          isPrime[j] = false;
        }
      }
    }
    fmt::print("{}\n", isPrime);
    for (int i = 2; i < n; i++) {
      if (isPrime[i]) res += 1;
    }
    return res;
  }
};

int main() {
  int n = 2;
  Solution sol;
  int v = sol.countPrimes(n);
  fmt::print("{}\n", v);
  return 0;
}
