/*
 * @lc app=leetcode.cn id=* lang=cpp
 *
 * [*] Sorting Algorithm for interview.
 */

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> bubble_sort(vector<int>& num) {
    vector<int> nums(num);
    int n = nums.size();
    for (int i = 0; i < n; i++){
      for (int j = 0; j < n - i - 1; j++){
        if (nums[j] > nums[j + 1]){
          swap(nums[j], nums[j + 1]);
        }
      }
    }
    return nums;
  }

  vector<int> insertion_sort(vector<int>& num) {
    vector<int> nums(num);
    int n = nums.size();
    for (int i = 0; i < n; i++){
      int j = i - 1;
      int key = nums[i];
      while (j >= 0 && nums[j] > key){
        nums[j + 1] = nums[j];
        j--;
      }
      nums[j + 1] = key;
    }
    return nums;
  }

  vector<int> quick_sort(vector<int>& num){
    vector<int> nums(num);
    int n = nums.size();
    quick_sort_helper(nums, 0, n - 1);
    return nums;
  }

  void quick_sort_helper(vector<int>& num, int low, int high){
    if (low < high){
      int pivot_index = quick_sort_partition(num, low, high);
      quick_sort_helper(num, low, pivot_index - 1);
      quick_sort_helper(num, pivot_index + 1, high);
    }
  }

  int quick_sort_partition(vector<int>& num, int low, int high){
    int pivot = num[high];
    int i = low - 1;
    for (int j = low; j < high; j++){
      if (num[j] <= pivot){
        i = i + 1;
        swap(num[i], num[j]);
      }
    }
    swap(num[i+1], num[high]);
    return i + 1;
  }

  vector<int> merge_sort(vector<int>& num) {
    vector<int> nums(num);
    int n = nums.size();
    if (n <= 1) return nums;
    merge_sort_helper(nums, 0, n - 1);
    return nums;
  }

  void merge_sort_helper(vector<int>& num, int left, int right) {
    if (right <= left) return;
    int mid = left + (right - left) / 2;
    merge_sort_helper(num, left, mid);
    merge_sort_helper(num, mid + 1, right);
    merge_sort_merge(num, left, mid, right);
  }

  void merge_sort_merge(vector<int>& num, int left, int mid, int right) {
    vector<int> temp(right - left + 1);

    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
      if (num[i] >= num[j]) {
        temp[k++] = num[j];
        j++;
      } else {
        temp[k++] = num[i];
        i++;
      }
    }
    for (; i <= mid; i++) {
      temp[k++] = num[i];
    }
    for (; j <= right; j++) {
      temp[k++] = num[j];
    }

    for (int p = left; p <= right; p++) {
      num[p] = temp[p - left];
    }
  }
};

int main() {
  vector<int> nums = {5, 7, 8, 1, 6, 2, 10, 78, 34, 9};
  Solution sol;
  auto v = sol.bubble_sort(nums);
  fmt::print("bubble_sort: \t{}\n", v);
  v = sol.insertion_sort(nums);
  fmt::print("insertion_sort: {}\n", v);
  v = sol.quick_sort(nums);
  fmt::print("quick_sort: \t{}\n", v);
  v = sol.merge_sort(nums);
  fmt::print("merge_sort: \t{}\n", v);
  return 0;
}
