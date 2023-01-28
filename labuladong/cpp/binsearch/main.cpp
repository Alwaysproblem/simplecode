#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int search(vector<int>& nums, int target) {
    if (!nums.size()) return -1;
    int left = 0, right = nums.size() - 1;
    int mid = 0;
    while (left < right) {
      mid = left + (right - left) / 2;
      if (nums.at(mid) == target)
        return mid;
      else if (nums.at(mid) > target) {
        right = mid - 1;
      } else if (nums.at(mid) < target) {
        left = mid + 1;
      }
    }
    return nums.at(left) == target ? -1 : left;
  }
};

int main() {
  Solution s;
  vector<int> v{-1, 0, 3, 5, 9, 12};
  int idx = s.search(v, 2);
  fmt::print("The index should be {}\n", idx);
  return 0;
}
