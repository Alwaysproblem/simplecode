
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

