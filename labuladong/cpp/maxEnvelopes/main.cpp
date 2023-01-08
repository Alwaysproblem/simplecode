#include <fmt/format.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int lengthOfLIS(vector<int>& nums) {
    vector<int> top(nums.size());

    int piles = 0;
    for (int i = 0; i < nums.size(); i++) {
      int poker = nums[i];

      int left = 0, right = piles;
      while (right > 0 && left < right) {
        int mid = left + (right - left) / 2;
        if (top[mid] >= poker) {
          right = mid;
        } else if (top[mid] < poker) {
          left = mid + 1;
        }
      }

      if (left == piles) piles++;
      top[left] = poker;
      fmt::print("{}\n", top);
    }
    return piles;
  }

  int maxEnvelopes(vector<vector<int>>& envelopes) {
    sort(envelopes.begin(), envelopes.end(),
         [](vector<int>& x, vector<int>& y) {
           if (x[0] < y[0]) return true;
           if (x[0] == y[0]) return x[1] > y[1];
           return false;
         });

    vector<int> lis = {};
    for (auto& v : envelopes) {
      lis.push_back(v[1]);
    }
    return lengthOfLIS(lis);
  }
};

int main() {
  Solution sol;
  vector<vector<int>> envelopes = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
  int v = sol.maxEnvelopes(envelopes);
  fmt::print("{}\n", v);
  return 0;
}
