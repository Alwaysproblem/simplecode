/*
 * @lc app=leetcode.cn id=739 lang=cpp
 *
 * [739] 每日温度
 * title: daily-temperatures
 */
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
 public:
  vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();
    stack<int> s{};
    stack<int> idx{};
    vector<int> ans(n);
    for (int i = n - 1; i >= 0; i--) {
      while (!s.empty() && s.top() <= temperatures[i]) {
        s.pop();
        idx.pop();
      }
      ans[i] = idx.empty() ? 0 : idx.top() - i;
      // ans[i] = s.empty() ? 0 : s.top();
      s.push(temperatures[i]);
      idx.push(i);
    }
    return ans;
  }
};
// @lc code=end

int main() {
  vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};
  Solution sol;
  vector<int> v = sol.dailyTemperatures(temperatures);
  fmt::print("{}\n", v);
  return 0;
}
