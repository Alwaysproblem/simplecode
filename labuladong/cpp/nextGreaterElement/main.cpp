#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> nextGreaterElements(vector<int>& nums) {
    vector<int> ans(nums.size());
    stack<int> s{};
    for (int i = nums.size() * 2 - 1; i >= 0; i--) {
      while (!s.empty() && s.top() <= nums[i % nums.size()]) s.pop();
      ans[i % nums.size()] = s.empty() ? -1 : s.top();
      s.push(nums[i % nums.size()]);
    }
    return ans;
  }
};

int main() {
  vector<int> nums = {1, 2, 3, 4, 3};
  Solution sol;
  vector<int> v = sol.nextGreaterElements(nums);
  fmt::print("{}\n", v);
  return 0;
}
