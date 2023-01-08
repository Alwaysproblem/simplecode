#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int lengthOfLongestSubstring(string s) {
    if (!s.size()) return 0;
    const int INT_MIN = 0;
    unordered_map<char, int> window{};
    int left = 0, right = 0;
    char c = 0, d = 0;
    int start = 0, len = INT_MIN;
    while (right < s.size()) {
      char c = s[right];
      right++;
      window[c]++;
      if (window[c] == 1 && right - left > len) len = right - left;

      fmt::print("({}, {})", left, right);

      while (left < right && window[c] > 1) {
        char d = s[left];
        left++;
        window[d]--;
      }
    }
    return len;
  }
};

int main() {
  Solution sol;
  string s = "pwwkew";
  int v = sol.lengthOfLongestSubstring(s);
  fmt::print("{}\n", v);
  return 0;
}
