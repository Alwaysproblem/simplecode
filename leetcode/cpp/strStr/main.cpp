#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  string pat{};
  vector<vector<int>> dp{};
  void KMP(const string &pattern) {
    int all_char_len = 256;
    pat = pattern;
    int M = pat.size();
    dp.assign(M, vector<int>(all_char_len, 0));
    dp[0][pat[0]] = 1;
    int X = 0;
    for (int j = 1; j < M; j++) {
      for (int c = 0; c < all_char_len; c++)
        dp[j][c] = dp[X][c];
      dp[j][pat.at(j)] = j + 1;
      X = dp[X][pat.at(j)];
    }
    // fmt::print("{}\n", dp);
  }

  int search(const string &txt){
    int N = txt.size();
    int M = pat.size();
    int j = 0;
    for (int i = 0; i < N;i++ ){
      j = dp[j][txt.at(i)];
      if (j == M) return i - M + 1;
    }
    return -1;
  }

  int strStr(string &haystack, string &needle) { 
    KMP(needle);
    return search(haystack);
  }
};

int main() {
  string haystack = "leetcode", needle = "leet";
  Solution s;
  int res = s.strStr(haystack, needle);
  fmt::print("{}\n", res);
  return 0;
}
