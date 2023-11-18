/*
 * @lc app=leetcode.cn id=187 lang=cpp
 *
 * [187] 重复的DNA序列
 * title: repeated-dna-sequences
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
  int StoN(char c) {
    int res = -1;
    switch (c) {
      case 'A':
        res = 0;
        break;
      case 'G':
        res = 1;
        break;
      case 'C':
        res = 2;
        break;
      case 'T':
        res = 3;
        break;

      default:
        cout << "error" << endl;
    }
    return res;
  }

  int addChar(vector<int> &arr, int windowHash, int right, int R) {
    return R * windowHash + arr[right];
  }

  int removeChar(vector<int> &arr, int windowHash, int left, int R, int len) {
    return windowHash - arr[left] * (int)pow(R, len - 1);
  }

  vector<string> findRepeatedDnaSequences(string &s) {
    vector<int> arr;
    vector<string> res;
    unordered_map<string, int> res_hash;
    string temp{};
    for (char c : s) arr.push_back(StoN(c));
    // fmt::print("{}\n", arr);
    unordered_map<int, int> seen{}, window{};
    int left = 0, right = 0, windowHash = 0, R = 4, L = 10;
    while (right < s.size()) {
      // window.add();
      windowHash = addChar(arr, windowHash, right, R);
      right++;

      // fmt::print("({}, {})\n", left, right);
      while (right - left == L) {
        // window.remove
        if (seen.count(windowHash)) {
          // fmt::print("already seen {}\n", windowHash);
          temp = s.substr(left, L);
          if (!res_hash.count(temp)) {
            res_hash[temp] = 1;
            res.push_back(temp);
          }
        } else {
          seen[windowHash] = 1;
        }
        windowHash = removeChar(arr, windowHash, left, R, L);
        left++;
      }
    }
    // fmt::print("{}\n", res);
    return res;
  }
};
// @lc code=end

int main() {
  string s = "AAAAAAAAAAAAA";
  // string s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
  Solution sol;
  vector<string> v = sol.findRepeatedDnaSequences(s);
  fmt::print("{}\n", v);
  return 0;
}
