/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// @lc code=start

class Solution {
 public:
  vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> m;
    vector<int> v;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      int diff = target - nums[i];
      if (m.find(diff) != m.end()) {
        auto p = m.find(diff);
        v.push_back(p->second);
        v.push_back(i);
      }
      m.insert(make_pair(nums[i], i));
    }

    return v;
  }
};

// @lc code=end

int main() {
  Solution s;
  vector<int> v{1, 6, 3, 2, 5};
  vector<int> result = s.twoSum(v, 11);
  for (int i : result) {
    cout << i << endl;
  }
  return 0;
}
