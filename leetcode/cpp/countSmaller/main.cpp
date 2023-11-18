/*
 * @lc app=leetcode.cn id=315 lang=cpp
 *
 * [315] 计算右侧小于当前元素的个数
 * title: count-of-smaller-numbers-after-self
 */

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

// @lc code=start
// solution will be https://leetcode.cn/problems/count-of-smaller-numbers-after-self/solutions/324892/ji-suan-you-ce-xiao-yu-dang-qian-yuan-su-de-ge-s-7/
class Solution {
private:
    vector<int> c;
    vector<int> a;

    void Init(int length) {
        c.resize(length, 0);
    }

    int LowBit(int x) {
        return x & (-x);
    }

    void Update(int pos) {
        while (pos < c.size()) {
            c[pos] += 1;
            pos += LowBit(pos);
        }
    }

    int Query(int pos) {
        int ret = 0;

        while (pos > 0) {
            ret += c[pos];
            pos -= LowBit(pos);
        }

        return ret;
    }

    void Discretization(vector<int>& nums) {
        a.assign(nums.begin(), nums.end());
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }
    
    int getId(int x) {
        return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
    }
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> resultList;

        Discretization(nums);

        Init(nums.size() + 5);
        
        for (int i = (int)nums.size() - 1; i >= 0; --i) {
            int id = getId(nums[i]);
            resultList.push_back(Query(id - 1));
            Update(id);
        }

        reverse(resultList.begin(), resultList.end());

        return resultList;
    }
};
// @lc code=end

int main() {
  vector<int> nums = {4, 2, 6, 3};
  Solution sol;
  auto v = sol.countSmaller(nums);
  fmt::print("{}\n", v);
  return 0;
}
