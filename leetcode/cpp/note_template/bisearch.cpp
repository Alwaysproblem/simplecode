int binarySearch(int[] nums, int target) {
  int left = 0, right = ...;

  while (...) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) {
      ...
    } else if (nums[mid] < target) {
      left = ...
    } else if (nums[mid] > target) {
      right = ...
    }
  }
  return ...;
}

// 查找
// 因为我们初始化 right = nums.length - 1
// 所以决定了我们的「搜索区间」是 [left, right]
// 所以决定了 while (left <= right)
// 同时也决定了 left = mid+1 和 right = mid-1
// 因为我们只需找到一个 target 的索引即可
// 所以当 nums[mid] == target 时可以立即返回

// 左边界
// 因为我们初始化 right = nums.length
// 所以决定了我们的「搜索区间」是 [left, right)
// 所以决定了 while (left < right)
// 同时也决定了 left = mid + 1 和 right = mid
// 因为我们需找到 target 的最左侧索引
// 所以当 nums[mid] == target 时不要立即返回
// 而要收紧右侧边界以锁定左侧边界

// 右边界
// 因为我们初始化 right = nums.length
// 所以决定了我们的「搜索区间」是 [left, right)
// 所以决定了 while (left < right)
// 同时也决定了 left = mid + 1 和 right = mid
// 因为我们需找到 target 的最右侧索引
// 所以当 nums[mid] == target 时不要立即返回
// 而要收紧左侧边界以锁定右侧边界
// 又因为收紧左侧边界时必须 left = mid + 1
// 所以最后无论返回 left 还是 right, 必须减一

int binary_search(int[] nums, int target) {
  int left = 0, right = nums.length - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] < target) {
      left = mid + 1;
    } else if (nums[mid] > target) {
      right = mid - 1;
    } else if (nums[mid] == target) {
      // 直接返回
      return mid;
    }
  }
  // 直接返回
  return -1;
}

int left_bound(int[] nums, int target) {
  int left = 0, right = nums.length - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] < target) {
      left = mid + 1;
    } else if (nums[mid] > target) {
      right = mid - 1;
    } else if (nums[mid] == target) {
      // 别返回，锁定左侧边界
      right = mid - 1;
    }
  }
  // 判断 target 是否存在于 nums 中
  // 此时 target 比所有数都大，返回 -1
  if (left == nums.length) return -1;
  // 判断一下 nums[left] 是不是 target
  return nums[left] == target ? left : -1;
}

int right_bound(int[] nums, int target) {
  int left = 0, right = nums.length - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] < target) {
      left = mid + 1;
    } else if (nums[mid] > target) {
      right = mid - 1;
    } else if (nums[mid] == target) {
      // 别返回，锁定右侧边界
      left = mid + 1;
    }
  }
  // 此时 left - 1 索引越界
  if (left - 1 < 0) return -1;
  // 判断一下 nums[left] 是不是 target
  return nums[left - 1] == target ? (left - 1) : -1;
}