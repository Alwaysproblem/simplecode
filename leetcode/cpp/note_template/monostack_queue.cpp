/*******************STACK************************/
int[] nextGreaterElement(int[] nums) {
  int n = nums.length;
  // 存放答案的数组
  int[] res = new int[n];
  Stack<Integer> s = new Stack<>();
  // 倒着往栈里放
  for (int i = n - 1; i >= 0; i--) {
    // 判定个子高矮
    while (!s.isEmpty() && s.peek() <= nums[i]) {
      // 矮个起开，反正也被挡着了。。。
      s.pop();
    }
    // nums[i] 身后的更大元素
    res[i] = s.isEmpty() ? -1 : s.peek();
    s.push(nums[i]);
  }
  return res;
}

/*******************QUEUE************************/
/* 单调队列的实现 */
class MonotonicQueue {
  LinkedList<Integer> maxq = new LinkedList<>();
 public
  void push(int n) {
    // 将小于 n 的元素全部删除
    while (!maxq.isEmpty() && maxq.getLast() < n) {
      maxq.pollLast();
    }
    // 然后将 n 加入尾部
    maxq.addLast(n);
  }

 public
  int max() { return maxq.getFirst(); }

 public
  void pop(int n) {
    if (n == maxq.getFirst()) {
      maxq.pollFirst();
    }
  }
}

/* 解题函数的实现 */
int[] maxSlidingWindow(int[] nums, int k) {
  MonotonicQueue window = new MonotonicQueue();
  List<Integer> res = new ArrayList<>();

  for (int i = 0; i < nums.length; i++) {
    if (i < k - 1) {
      //先填满窗口的前 k - 1
      window.push(nums[i]);
    } else {
      // 窗口向前滑动，加入新数字
      window.push(nums[i]);
      // 记录当前窗口的最大值
      res.add(window.max());
      // 移出旧数字
      window.pop(nums[i - k + 1]);
    }
  }
  // 需要转成 int[] 数组再返回
  int[] arr = new int[res.size()];
  for (int i = 0; i < res.size(); i++) {
    arr[i] = res.get(i);
  }
  return arr;
}
