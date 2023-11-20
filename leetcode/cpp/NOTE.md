# LeetCode 学习笔记

-------------

## 无重复字符的最长子串

给定一个字符串 `s` ，请你找出其中不含有重复字符的 最长子串的长度。

示例 1:

```

输入: s = "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

```

示例 2:

```

输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。

```

示例 3:

```

输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

```

提示：

* `0 <= s.length <= 5 * 104`
* `s` 由英文字母、数字、符号和空格组成

```cpp
class Solution {
 public:
  int lengthOfLongestSubstring(string s) {
    if (!s.size()) return 0;
    const int _INT_MIN_ = 0;
    unordered_map<char, int> window{};
    int left = 0, right = 0;
    char c = 0, d = 0;
    int start = 0, len = _INT_MIN_;
    while (right < s.size()) {
      char c = s[right];
      right++;
      window[c]++;
      if (window[c] == 1 && right - left > len) len = right - left;

      // fmt::print("({}, {})", left, right);

      while (left < right && window[c] > 1) {
        char d = s[left];
        left++;
        window[d]--;
      }
    }
    return len;
  }
};
```

-------------

## 岛屿数量

给你一个由 `'1'`（陆地）和 `'0'`（水）组成的的二维网格，请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。

示例 1：

```

输入：grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
输出：1

```

示例 2：

```

输入：grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
输出：3

```

提示：

* `m == grid.length`
* `n == grid[i].length`
* `1 <= m, n <= 300`
* `grid[i][j]` 的值为 `'0'` 或 `'1'`

```cpp
class UnionFind {
 public:
  UnionFind() = delete;
  UnionFind(int n) : count(n) {
    parent.reserve(n);
    for (int i = 0; i < n; i++) {
      parent.emplace_back(i);
    }
  }

  void Union(int p, int q) {
    int rootP = find(p);
    int rootQ = find(q);

    if (rootP == rootQ) return;
    parent[rootQ] = rootP;
    count--;
  }

  bool connected(int p, int q) { return find(p) == find(q); }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  int get_count() const { return count; }

  vector<int> get_parent() const { return parent; }

 private:
  int count;
  vector<int> parent;
};

class Solution {
 public:
  // -------------DFS----------------
  void dfs(vector<vector<char>>& grid, int i, int j,
           vector<vector<bool>>& visited) {
    int n = grid.size();
    int m = grid[0].size();

    if (i < 0 || j < 0 || j >= n || i >= m) return;
    if (visited[j][i]) return;
    if (grid[j][i] == '0') return;

    visited[j][i] = true;

    vector<pair<int, int>> actions = {
        {-1, 0},
        {0, -1},
        {1, 0},
        {0, 1},
    };

    int x = 0, y = 0;
    for (auto& p : actions) {
      x = p.first, y = p.second;
      dfs(grid, i + x, j + y, visited);
    }
  }

  int numIslands(vector<vector<char>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m));
    int cnt = 0;
    for (int row = 0; row < n; row++) {
      for (int col = 0; col < m; col++) {
        if (!visited[row][col] && grid[row][col] == '1') {
          dfs(grid, col, row, visited);
          cnt++;
        }
      }
    }

    // print2D(visited);
    return cnt;
  }

  // -------------Union Find-----------------
  int get_index(int row, int col, int m) { return col * m + row; }

  char get_value(vector<vector<char>>& grid, int i, int j) {
    int n = grid.size();
    int m = grid[0].size();
    if (i < 0 || i >= n) return '0';
    if (j < 0 || j >= m) return '0';
    return grid[i][j];
  }

  int numIslands_with_uf(vector<vector<char>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    UnionFind uf{n * m};
    vector<pair<int, int>> actions = {
        {-1, 0},
        {0, -1},
        {1, 0},
        {0, 1},
    };

    // collect the count number about single 1.
    // UnionFind can only find the multiple 1.
    // like this:
    //   0
    // 0 1 0
    //   0
    int single_1_count = 0;
    for (int col = 0; col < n; col++) {
      for (int row = 0; row < m; row++) {
        if (get_value(grid, col, row) == '1' &&
            get_value(grid, col - 1, row) == '0' &&
            get_value(grid, col, row - 1) == '0' &&
            get_value(grid, col + 1, row) == '0' &&
            get_value(grid, col, row + 1) == '0') {
          single_1_count++;
        }
      }
    }

    int x = 0, y = 0;
    for (int col = 0; col < n; col++) {
      for (int row = 0; row < m; row++) {
        for (auto& p : actions) {
          x = p.first, y = p.second;
          if (((row + x) >= 0 && (col + y) >= 0) &&
              ((row + x) < m && (col + y) < n))
            if (grid[col][row] == '1') {
              if (grid[col + y][row + x] == '1') {
                uf.Union(get_index(row, col, m),
                         get_index(row + x, col + y, m));
              }
            }
        }
      }
    }

    // update the parent of UnionFind.
    // this is important for get precise 1 block location.
    vector<vector<int>> board(n, vector<int>(m, -1));
    for (int col = 0; col < n; col++) {
      for (int row = 0; row < m; row++) {
        int idx = get_index(row, col, m);
        board[col][row] = uf.find(idx);
      }
    }

    vector<int> par = uf.get_parent();
    int multi_1_count = 0;
    unordered_map<int, int> counter{};
    for (const int pn : par) {
      counter[pn]++;
    }

    for (auto& c : counter) {
      if (c.second > 1) {
        multi_1_count++;
      }
    }

    // fmt::print("parents: {}\n", par);
    // fmt::print("single 1 count: {}\n", single_1_count);
    // fmt::print("counter: {}\n", counter);
    // fmt::print("multi_1_count: {}\n", multi_1_count);
    // print2D(board);
    // -----------
    //    1 1 1
    //    0 1 0
    //    1 1 1

    //    parents: [6, 6, 6, 3, 6, 5, 6, 6, 6]
    //    single 1 count: 0
    //    counter: {5: 1, 3: 1, 6: 7}
    //    multi_1_count: 1
    //    board:
    //      6 6 6
    //      3 6 5
    //      6 6 6

    return multi_1_count + single_1_count;
  }
};
```

-------------

## 二叉树的最小深度

给定一个二叉树，找出其最小深度。
最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
说明：叶子节点是指没有子节点的节点。

示例 1：
![](https://assets.leetcode.com/uploads/2020/10/12/ex_depth.jpg)

```

输入：root = [3,9,20,null,null,15,7]
输出：2

```

示例 2：

```

输入：root = [2,null,3,null,4,null,5,null,6]
输出：5

```

提示：

* 树中节点数的范围在 `[0, 105]` 内
* `-1000 <= Node.val <= 1000`

```cpp
class Solution {
 public:
  int minDepth(TreeNode *root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;

    queue<TreeNode *> q;
    q.push(root);
    TreeNode *cur = nullptr;

    int depth = 0;
    while (!q.empty()) {
      int sz = q.size();
      for (int ix = 0; ix < sz; ++ix) {
        cur = q.front();
        q.pop();
        if (cur->left == nullptr && cur->right == nullptr) {
          return depth + 1;
        }
        if (cur->left != nullptr) q.push(cur->left);
        if (cur->right != nullptr) q.push(cur->right);
      }
      depth++;
    }
    return depth;
  }
};
```

-------------

## 平衡括号字符串的最少插入次数

给你一个括号字符串 `s` ，它只包含字符 `'('` 和 `')'` 。一个括号字符串被称为平衡的当它满足：

* 任何左括号 `'('` 必须对应两个连续的右括号 `'))'` 。
* 左括号 `'('` 必须在对应的连续两个右括号 `'))'` 之前。

比方说 `"())"`， `"())(())))"` 和 `"(())())))"` 都是平衡的， `")()"`， `"()))"` 和 `"(()))"` 都是不平衡的。
你可以在任意位置插入字符 '(' 和 ')' 使字符串平衡。
请你返回让 `s` 平衡的最少插入次数。

示例 1：

```
输入：s = "(()))"
输出：1
解释：第二个左括号有与之匹配的两个右括号，但是第一个左括号只有一个右括号。我们需要在字符串结尾额外增加一个 ')' 使字符串变成平衡字符串 "(())))" 。

```

示例 2：

```
输入：s = "())"
输出：0
解释：字符串已经平衡了。

```

示例 3：

```
输入：s = "))())("
输出：3
解释：添加 '(' 去匹配最开头的 '))' ，然后添加 '))' 去匹配最后一个 '(' 。

```

示例 4：

```
输入：s = "(((((("
输出：12
解释：添加 12 个 ')' 得到平衡字符串。

```

示例 5：

```
输入：s = ")))))))"
输出：5
解释：在字符串开头添加 4 个 '(' 并在结尾添加 1 个 ')' ，字符串变成平衡字符串 "(((())))))))" 。

```

提示：

* `1 <= s.length <= 10^5`
* `s` 只包含 `'('` 和 `')'` 。

```cpp
class Solution {
 public:
  int minInsertions(string s) {
    int res = 0, need = 0;

    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '(') {
        need += 2;
        if (need % 2 == 1) {
          res++;
          need--;
        }
      }

      if (s[i] == ')') {
        need--;
        if (need == -1) {
          res++;
          need = 1;
        }
      }
    }

    return res + need;
  }
};
```

-------------

## 计数质数

给定整数 `n` ，返回 所有小于非负整数 `n` 的质数的数量 。

示例 1：

```

输入：n = 10
输出：4
解释：小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7 。

```

示例 2：

```

输入：n = 0
输出：0

```

示例 3：

```

输入：n = 1
输出：0

```

提示：

* `0 <= n <= 5 * 106`

```cpp
class Solution {
 public:
  int countPrimes(int n) {
    vector<bool> isPrime(n, true);
    int res = 0;
    for (int i = 2; i * i < n; i++) {
      if (isPrime[i]) {
        for (int j = i * i; j < n; j += i) {
          isPrime[j] = false;
        }
      }
    }
    // fmt::print("{}\n", isPrime);
    for (int i = 2; i < n; i++) {
      if (isPrime[i]) res += 1;
    }
    return res;
  }
};
```

-------------

## 两数之和

给定一个整数数组 `nums` 和一个整数目标值 `target`，请你在该数组中找出 和为目标值 `target`  的那 两个 整数，并返回它们的数组下标。
你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
你可以按任意顺序返回答案。

示例 1：

```

输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。

```

示例 2：

```

输入：nums = [3,2,4], target = 6
输出：[1,2]

```

示例 3：

```

输入：nums = [3,3], target = 6
输出：[0,1]

```

提示：

* `2 <= nums.length <= 104`
* `-109 <= nums[i] <= 109`
* `-109 <= target <= 109`
* 只会存在一个有效答案

进阶：你可以想出一个时间复杂度小于 `O(n2)` 的算法吗？

```cpp

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

```

-------------

## 完全二叉树的节点个数

给你一棵 完全二叉树 的根节点 `root` ，求出该树的节点个数。
[完全二叉树](https://baike.baidu.com/item/%E5%AE%8C%E5%85%A8%E4%BA%8C%E5%8F%89%E6%A0%91/7773232?fr=aladdin) 的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 `h` 层，则该层包含 `1~ 2h` 个节点。

示例 1：
![](https://assets.leetcode.com/uploads/2021/01/14/complete.jpg)

```

输入：root = [1,2,3,4,5,6]
输出：6

```

示例 2：

```

输入：root = []
输出：0

```

示例 3：

```

输入：root = [1]
输出：1

```

提示：

* 树中节点的数目范围是`[0, 5 * 104]`
* `0 <= Node.val <= 5 * 104`
* 题目数据保证输入的树是 完全二叉树

进阶：遍历树来统计节点是一种时间复杂度为 `O(n)` 的简单解决方案。你可以设计一个更快的算法吗？

```cpp
class Solution {
 public:
  int level = 0;
  int countNodes(TreeNode* root) {
    if (!root) return 0;
    int hl = 0;
    int hr = 0;
    TreeNode* cur = root;
    for (hl = 0; cur; cur = cur->left, hl++)
      ;

    cur = root;
    for (hr = 0; cur; cur = cur->right, hr++)
      ;
    if (hr == hl) return (int)pow(2, hr) - 1;

    return countNodes(root->left) + countNodes(root->right) + 1;
  }
};
```

-------------

## 让字符串成为回文串的最少插入次数

给你一个字符串 `s` ，每一次操作你都可以在字符串的任意位置插入任意字符。
请你返回让 `s` 成为回文串的 最少操作次数 。
「回文串」是正读和反读都相同的字符串。

示例 1：

```

输入：s = "zzazz"
输出：0
解释：字符串 "zzazz" 已经是回文串了，所以不需要做任何插入操作。

```

示例 2：

```

输入：s = "mbadm"
输出：2
解释：字符串可变为 "mbdadbm" 或者 "mdbabdm" 。

```

示例 3：

```

输入：s = "leetcode"
输出：5
解释：插入 5 个字符后字符串变为 "leetcodocteel" 。

```

提示：

* `1 <= s.length <= 500`
* `s` 中所有字符都是小写字母。

```cpp
class Solution {
 public:
  int minInsertions(string s) {
    if (!s.size()) return 0;
    vector<vector<int>> dp(s.size(), vector<int>(s.size()));
    for (int i = 0; i < s.size(); i++) {
      dp[i][i] = 0;
    }

    for (int start = s.size() - 1; start >= 0; start--) {
      for (int end = start + 1; end < s.size(); end++) {
        if (s[start] == s[end])
          dp[start][end] = dp[start + 1][end - 1];
        else
          dp[start][end] = min(dp[start + 1][end], dp[start][end - 1]) + 1;
      }
    }
    // fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    return dp.front().back();
  }
};
```

-------------

## 链表随机节点

给你一个单链表，随机选择链表的一个节点，并返回相应的节点值。每个节点 被选中的概率一样 。
实现 `Solution` 类：

* `Solution(ListNode head)` 使用整数数组初始化对象。
* `int getRandom()` 从链表中随机选择一个节点并返回该节点的值。链表中所有节点被选中的概率相等。

示例：
![](https://assets.leetcode.com/uploads/2021/03/16/getrand-linked-list.jpg)

```

输入
["Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"]
[[[1, 2, 3]], [], [], [], [], []]
输出
[null, 1, 3, 2, 2, 3]

解释
Solution solution = new Solution([1, 2, 3]);
solution.getRandom(); // 返回 1
solution.getRandom(); // 返回 3
solution.getRandom(); // 返回 2
solution.getRandom(); // 返回 2
solution.getRandom(); // 返回 3
// getRandom() 方法应随机返回 1、2、3中的一个，每个元素被返回的概率相等。
```

提示：

* 链表中的节点数在范围 `[1, 104]` 内
* `-104 <= Node.val <= 104`
* 至多调用 `getRandom` 方法 `104` 次

进阶：

* 如果链表非常大且长度未知，该怎么处理？
* 你能否在不使用额外空间的情况下解决此问题？

```cpp
class Solution {
 public:
  ListNode *head_;
  Solution(ListNode *head) : head_(head) {}

  int getRandom(ListNode *cur_head = nullptr) {
    if (!cur_head) {
      cur_head = head_;
    }
    int i = 0, res = 0;
    for (ListNode *cur = cur_head; cur != nullptr; cur = cur->next) {
      i++;
      if (0 == (rand() % i)) {
        res = cur->val;
      }
    }
    return res;
  }
  vector<int> getKRandom(int k = 1, ListNode *cur_head = nullptr) {
    if (!cur_head) {
      cur_head = head_;
    }
    vector<int> res(k);
    ListNode *p = cur_head;
    for (int i = 0; i < k; i++) {
      res[i] = p->val;
      p = p->next;
    }

    int i = 0, j = 0;
    for (ListNode *cur = cur_head; cur != nullptr; cur = cur->next) {
      i++;
      j = rand() % i;
      if (k > j) {
        res[j++] = cur->val;
      }
    }
    return res;
  }
};
```

-------------

## 打家劫舍 II

你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都 围成一圈 ，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。
给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下 ，今晚能够偷窃到的最高金额。

示例 1：

```

输入：nums = [2,3,2]
输出：3
解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。

```

示例 2：

```

输入：nums = [1,2,3,1]
输出：4
解释：你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。
     偷窃到的最高金额 = 1 + 3 = 4 。
```

示例 3：

```

输入：nums = [1,2,3]
输出：3

```

提示：

* `1 <= nums.length <= 100`
* `0 <= nums[i] <= 1000`

```cpp
class Solution {
 public:
  int robRange(vector<int>& nums, int start, int end) {
    vector<int> dp(nums.size() + 1);
    dp[0] = 0;
    for (int i = start + 1; i <= end; i++) {
      if (i - 2 > 0)
        dp[i] = max(dp[i - 1], dp[i - 2] + nums[i - 1]);
      else
        dp[i] = max(dp[i - 1], dp[0] + nums[i - 1]);
    }
    // fmt::print("{}\n", dp);
    return dp[end];
  }

  int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    // choose all.
    int s1 = robRange(nums, 1, n - 1);
    // choose all but the last one since this is loop.
    int s2 = robRange(nums, 1, n - 2) + nums[n - 1];
    // choose all but the first one.
    int s3 = robRange(nums, 2, n - 1) + nums[0];
    // fmt::print("{}, {}, {}\n", s1, s2, s3);
    return max(max(s1, s2), s3);
  }
};
```

-------------

## 反转链表

给你单链表的头节点 `head` ，请你反转链表，并返回反转后的链表。

示例 1：
![](https://assets.leetcode.com/uploads/2021/02/19/rev1ex1.jpg)

```

输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]

```

示例 2：
![](https://assets.leetcode.com/uploads/2021/02/19/rev1ex2.jpg)

```

输入：head = [1,2]
输出：[2,1]

```

示例 3：

```

输入：head = []
输出：[]

```

提示：

* 链表中节点的数目范围是 `[0, 5000]`
* `-5000 <= Node.val <= 5000`

进阶：链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？

```cpp
class Solution {
 public:
  // method 1
  ListNode* reverseList(ListNode* head) {
    if (!head) return nullptr;
    if (!head->next) {
      return head;
    }
    ListNode* tail = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return tail;
  }

  // method 2
  // `ListNode* &tail_ptr` This is the reference of ListNode ptr.
  // with this `tail_ptr = head;` can be worked or every time the code
  // use the `tail_ptr` will be a copy of value not reference.
  ListNode* reverseList1_helper(ListNode* head, ListNode*& tail_ptr) {
    if (!head) return nullptr;
    if (!head->next) {
      tail_ptr = head;
      return head;
    }
    ListNode* tail = reverseList1_helper(head->next, tail_ptr);
    tail->next = head;
    head->next = nullptr;
    return head;
  }

  ListNode* reverseList1(ListNode* head) {
    ListNode* tail_ptr = nullptr;
    reverseList1_helper(head, tail_ptr);
    return tail_ptr;
  }

  // method 3
  ListNode* reverseList2(ListNode* head) {
    if (!head) return nullptr;
    if (!head->next) {
      return head;
    }
    ListNode* cur = head;
    ListNode* nex = nullptr;
    ListNode* pre = nullptr;
    while (cur->next) {
      nex = cur->next;
      cur->next = pre;
      pre = cur;
      cur = nex;
    }
    cur->next = pre;
    return cur;
  }
};
```

-------------

## 最小覆盖子串

给你一个字符串 `s` 、一个字符串 `t` 。返回 `s` 中涵盖 `t` 所有字符的最小子串。如果 `s` 中不存在涵盖 `t` 所有字符的子串，则返回空字符串 `""` 。

注意：

* 对于 `t` 中重复字符，我们寻找的子字符串中该字符数量必须不少于 `t` 中该字符数量。
* 如果 `s` 中存在这样的子串，我们保证它是唯一的答案。

示例 1：

```

输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。

```

示例 2：

```

输入：s = "a", t = "a"
输出："a"
解释：整个字符串 s 是最小覆盖子串。

```

示例 3:

```

输入: s = "a", t = "aa"
输出: ""
解释: t 中两个字符 'a' 均应包含在 s 的子串中，
因此没有符合条件的子字符串，返回空字符串。
```

提示：

* `m == s.length`
* `n == t.length`
* `1 <= m, n <= 105`
* `s` 和 `t` 由英文字母组成

进阶：你能设计一个在 `o(m+n)` 时间内解决此问题的算法吗？

```cpp
class Solution {
 public:
  string minWindow(string s, string t) {
    if (s.size() == 0 || t.size() == 0) return "";
    unordered_map<char, int> need{}, window{};
    const int INTMAX = s.size() + 1;
    for (char c : t) need[c]++;
    int left = 0, right = 0;
    char c = 0;
    char d = 0;
    int start = 0, len = INTMAX;
    int valid = 0;
    while (right < s.size()) {
      c = s[right];
      right++;

      // window.add(right)
      if (need.count(c)) {
        window[c]++;
        if (window[c] == need[c]) valid++;
      }

      // fmt::print("({}, {})\n", left, right);

      while (valid == need.size()) {
        if (len > right - left) {
          start = left;
          len = right - left;
        }
        d = s[left];
        left++;
        // window.remove(left);
        if (need.count(d)) {
          if (window[d] == need[d]) valid--;
          window[d]--;
        }
      }
    }
    // fmt::print("len: {} start: {}\n", len, start);
    return len == INTMAX ? "" : s.substr(start, len);
  }
};
```

-------------

## 最长公共子序列

给定两个字符串 `text1` 和 `text2`，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 `0` 。
一个字符串的 子序列是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。

* 例如，`"ace"` 是 `"abcde"` 的子序列，但 `"aec"` 不是 `"abcde"` 的子序列。

两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。

示例 1：

```

输入：text1 = "abcde", text2 = "ace" 
输出：3  
解释：最长公共子序列是 "ace" ，它的长度为 3 。

```

示例 2：

```

输入：text1 = "abc", text2 = "abc"
输出：3
解释：最长公共子序列是 "abc" ，它的长度为 3 。

```

示例 3：

```

输入：text1 = "abc", text2 = "def"
输出：0
解释：两个字符串没有公共子序列，返回 0 。

```

提示：

* `1 <= text1.length, text2.length <= 1000`
* `text1` 和 `text2` 仅由小写英文字符组成。

```cpp
class Solution {
 public:
  int longestCommonSubsequence(string text1, string text2) {
    vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1, 0));
    for (int i = 1; i <= text1.size(); i++) {
      for (int j = 1; j <= text2.size(); j++) {
        if (text1[i - 1] == text2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
        } else {
          dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
      }
    }
    // print2D(dp);
    // fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    return dp.back().back();
  }
};
```

-------------

## 编辑距离

给你两个单词 `word1` 和 `word2`， 请返回将 `word1` 转换成 `word2` 所使用的最少操作数  。
你可以对一个单词进行如下三种操作：

* 插入一个字符
* 删除一个字符
* 替换一个字符

示例 1：

```

输入：word1 = "horse", word2 = "ros"
输出：3
解释：
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')

```

示例 2：

```

输入：word1 = "intention", word2 = "execution"
输出：5
解释：
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')

```

提示：

* `0 <= word1.length, word2.length <= 500`
* `word1` 和 `word2` 由小写英文字母组成

```cpp
class Solution {
 public:
  enum Choice { INSERT = 0, REPLACE, DELETE, SKIP };

  int record_action(int deletion, int insertion, int replacement) {
    Choice c = Choice::DELETE;
    if (deletion > insertion) {
      c = Choice::INSERT;
    }
    if (deletion > replacement) {
      c = Choice::REPLACE;
    }
    return c;
  }

  int minDistance(string word1, string word2) {
    vector<vector<int>> dp(word2.size() + 1, vector<int>(word1.size() + 1));
    vector<vector<int>> actions(word2.size() + 1,
                                vector<int>(word1.size() + 1));
    Choice c;
    for (int i = 1; i <= word1.size(); i++) {
      dp[0][i] = i;
      actions[0][i] = Choice::DELETE;
    }
    for (int i = 1; i <= word2.size(); i++) {
      dp[i][0] = i;
      actions[i][0] = Choice::INSERT;
    }
    for (int row = 1; row <= word2.size(); row++) {
      for (int col = 1; col <= word1.size(); col++) {
        if (word2[row - 1] == word1[col - 1]) {
          dp[row][col] = dp[row - 1][col - 1];  // skip
          actions[row][col] = Choice::SKIP;     // skip
        } else {
          dp[row][col] = min(min(dp[row - 1][col],       // insertion
                                 dp[row - 1][col - 1]),  // replacement
                             dp[row][col - 1]            // deletion
                             ) +
                         1;

          actions[row][col] = record_action(dp[row][col - 1], dp[row - 1][col],
                                            dp[row - 1][col - 1]);
        }
      }
    }
    // print_solution(word1, word2, actions);
    return dp.back().back();
  }
};
```

-------------

## 子集

给你一个整数数组 `nums` ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。
解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

示例 1：

```

输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

```

示例 2：

```

输入：nums = [0]
输出：[[],[0]]

```

提示：

* `1 <= nums.length <= 10`
* `-10 <= nums[i] <= 10`
* `nums` 中的所有元素 互不相同

```cpp
class Solution {
 public:
  vector<vector<int>> res{};
  unordered_map<int, int> visited{};
  vector<vector<int>> subsets(vector<int>& nums) {
    vector<int> sol{};
    backtrack(nums, 0, sol);
    return res;
  }

  void backtrack(vector<int>& nums, int candidate_idx, vector<int>& solution) {
    if (candidate_idx > nums.size()) return;
    res.push_back(vector<int>(solution));
    for (int i = candidate_idx; i < nums.size(); i++) {
      solution.push_back(nums[i]);
      backtrack(nums, i + 1, solution);
      solution.pop_back();
    }
  }
};
```

-------------

## 反转链表 II

给你单链表的头指针 `head` 和两个整数 `left` 和 `right` ，其中 `left <= right` 。请你反转从位置 `left` 到位置 `right` 的链表节点，返回 反转后的链表 。

示例 1：
![](https://assets.leetcode.com/uploads/2021/02/19/rev2ex2.jpg)

```

输入：head = [1,2,3,4,5], left = 2, right = 4
输出：[1,4,3,2,5]

```

示例 2：

```

输入：head = [5], left = 1, right = 1
输出：[5]

```

提示：

* 链表中节点数目为 `n`
* `1 <= n <= 500`
* `-500 <= Node.val <= 500`
* `1 <= left <= right <= n`

进阶： 你可以使用一趟扫描完成反转吗？

```cpp
class Solution {
 public:
  ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode* dummyNode = new ListNode(-1);
    dummyNode->next = head;
    ListNode* pre = dummyNode;
    for (int i = 0; i < left - 1; i++) {
      pre = pre->next;
    }
    ListNode* cur = pre->next;
    ListNode* next = nullptr;
    for (int i = 0; i < right - left; i++) {
      next = cur->next;
      cur->next = next->next;
      next->next =
          pre->next;  // ! here, from second iteration the `cur` != `pre->next`.
      pre->next = next;
    }
    ListNode* ret = dummyNode->next;
    delete dummyNode;
    return ret;
  }
};
```

-------------

## 二叉搜索树中的插入操作

给定二叉搜索树（BST）的根节点 `root` 和要插入树中的值 `value` ，将值插入二叉搜索树。 返回插入后二叉搜索树的根节点。 输入数据 保证 ，新值和原始二叉搜索树中的任意节点值都不同。
注意，可能存在多种有效的插入方式，只要树在插入后仍保持为二叉搜索树即可。 你可以返回 任意有效的结果 。

示例 1：
![](https://assets.leetcode.com/uploads/2020/10/05/insertbst.jpg)

```

输入：root = [4,2,7,1,3], val = 5
输出：[4,2,7,1,3,5]
解释：另一个满足题目要求可以通过的树是：
![](https://assets.leetcode.com/uploads/2020/10/05/bst.jpg)

```

示例 2：

```

输入：root = [40,20,60,10,30,50,70], val = 25
输出：[40,20,60,10,30,50,70,null,null,25]

```

示例 3：

```

输入：root = [4,2,7,1,3,null,null,null,null,null,null], val = 5
输出：[4,2,7,1,3,5]

```

提示：

* 树中的节点数将在 `[0, 104]`的范围内。
* `-108 <= Node.val <= 108`
* 所有值 `Node.val` 是 独一无二 的。
* `-108 <= val <= 108`
* 保证 `val` 在原始BST中不存在。

```cpp
class Solution {
 public:
  TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (root->val == val) return root;
    if (val < root->val)
      root->left = insertIntoBST(root->left, val);
    else
      root->right = insertIntoBST(root->right, val);
    return root;
  }
};
```

-------------

## 戳气球

有 `n` 个气球，编号为`0` 到 `n - 1`，每个气球上都标有一个数字，这些数字存在数组 `nums` 中。
现在要求你戳破所有的气球。戳破第 `i` 个气球，你可以获得 `nums[i - 1] * nums[i] * nums[i + 1]` 枚硬币。 这里的 `i - 1` 和 `i + 1` 代表和 `i` 相邻的两个气球的序号。如果 `i - 1`或 `i + 1` 超出了数组的边界，那么就当它是一个数字为 `1` 的气球。
求所能获得硬币的最大数量。

示例 1：

```

输入：nums = [3,1,5,8]
输出：167
解释：
nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
```

示例 2：

```

输入：nums = [1,5]
输出：10

```

提示：

* `n == nums.length`
* `1 <= n <= 300`
* `0 <= nums[i] <= 100`

```cpp
class Solution {
 public:
  int maxCoins(vector<int>& nums) {
    int n = nums.size();
    vector<int> scores(nums.size() + 2, 1);
    for (int i = 1; i <= nums.size(); i++) {
      scores[i] = nums[i - 1];
    }

    vector<vector<int>> dp(scores.size(), vector<int>(scores.size(), 0));
    for (int i = n; i >= 0; i--) {
      for (int j = i + 1; j < n + 2; j++) {
        for (int k = i + 1; k < j; k++) {
          // i OOO k OOO j
          // i {dp[i][k]} k {dp[k][j]} j
          // if we got dp[i][k] and dp[k][j]
          // then all balloons between i and k have been burst
          // as well as those between k and j.
          // so the maximum coins we can get is the sum of dp[i][k], dp[k][j]
          // and scores[i] * scores[k] * scores[j]
          dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] +
                                       scores[i] * scores[k] * scores[j]);
        }
      }
    }
    // fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    return dp.front().back();
  }
};
```

-------------

## 用最少数量的箭引爆气球

有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组 `points` ，其中`points[i] = [xstart, xend]` 表示水平直径在 `xstart` 和 `xend`之间的气球。你不知道气球的确切 y 坐标。
一支弓箭可以沿着 x 轴从不同点 完全垂直 地射出。在坐标 `x` 处射出一支箭，若有一个气球的直径的开始和结束坐标为 `x``start`，`x``end`， 且满足  `xstart ≤ x ≤ x``end`，则该气球会被 引爆 。可以射出的弓箭的数量 没有限制 。 弓箭一旦被射出之后，可以无限地前进。
给你一个数组 `points` ，返回引爆所有气球所必须射出的 最小 弓箭数。

示例 1：

```

输入：points = [[10,16],[2,8],[1,6],[7,12]]
输出：2
解释：气球可以用2支箭来爆破:
-在x = 6处射出箭，击破气球[2,8]和[1,6]。
-在x = 11处发射箭，击破气球[10,16]和[7,12]。
```

示例 2：

```

输入：points = [[1,2],[3,4],[5,6],[7,8]]
输出：4
解释：每个气球需要射出一支箭，总共需要4支箭。
```

示例 3：

```

输入：points = [[1,2],[2,3],[3,4],[4,5]]
输出：2
解释：气球可以用2支箭来爆破:
- 在x = 2处发射箭，击破气球[1,2]和[2,3]。
- 在x = 4处射出箭，击破气球[3,4]和[4,5]。
```

提示:

* `1 <= points.length <= 105`
* `points[i].length == 2`
* `-231 <= xstart < xend <= 231 - 1`

```cpp
class Solution {
 public:
  int findMinArrowShots(vector<vector<int>>& points) {
    sort(points.begin(), points.end(),
         [](vector<int>& a, vector<int>& b) { return a[0] < b[0]; });
    int arrows = 1;
    int start = points[0][0], end = points[0][1];
    for (int i = 1; i < points.size(); i++) {
      int a = points[i][0];
      int b = points[i][1];
      if (a > end) {
        arrows++;
        start = a;
        end = b;
      } else {
        start = max(start, a);
        end = min(end, b);
      }
    }
    return arrows;
  }
};
```

-------------

## 找到字符串中所有字母异位词

给定两个字符串 `s` 和 `p`，找到 `s`中所有 `p`的 异位词的子串，返回这些子串的起始索引。不考虑答案输出的顺序。
异位词 指由相同字母重排列形成的字符串（包括相同的字符串）。

示例 1:

```

输入: s = "cbaebabacd", p = "abc"
输出: [0,6]
解释:
起始索引等于 0 的子串是 "cba", 它是 "abc" 的异位词。
起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词。

```

示例 2:

```

输入: s = "abab", p = "ab"
输出: [0,1,2]
解释:
起始索引等于 0 的子串是 "ab", 它是 "ab" 的异位词。
起始索引等于 1 的子串是 "ba", 它是 "ab" 的异位词。
起始索引等于 2 的子串是 "ab", 它是 "ab" 的异位词。

```

提示:

* `1 <= s.length, p.length <= 3 * 104`
* `s` 和 `p` 仅包含小写字母

```cpp
class Solution {
 public:
  vector<int> findAnagrams(string s, string p) {
    if (!s.size() || !p.size()) return vector<int>();
    if (s.size() < p.size()) return vector<int>();
    unordered_map<char, int> need{}, window{};
    for (char t : p) need[t]++;
    int left = 0, right = 0;
    char c = '0', d = '0';
    int start = 0, valid = 0;
    vector<int> starts{};
    while (right < s.size()) {
      c = s[right];
      right++;

      if (need.count(c)) {
        window[c]++;
        if (need[c] == window[c]) valid++;
      }

      // fmt::print("({}, {})\n", left, right);

      while (left < right && right - left == p.size()) {
        if (valid == need.size()) {
          start = left;
          starts.push_back(start);
        }

        d = s[left];
        left++;
        if (need.count(d)) {
          if (need[d] == window[d]) valid--;
          window[d]--;
        }
      }
    }
    return starts;
  }
};
```

-------------

## 计算右侧小于当前元素的个数

给你一个整数数组 `nums`，按要求返回一个新数组 `counts`。数组 `counts` 有该性质： `counts[i]` 的值是  `nums[i]` 右侧小于 `nums[i]` 的元素的数量。

示例 1：

```

输入：nums = [5,2,6,1]
输出：[2,1,1,0] 
解释：
5 的右侧有 2 个更小的元素 (2 和 1)
2 的右侧仅有 1 个更小的元素 (1)
6 的右侧有 1 个更小的元素 (1)
1 的右侧有 0 个更小的元素

```

示例 2：

```

输入：nums = [-1]
输出：[0]

```

示例 3：

```

输入：nums = [-1,-1]
输出：[0,0]

```

提示：

* `1 <= nums.length <= 105`
* `-104 <= nums[i] <= 104`

```cpp
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
```

-------------

## 无重叠区间

给定一个区间的集合 `intervals` ，其中 `intervals[i] = [starti, endi]` 。返回 需要移除区间的最小数量，使剩余区间互不重叠。

示例 1:

```

输入: intervals = [[1,2],[2,3],[3,4],[1,3]]
输出: 1
解释: 移除 [1,3] 后，剩下的区间没有重叠。

```

示例 2:

```

输入: intervals = [ [1,2], [1,2], [1,2] ]
输出: 2
解释: 你需要移除两个 [1,2] 来使剩下的区间没有重叠。

```

示例 3:

```

输入: intervals = [ [1,2], [2,3] ]
输出: 0
解释: 你不需要移除任何区间，因为它们已经是无重叠的了。

```

提示:

* `1 <= intervals.length <= 105`
* `intervals[i].length == 2`
* `-5 * 104 <= starti < endi <= 5 * 104`

```cpp
class Solution {
 public:
  int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;

    sort(
        intervals.begin(), intervals.end(),
        [](const vector<int>& a, const vector<int>& b) { return a[1] < b[1]; });

    int end = intervals[0][1];
    int count = 0;

    for (int i = 1; i < intervals.size(); i++) {
      if (intervals[i][0] >= end) {
        end = intervals[i][1];
      } else {
        count++;
        end = min(end, intervals[i][1]);
      }
    }

    return count;
  }
};
```

-------------

## 等式方程的可满足性

给定一个由表示变量之间关系的字符串方程组成的数组，每个字符串方程 `equations[i]` 的长度为 `4`，并采用两种不同的形式之一：`"a==b"` 或 `"a!=b"`。在这里，a 和 b 是小写字母（不一定不同），表示单字母变量名。
只有当可以将整数分配给变量名，以便满足所有给定的方程时才返回 `true`，否则返回 `false`。

示例 1：

```
输入：["a==b","b!=a"]
输出：false
解释：如果我们指定，a = 1 且 b = 1，那么可以满足第一个方程，但无法满足第二个方程。没有办法分配变量同时满足这两个方程。

```

示例 2：

```
输入：["b==a","a==b"]
输出：true
解释：我们可以指定 a = 1 且 b = 1 以满足满足这两个方程。

```

示例 3：

```
输入：["a==b","b==c","a==c"]
输出：true

```

示例 4：

```
输入：["a==b","b!=c","c==a"]
输出：false

```

示例 5：

```
输入：["c==c","b==d","x!=z"]
输出：true

```

提示：

1. `1 <= equations.length <= 500`
2. `equations[i].length == 4`
3. `equations[i][0]` 和 `equations[i][3]` 是小写字母
4. `equations[i][1]` 要么是 `'='`，要么是 `'!'`
5. `equations[i][2]` 是 `'='`

```cpp
class UnionFind {
 public:
  UnionFind() = delete;
  UnionFind(int n) : count(n) {
    parent.reserve(n);
    for (int i = 0; i < n; i++) {
      parent.emplace_back(i);
    }
  }

  void Union(int p, int q) {
    int rootP = find(p);
    int rootQ = find(q);

    if (rootP == rootQ) return;
    parent[rootQ] = rootP;
    count--;
  }

  bool connected(int p, int q) { return find(p) == find(q); }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  int get_count() const { return count; }

 private:
  int count;
  vector<int> parent;
};

class Solution {
 public:
  bool equationsPossible(vector<string>& equations) {
    UnionFind uf(26);
    char lhs = 0, rhs = 0;
    for (string &e : equations){
      lhs = e.at(0);
      rhs = e.at(3);
      if (e.at(1) == '=')
        uf.Union(lhs - 'a', rhs - 'a');
    }

    for (string &e : equations){
      lhs = e.at(0);
      rhs = e.at(3);
      if (e.at(1) == '!')
        if (uf.connected(lhs - 'a', rhs - 'a'))
          return false;
    }

    return true;
  }
};
```

-------------

## 数组中的第K个最大元素

给定整数数组 `nums` 和整数 `k`，请返回数组中第 `k` 个最大的元素。
请注意，你需要找的是数组排序后的第 `k` 个最大的元素，而不是第 `k` 个不同的元素。
你必须设计并实现时间复杂度为 `O(n)` 的算法解决此问题。

示例 1:

```

输入: [3,2,1,5,6,4], k = 2
输出: 5

```

示例 2:

```

输入: [3,2,3,1,2,4,5,5,6], k = 4
输出: 4
```

提示：

* `1 <= k <= nums.length <= 105`
* `-104 <= nums[i] <= 104`

```cpp
struct Compare {
  bool operator()(const int a, const int b) const { return a > b; }
};

class Solution {
 public:
  int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, Compare> pq;
    for (int i : nums) {
      if (pq.size() < k) pq.push(i);
      else{
        if (i > pq.top()) pq.push(i);
        if (pq.size() > k) pq.pop();
      }
    }
    return pq.top();
  }
};
```

-------------

## 二叉搜索树中的搜索

给定二叉搜索树（BST）的根节点 `root` 和一个整数值 `val`。
你需要在 BST 中找到节点值等于 `val` 的节点。 返回以该节点为根的子树。 如果节点不存在，则返回 `null` 。

示例 1:
![](https://assets.leetcode.com/uploads/2021/01/12/tree1.jpg)

```

输入：root = [4,2,7,1,3], val = 2
输出：[2,1,3]

```

示例 2:
![](https://assets.leetcode.com/uploads/2021/01/12/tree2.jpg)

```

输入：root = [4,2,7,1,3], val = 5
输出：[]

```

提示：

* 数中节点数在 `[1, 5000]` 范围内
* `1 <= Node.val <= 107`
* `root` 是二叉搜索树
* `1 <= val <= 107`

```cpp
class Solution {
 public:
  TreeNode* searchBST(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (root->val == val) return root;
    if (val < root->val) return searchBST(root->left, val);
    if (val > root->val) return searchBST(root->right, val);
    return nullptr;
  }
};
```

-------------

## 网络延迟时间

有 `n` 个网络节点，标记为 `1` 到 `n`。
给你一个列表 `times`，表示信号经过 有向 边的传递时间。 `times[i] = (ui, vi, wi)`，其中 `ui` 是源节点，`vi` 是目标节点， `wi` 是一个信号从源节点传递到目标节点的时间。
现在，从某个节点 `K` 发出一个信号。需要多久才能使所有节点都收到信号？如果不能使所有节点收到信号，返回 `-1` 。

示例 1：
![](https://assets.leetcode.com/uploads/2019/05/23/931_example_1.png)

```

输入：times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
输出：2

```

示例 2：

```

输入：times = [[1,2,1]], n = 2, k = 1
输出：1

```

示例 3：

```

输入：times = [[1,2,1]], n = 2, k = 2
输出：-1

```

提示：

* `1 <= k <= n <= 100`
* `1 <= times.length <= 6000`
* `times[i].length == 3`
* `1 <= ui, vi <= n`
* `ui != vi`
* `0 <= wi <= 100`
* 所有 `(ui, vi)` 对都 互不相同（即，不含重复边）

```cpp
class Solution {
 public:
  vector<vector<int>> graph;
  vector<vector<int>> adjacent(int node) {
    vector<vector<int>> adj{};
    for (int i = 1; i < graph[node].size(); i++) {
      if (graph[node][i] != -1) {
        adj.push_back(vector<int>{i, graph[node][i]});
      }
    }
    return adj;
  }

  void relax(vector<int> &cost, vector<int> &prev, int parent, int child,
             int weight) {
    cost[child] = cost[parent] + weight;
    prev[child] = parent;
  }

  int networkDelayTime(vector<vector<int>> &times, int n, int k) {
    // setup Graph
    graph.assign(n + 1, vector<int>(n + 1, -1));
    for (vector<int> &x : times) {
      if (x[0] < 1 || x[0] > n) {
        // fmt::print("Error!");
        return -1;
      } else if (x[1] < 1 || x[1] > n) {
        // fmt::print("Error!");
        return -1;
      } else {
        graph.at(x[0]).at(x[1]) = x[2];
      }
    }
    queue<int> q{};
    vector<int> cost(n + 1, INT_MAX);
    vector<int> prev(n + 1, -1);
    // vector<bool> visited(n + 1, false);
    unordered_set<int> visited{};
    q.emplace(k);
    cost[k] = 0;
    cost[0] = 0;
    int depth = 0;
    int cur = -1;
    int nxt_node = -1;
    int nxt_weight = INT_MAX;
    while (visited.size() <= n && !q.empty()) {
      int sz = q.size();
      for (int j = 0; j < sz; j++) {
        cur = q.front();
        q.pop();
        // visited[cur] = true;
        visited.insert(cur);
        for (vector<int> &nxt : adjacent(cur)) {
          nxt_node = nxt[0];
          nxt_weight = nxt[1];
          if (cost[cur] + nxt_weight < cost[nxt_node]) {
            relax(cost, prev, cur, nxt_node, nxt_weight);
            q.emplace(nxt_node);
          }
        }
      }
      depth++;
    }
    // fmt::print("{}\n", cost);
    // fmt::print("{}\n", prev);
    // print_path(prev, 3);
    for (int j = 1; j < prev.size(); j++) {
      if (j != k && prev[j] == -1) return -1;
    }
    int max_val = 0;
    for (int j : cost) {
      if (j != INT_MAX && j > max_val) max_val = j;
    }
    return max_val;
  }
};
```

-------------

## 每日温度

给定一个整数数组 `temperatures` ，表示每天的温度，返回一个数组 `answer` ，其中 `answer[i]` 是指对于第 `i` 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 `0` 来代替。

示例 1:

```

输入: temperatures = [73,74,75,71,69,72,76,73]
输出: [1,1,4,2,1,1,0,0]

```

示例 2:

```

输入: temperatures = [30,40,50,60]
输出: [1,1,1,0]

```

示例 3:

```

输入: temperatures = [30,60,90]
输出: [1,1,0]
```

提示：

* `1 <= temperatures.length <= 105`
* `30 <= temperatures[i] <= 100`

```cpp
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
```

-------------

## 所有可能的路径

给你一个有 `n` 个节点的 有向无环图（DAG），请你找出所有从节点 `0` 到节点 `n-1` 的路径并输出（不要求按特定顺序）
 `graph[i]` 是一个从节点 `i` 可以访问的所有节点的列表（即从节点 `i` 到节点 `graph[i][j]`存在一条有向边）。

示例 1：
![](https://assets.leetcode.com/uploads/2020/09/28/all_1.jpg)

```

输入：graph = [[1,2],[3],[3],[]]
输出：[[0,1,3],[0,2,3]]
解释：有两条路径 0 -> 1 -> 3 和 0 -> 2 -> 3

```

示例 2：
![](https://assets.leetcode.com/uploads/2020/09/28/all_2.jpg)

```

输入：graph = [[4,3,1],[3,2,4],[3],[4],[]]
输出：[[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]

```

提示：

* `n == graph.length`
* `2 <= n <= 15`
* `0 <= graph[i][j] < n`
* `graph[i][j] != i`（即不存在自环）
* `graph[i]` 中的所有元素 互不相同
* 保证输入为 有向无环图（DAG）

```cpp

class Solution {
 public:
  vector<bool> visited{};
  vector<vector<int>> paths = {};
  vector<int> neighbour(vector<vector<int>>& graph, int node) {
    return graph[node];
  }

  void DFS(vector<vector<int>>& graph, int node, vector<int>& path) {
    if (node >= graph.size() || node < 0) return;
    if (visited[node]) return;
    if (0 == neighbour(graph, node).size() || node == graph.size() - 1) {
      if (node != graph.size() - 1) return;
      path.push_back(node);
      paths.push_back(vector<int>(path));
      path.pop_back();
      return;
    }
    path.push_back(node);
    for (int child : neighbour(graph, node)) {
      DFS(graph, child, path);
    }
    path.pop_back();
    // visited[node] = true;
  }

  vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    visited.assign(graph.size(), false);
    visited.reserve(graph.size());
    vector<int> path{};
    DFS(graph, 0, path);
    return paths;
  }
};

```

-------------

## 环形链表

给你一个链表的头节点 `head` ，判断链表中是否有环。
如果链表中有某个节点，可以通过连续跟踪 `next` 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 `pos` 来表示链表尾连接到链表中的位置（索引从 0 开始）。注意：`pos` 不作为参数进行传递。仅仅是为了标识链表的实际情况。
如果链表中存在环 ，则返回 `true` 。 否则，返回 `false` 。

示例 1：
![](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/07/circularlinkedlist.png)

```

输入：head = [3,2,0,-4], pos = 1
输出：true
解释：链表中有一个环，其尾部连接到第二个节点。

```

示例 2：
![](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/07/circularlinkedlist_test2.png)

```

输入：head = [1,2], pos = 0
输出：true
解释：链表中有一个环，其尾部连接到第一个节点。

```

示例 3：
![](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/07/circularlinkedlist_test3.png)

```

输入：head = [1], pos = -1
输出：false
解释：链表中没有环。

```

提示：

* 链表中节点的数目范围是 `[0, 104]`
* `-105 <= Node.val <= 105`
* `pos` 为 `-1` 或者链表中的一个 有效索引 。

进阶：你能用 `O(1)`（即，常量）内存解决此问题吗？

```cpp
class Solution {
 public:
  ListNode *hasCycle(ListNode *head) {
    if (head == nullptr) return nullptr;
    ListNode *slow = head, *fast = head;
    while (slow->next != nullptr && fast->next != nullptr &&
           fast->next->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast) {
        break;
      }
    }

    if (slow->next == nullptr) return nullptr;
    if (fast->next == nullptr) return nullptr;
    if (fast->next->next == nullptr) return nullptr;

    ListNode *res = head;
    while (res != slow) {
      res = res->next;
      slow = slow->next;
    }
    return res;
  }
};
```

-------------

## 二叉树的最近公共祖先

给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
[百度百科](https://baike.baidu.com/item/%E6%9C%80%E8%BF%91%E5%85%AC%E5%85%B1%E7%A5%96%E5%85%88/8918834?fr=aladdin)中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

示例 1：
![](https://assets.leetcode.com/uploads/2018/12/14/binarytree.png)

```

输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出：3
解释：节点 5 和节点 1 的最近公共祖先是节点 3 。

```

示例 2：
![](https://assets.leetcode.com/uploads/2018/12/14/binarytree.png)

```

输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出：5
解释：节点 5 和节点 4 的最近公共祖先是节点 5 。因为根据定义最近公共祖先节点可以为节点本身。

```

示例 3：

```

输入：root = [1,2], p = 1, q = 2
输出：1

```

提示：

* 树中节点数目在范围 `[2, 105]` 内。
* `-109 <= Node.val <= 109`
* 所有 `Node.val` `互不相同` 。
* `p != q`
* `p` 和 `q` 均存在于给定的二叉树中。

```cpp
class Solution {
 public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (!root) return nullptr;
    if (root == p) return p;
    if (root == q) return q;

    TreeNode *lca_l = nullptr, *lca_r = nullptr;
    if (root->left) lca_l = lowestCommonAncestor(root->left, p, q);
    if (root->right) lca_r = lowestCommonAncestor(root->right, p, q);

    if (lca_l == nullptr) return lca_r;
    if (lca_r == nullptr) return lca_l;
    if (lca_r == nullptr && lca_l == nullptr) return nullptr;
    return root;
  }
};
```

-------------

## 最大子数组和

给你一个整数数组 `nums` ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
子数组 是数组中的一个连续部分。

示例 1：

```

输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。

```

示例 2：

```

输入：nums = [1]
输出：1

```

示例 3：

```

输入：nums = [5,4,-1,7,8]
输出：23

```

提示：

* `1 <= nums.length <= 105`
* `-104 <= nums[i] <= 104`

进阶：如果你已经实现复杂度为 `O(n)` 的解法，尝试使用更为精妙的 分治法 求解。

```cpp
class Solution {
 public:
  int maxSubArray(vector<int>& nums) {
    vector<int> dp(nums.size());
    dp[0] = nums[0];
    for (int i = 1; i < nums.size(); i++) {
      dp[i] = max(dp[i - 1] + nums[i], nums[i]);
    }
    return *max_element(dp.begin(), dp.end());
  }
};

class Solution_Recur {
 public:
  struct Status {
    int lSum, rSum, mSum, iSum;
  };

  Status pushUp(Status l, Status r) {
    int iSum = l.iSum + r.iSum;
    int lSum = max(l.lSum, l.iSum + r.lSum);
    int rSum = max(r.rSum, r.iSum + l.rSum);
    int mSum = max(max(l.mSum, r.mSum), l.rSum + r.lSum);
    return (Status){lSum, rSum, mSum, iSum};
  };

  Status get(vector<int>& a, int l, int r) {
    if (l == r) {
      return (Status){a[l], a[l], a[l], a[l]};
    }
    int m = (l + r) >> 1;
    Status lSub = get(a, l, m);
    Status rSub = get(a, m + 1, r);
    return pushUp(lSub, rSub);
  }

  int maxSubArray(vector<int>& nums) {
    return get(nums, 0, nums.size() - 1).mSum;
  }
};
```

-------------

## 打家劫舍

你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。

示例 1：

```

输入：[1,2,3,1]
输出：4
解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
     偷窃到的最高金额 = 1 + 3 = 4 。
```

示例 2：

```

输入：[2,7,9,3,1]
输出：12
解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
     偷窃到的最高金额 = 2 + 9 + 1 = 12 。

```

提示：

* `1 <= nums.length <= 100`
* `0 <= nums[i] <= 400`

```cpp
class Solution {
 public:
  int rob(vector<int>& nums) {
    vector<int> dp(nums.size() + 1);
    dp[0] = 0;
    for (int i = 1; i <= nums.size(); i++) {
      if (i - 2 > 0)
        dp[i] = max(dp[i - 1], dp[i - 2] + nums[i - 1]);
      else
        dp[i] = max(dp[i - 1], dp[0] + nums[i - 1]);
    }
    // fmt::print("{}\n", dp);
    return dp.back();
  }
};
```

-------------

## 重复的DNA序列

DNA序列 由一系列核苷酸组成，缩写为 `'A'`, `'C'`, `'G'` 和 `'T'`.。

* 例如，`"ACGAATTCCG"` 是一个 DNA序列 。

在研究 DNA 时，识别 DNA 中的重复序列非常有用。
给定一个表示 DNA序列 的字符串 `s` ，返回所有在 DNA 分子中出现不止一次的 长度为 `10` 的序列(子字符串)。你可以按 任意顺序 返回答案。

示例 1：

```

输入：s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
输出：["AAAAACCCCC","CCCCCAAAAA"]

```

示例 2：

```

输入：s = "AAAAAAAAAAAAA"
输出：["AAAAAAAAAA"]

```

提示：

* `0 <= s.length <= 105`
* `s[i]``==``'A'`、`'C'`、`'G'` or `'T'`

```cpp
class Solution {
 public:
  int StoN(char c) {
    int res = -1;
    switch (c) {
      case 'A':
        res = 0;
        break;
      case 'G':
        res = 1;
        break;
      case 'C':
        res = 2;
        break;
      case 'T':
        res = 3;
        break;

      default:
        cout << "error" << endl;
    }
    return res;
  }

  int addChar(vector<int> &arr, int windowHash, int right, int R) {
    return R * windowHash + arr[right];
  }

  int removeChar(vector<int> &arr, int windowHash, int left, int R, int len) {
    return windowHash - arr[left] * (int)pow(R, len - 1);
  }

  vector<string> findRepeatedDnaSequences(string &s) {
    vector<int> arr;
    vector<string> res;
    unordered_map<string, int> res_hash;
    string temp{};
    for (char c : s) arr.push_back(StoN(c));
    // fmt::print("{}\n", arr);
    unordered_map<int, int> seen{}, window{};
    int left = 0, right = 0, windowHash = 0, R = 4, L = 10;
    while (right < s.size()) {
      // window.add();
      windowHash = addChar(arr, windowHash, right, R);
      right++;

      // fmt::print("({}, {})\n", left, right);
      while (right - left == L) {
        // window.remove
        if (seen.count(windowHash)) {
          // fmt::print("already seen {}\n", windowHash);
          temp = s.substr(left, L);
          if (!res_hash.count(temp)) {
            res_hash[temp] = 1;
            res.push_back(temp);
          }
        } else {
          seen[windowHash] = 1;
        }
        windowHash = removeChar(arr, windowHash, left, R, L);
        left++;
      }
    }
    // fmt::print("{}\n", res);
    return res;
  }
};
```

-------------

## 跳跃游戏 II

给定一个长度为 `n` 的 0 索引整数数组 `nums`。初始位置为 `nums[0]`。
每个元素 `nums[i]` 表示从索引 `i` 向前跳转的最大长度。换句话说，如果你在 `nums[i]` 处，你可以跳转到任意 `nums[i + j]` 处:

* `0 <= j <= nums[i]`
* `i + j < n`

返回到达 `nums[n - 1]` 的最小跳跃次数。生成的测试用例可以到达 `nums[n - 1]`。

示例 1:

```

输入: nums = [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。

```

示例 2:

```

输入: nums = [2,3,0,1,4]
输出: 2

```

提示:

* `1 <= nums.length <= 104`
* `0 <= nums[i] <= 1000`
* 题目保证可以到达 `nums[n-1]`

```cpp
class Solution {
 public:
  int jump(vector<int>& nums) {
    int n = nums.size();
    int cnt = 0;
    int i = 0;
    int idx = 0;
    while (i < n - 1) {
      if (nums[i] < 1) return -1;
      if (i + nums[i] >= n - 1) return cnt + 1;
      int maxPos = nums[i + 1];
      idx = i + 1;
      for (int j = 1; j <= nums[i]; j++) {
        if (maxPos <= nums[i + j] + j) {
          idx = i + j;
          // takeways: I need to find the maximum step
          // I can make from the current position
          maxPos = nums[i + j] + j;
        }
      }
      cnt++;
      i = idx;
    }
    return cnt;
  }
};
```

-------------

## 二分查找

给定一个 `n` 个元素有序的（升序）整型数组 `nums` 和一个目标值 `target`  ，写一个函数搜索 `nums` 中的 `target`，如果目标值存在返回下标，否则返回 `-1`。
  
示例 1:

```
输入: nums = [-1,0,3,5,9,12], target = 9
输出: 4
解释: 9 出现在 nums 中并且下标为 4

```

示例 2:

```
输入: nums = [-1,0,3,5,9,12], target = 2
输出: -1
解释: 2 不存在 nums 中因此返回 -1

```

提示：

1. 你可以假设 `nums` 中的所有元素是不重复的。
2. `n` 将在 `[1, 10000]`之间。
3. `nums` 的每个元素都将在 `[-9999, 9999]`之间。

```cpp
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
    return nums.at(left) == target ? left : -1;
  }
};
```

-------------

## 字符串的排列

给你两个字符串 `s1` 和 `s2` ，写一个函数来判断 `s2` 是否包含 `s1`的排列。如果是，返回 `true` ；否则，返回 `false` 。
换句话说，`s1` 的排列之一是 `s2` 的 子串 。

示例 1：

```

输入：s1 = "ab" s2 = "eidbaooo"
输出：true
解释：s2 包含 s1 的排列之一 ("ba").

```

示例 2：

```

输入：s1= "ab" s2 = "eidboaoo"
输出：false

```

提示：

* `1 <= s1.length, s2.length <= 104`
* `s1` 和 `s2` 仅包含小写字母

```cpp
class Solution {
 public:
  bool checkInclusion(string s1, string s2) {
    if (!s2.size()) return false;
    if (!s1.size()) return false;
    if (s1.size() > s2.size()) return false;
    unordered_map<char, int> need{}, window{};
    for (char i : s1) need[i]++;
    int left = 0, right = 0;
    char c = 0, d = 0;
    bool res = false;
    int valid = 0;
    while (right < s2.size()) {
      c = s2[right];
      right++;

      if (need.count(c)) {
        window[c]++;
        if (need[c] == window[c]) valid++;
      }

      // fmt::print("({}, {})", left, right);

      while (right - left >= s1.size()) {
        if (valid == need.size()) return true;
        d = s2[left];
        left++;
        if (need.count(d)) {
          window[d]--;
          if (need[d] == window[d]) valid--;
        }
      }
    }

    return false;
  }
};
```

-------------

## K 个一组翻转链表

给你链表的头节点 `head` ，每 `k`个节点一组进行翻转，请你返回修改后的链表。
`k` 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 `k`的整数倍，那么请将最后剩余的节点保持原有顺序。
你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

示例 1：
![](https://assets.leetcode.com/uploads/2020/10/03/reverse_ex1.jpg)

```

输入：head = [1,2,3,4,5], k = 2
输出：[2,1,4,3,5]

```

示例 2：
![](https://assets.leetcode.com/uploads/2020/10/03/reverse_ex2.jpg)

```

输入：head = [1,2,3,4,5], k = 3
输出：[3,2,1,4,5]

```

提示：

* 链表中的节点数目为 `n`
* `1 <= k <= n <= 5000`
* `0 <= Node.val <= 1000`

进阶：你可以设计一个只用 `O(1)` 额外内存空间的算法解决此问题吗？

```cpp
class Solution {
 public:
  ListNode* reverse(ListNode* head, ListNode* target) {
    ListNode *pre = nullptr, *cur = head, *nxt = head;
    while (cur != target) {
      nxt = cur->next;
      cur->next = pre;
      pre = cur;
      cur = nxt;
    }
    return pre;
  }
  ListNode* reverseKGroup(ListNode* head, int k) {
    if (!head) return head;
    ListNode* cur = nullptr;
    int i = 0;
    for (cur = head; cur != nullptr && i < k; cur = cur->next, i++)
      ;
    if (i < k) return head;
    ListNode* tail = reverseKGroup(cur, k);
    ListNode* new_head = reverse(head, cur);
    head->next = tail;
    return new_head;
  }
};
```

-------------

## 二叉树的序列化与反序列化

序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。
请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。
提示: 输入输出格式与 LeetCode 目前使用的方式一致，详情请参阅 [LeetCode 序列化二叉树的格式](/faq/#binary-tree)。你并非必须采取这种方式，你也可以采用其他的方法解决这个问题。

示例 1：
![](https://assets.leetcode.com/uploads/2020/09/15/serdeser.jpg)

```

输入：root = [1,2,3,null,null,4,5]
输出：[1,2,3,null,null,4,5]

```

示例 2：

```

输入：root = []
输出：[]

```

示例 3：

```

输入：root = [1]
输出：[1]

```

示例 4：

```

输入：root = [1,2]
输出：[1,2]

```

提示：

* 树中结点数在范围 `[0, 104]` 内
* `-1000 <= Node.val <= 1000`

```cpp
vector<string> split(string str, string delimiter = " ") {
  vector<string> tokens;
  size_t start = 0, end = 0;
  while ((end = str.find(delimiter, start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + delimiter.length();
  }
  return tokens;
}

class Codec {
 public:
  // Encodes a tree to a single string.
  string serialize(TreeNode *root) {
    queue<TreeNode *> q;

    q.push(root);
    TreeNode *cur = nullptr;
    string serialize_str = "";

    while (!q.empty()) {
      int sz = q.size();
      for (int i = 0; i < sz; i++) {
        cur = q.front();
        q.pop();
        if (cur == nullptr) {
          serialize_str += "null, ";
          continue;
        }
        serialize_str += to_string(cur->val);
        serialize_str += ", ";
        q.push(cur->left);
        q.push(cur->right);
      }
    }
    return serialize_str;
  }

  // Decodes your encoded data to tree.
  TreeNode *deserialize(string data) {
    if (data == "") return nullptr;
    vector<string> tokens = split(data, string(", "));
    queue<TreeNode *> q;
    int idx = 0;
    if (tokens[idx] == "null") return nullptr;
    TreeNode *root = new TreeNode(stoi(tokens[idx]));
    q.push(root);
    TreeNode *cur = nullptr;

    while (!q.empty() && idx < tokens.size()) {
      cur = q.front();
      q.pop();

      if (cur == nullptr) {
        continue;
      }

      idx++;
      if (tokens[idx] == "null")
        cur->left = nullptr;
      else
        cur->left = new TreeNode(stoi(tokens[idx]));
      q.push(cur->left);
      idx++;
      if (tokens[idx] == "null")
        cur->right = nullptr;
      else
        cur->right = new TreeNode(stoi(tokens[idx]));
      q.push(cur->right);
    }
    return root;
  }
};
```

-------------

## 鸡蛋掉落

给你 `k` 枚相同的鸡蛋，并可以使用一栋从第 `1` 层到第 `n` 层共有 `n` 层楼的建筑。
已知存在楼层 `f` ，满足 `0 <= f <= n` ，任何从 高于 `f` 的楼层落下的鸡蛋都会碎，从 `f` 楼层或比它低的楼层落下的鸡蛋都不会破。
每次操作，你可以取一枚没有碎的鸡蛋并把它从任一楼层 `x` 扔下（满足 `1 <= x <= n`）。如果鸡蛋碎了，你就不能再次使用它。如果某枚鸡蛋扔下后没有摔碎，则可以在之后的操作中 重复使用 这枚鸡蛋。
请你计算并返回要确定 `f` 确切的值 的 最小操作次数 是多少？

示例 1：

```

输入：k = 1, n = 2
输出：2
解释：
鸡蛋从 1 楼掉落。如果它碎了，肯定能得出 f = 0 。 
否则，鸡蛋从 2 楼掉落。如果它碎了，肯定能得出 f = 1 。 
如果它没碎，那么肯定能得出 f = 2 。 
因此，在最坏的情况下我们需要移动 2 次以确定 f 是多少。 

```

示例 2：

```

输入：k = 2, n = 6
输出：3

```

示例 3：

```

输入：k = 3, n = 14
输出：4

```

提示：

* `1 <= k <= 100`
* `1 <= n <= 104`

```cpp
class Solution {
 public:
  int superEggDrop(int K, int N) {
    // define a problem that you have k eggs,
    // and drop m times, at most the level you can achieve.
    vector<vector<double>> dp(K + 1, vector<double>(N + 1));
    for (int m = 1; m <= N && dp[K][m] < N; m++) {
      for (int k = 1; k <= K; k++) {
        dp[k][m] = dp[k][m - 1] + dp[k - 1][m - 1] + 1;
      }
    }
    // fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    for (int i = 0; i <= N; i++) {
      if (dp[K][i] >= N) {
        return i;
      }
    }
    return 0;
  }
};
```

-------------

## 在排序数组中查找元素的第一个和最后一个位置

给你一个按照非递减顺序排列的整数数组 `nums`，和一个目标值 `target`。请你找出给定目标值在数组中的开始位置和结束位置。
如果数组中不存在目标值 `target`，返回 `[-1, -1]`。
你必须设计并实现时间复杂度为 `O(log n)` 的算法解决此问题。

示例 1：

```

输入：nums = [5,7,7,8,8,10], target = 8
输出：[3,4]
```

示例 2：

```

输入：nums = [5,7,7,8,8,10], target = 6
输出：[-1,-1]
```

示例 3：

```

输入：nums = [], target = 0
输出：[-1,-1]
```

提示：

* `0 <= nums.length <= 105`
* `-109 <= nums[i] <= 109`
* `nums` 是一个非递减数组
* `-109 <= target <= 109`

```cpp
class Solution {
 public:
  int searchLowerbound(vector<int>& nums, int target) {
    if (!nums.size()) return -1;
    int left = 0, right = nums.size() - 1;
    int mid = 0;
    while (left <= right) {
      mid = left + (right - left) / 2;
      if (nums[mid] == target) {
        right = mid - 1;
      } else if (nums[mid] > target) {
        right = mid - 1;
      } else if (nums[mid] < target) {
        left = mid + 1;
      }
    }
    if (left >= nums.size()) return -1;
    return target == nums[left] ? left : -1;
  }
  int searchUpperbound(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    int mid = 0;
    while (left <= right) {
      mid = left + (right - left) / 2;
      if (nums[mid] == target) {
        left = mid + 1;
      } else if (nums[mid] > target) {
        right = mid - 1;
      } else if (nums[mid] < target) {
        left = mid + 1;
      }
    }
    if (right < 0) return -1;
    return target == nums[right] ? right : -1;
  }
  vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> res;
    int lower = searchLowerbound(nums, target);
    int upper = searchUpperbound(nums, target);
    res.push_back(lower);
    res.push_back(upper);
    return res;
  }
};
```

-------------

## x 的平方根

给你一个非负整数 `x` ，计算并返回 `x` 的 算术平方根 。
由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。
注意：不允许使用任何内置指数函数和算符，例如 `pow(x, 0.5)` 或者 `x ** 0.5` 。

示例 1：

```

输入：x = 4
输出：2

```

示例 2：

```

输入：x = 8
输出：2
解释：8 的算术平方根是 2.82842..., 由于返回类型是整数，小数部分将被舍去。

```

提示：

* `0 <= x <= 231 - 1`

```cpp
class Solution {
 public:
  int mySqrt_simple(int x) {
    if (x == 0) {
      return 0;
    }
    int ans = exp(0.5 * log(x));
    return ((long long)(ans + 1) * (ans + 1) <= x ? ans + 1 : ans);
  }

  int mySqrt_binsearch(int x) {
    long long left = 0, right = x, mid = 0;
    while (left <= right) {
      mid = left + (right - left) / 2;
      if (mid * mid > x) {
        right = mid - 1;
      } else if (mid * mid < x) {
        left = mid + 1;
      } else {
        return mid;
      }
    }

    return (left + right) / 2;
  }

  int mySqrt_newton(int x) {
    if (!x) return 0;
    double C = x;
    double x0 = x;
    double xi = 0;
    while (1) {
      xi = 0.5 * (x0 + C / x0);
      if (fabs(xi - x0) < 1e-7) break;
      x0 = xi;
    }
    return (int)xi;
  }

  int mySqrt_newton_back(int x) {
    long long r = x;
    while (r * r > x) r = (r + x / r) / 2;
    return r;
  }

  int mySqrt(int x) { return mySqrt_newton_back(x); }
};
```

-------------

## 俄罗斯套娃信封问题

给你一个二维整数数组 `envelopes` ，其中 `envelopes[i] = [wi, hi]` ，表示第 `i` 个信封的宽度和高度。
当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。
请计算 最多能有多少个 信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。
注意：不允许旋转信封。

示例 1：

```

输入：envelopes = [[5,4],[6,4],[6,7],[2,3]]
输出：3
解释：最多信封的个数为 3, 组合为: [2,3] => [5,4] => [6,7]。
```

示例 2：

```

输入：envelopes = [[1,1],[1,1],[1,1]]
输出：1

```

提示：

* `1 <= envelopes.length <= 105`
* `envelopes[i].length == 2`
* `1 <= wi, hi <= 105`

```cpp
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
      // fmt::print("{}\n", top);
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
```

-------------

## 回文链表

给你一个单链表的头节点 `head` ，请你判断该链表是否为回文链表。如果是，返回 `true` ；否则，返回 `false` 。

示例 1：
![](https://assets.leetcode.com/uploads/2021/03/03/pal1linked-list.jpg)

```

输入：head = [1,2,2,1]
输出：true

```

示例 2：
![](https://assets.leetcode.com/uploads/2021/03/03/pal2linked-list.jpg)

```

输入：head = [1,2]
输出：false

```

提示：

* 链表中节点数目在范围`[1, 105]` 内
* `0 <= Node.val <= 9`

进阶：你能否用 `O(n)` 时间复杂度和 `O(1)` 空间复杂度解决此题？

```cpp
class Solution {
 public:
  ListNode *comp = nullptr;
  int f = 0, b = 0;
  ListNode *reversed(ListNode *head, int b) {
    if (!head->next) return head;
    b++;
    ListNode *tail = reversed(head->next, b);
    if (!tail) return nullptr;
    if (f > b) return tail;
    if (comp->val != tail->val) return nullptr;
    comp = comp->next;
    f++;
    return head;
  }

  bool isPalindrome(ListNode *head) {
    comp = head;
    ListNode *p = reversed(head, 0);
    if (!p) return false;
    return true;
  }
};
```

-------------

## 超级次方

你的任务是计算 `ab` 对 `1337` 取模，`a` 是一个正整数，`b` 是一个非常大的正整数且会以数组形式给出。

示例 1：

```

输入：a = 2, b = [3]
输出：8

```

示例 2：

```

输入：a = 2, b = [1,0]
输出：1024

```

示例 3：

```

输入：a = 1, b = [4,3,3,8,5,2]
输出：1

```

示例 4：

```

输入：a = 2147483647, b = [2,0,0]
输出：1198

```

提示：

* `1 <= a <= 231 - 1`
* `1 <= b.length <= 2000`
* `0 <= b[i] <= 9`
* `b` 不含前导 0

```cpp
class Solution {
 public:
  const int base = 1337;
  int mypow(int a, int k) {
    // 对因子求模
    a %= base;
    int res = 1;
    for (int _ = 0; _ < k; _++) {
      // 这里有乘法，是潜在的溢出点
      res *= a;
      // 对乘法结果求模
      res %= base;
    }
    return res;
  }

  int superPow(int a, vector<int>& b) {
    if (b.empty()) return 1;
    if (a == 0) return 0;

    int last = b.back();
    b.pop_back();

    int m1 = mypow(superPow(a, b), 10);
    int m2 = mypow(a, last);

    return (m1 * m2) % base;
  }
};
```

-------------

## 错误的集合

集合 `s` 包含从 `1` 到 `n` 的整数。不幸的是，因为数据错误，导致集合里面某一个数字复制了成了集合里面的另外一个数字的值，导致集合 丢失了一个数字 并且 有一个数字重复 。
给定一个数组 `nums` 代表了集合 `S` 发生错误后的结果。
请你找出重复出现的整数，再找到丢失的整数，将它们以数组的形式返回。

示例 1：

```

输入：nums = [1,2,2,4]
输出：[2,3]

```

示例 2：

```

输入：nums = [1,1]
输出：[1,2]

```

提示：

* `2 <= nums.length <= 104`
* `1 <= nums[i] <= 104`

```cpp
class Solution {
 public:
  vector<int> findErrorNums(vector<int>& nums) {
    // 1 2 4 2
    // 0 1 2 3
    // in normal, the nums is respond to index
    // if the index is duplicate, the value is negative
    // if the index is missing, the value is positive
    // for example:
    // for `4`, it will change the sign of `nums[3]` to negative
    // when it comes to `2` again, it will find the duplicate element,
    // and will change the sign of `nums[1]` to negative, but `nums[1]` is
    // already negative. So we find the duplicate element is 1(idx) + 1.
    // Similarly, if there is missing element, we find it by checking the
    // positive element in nums.
    int n = nums.size();
    int dup = -1, idx = 0;
    for (int i = 0; i < n; i++) {
      idx = (int)abs(nums.at(i)) - 1;
      if (nums.at(idx) < 0) {
        dup = idx;
      } else {
        nums.at(idx) *= -1;
      }
    }
    int missing = -1;
    for (int i = 0; i < n; i++) {
      if (nums.at(i) > 0) {
        missing = i + 1;
      }
    }
    // fmt::print("{}, dup: {}, missing: {}\n", nums, dup, missing);
    return vector<int>{dup + 1, missing};
    // return vector<int>();
  }
};
```

-------------

## 最长回文子序列

给你一个字符串 `s` ，找出其中最长的回文子序列，并返回该序列的长度。
子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。

示例 1：

```

输入：s = "bbbab"
输出：4
解释：一个可能的最长回文子序列为 "bbbb" 。

```

示例 2：

```

输入：s = "cbbd"
输出：2
解释：一个可能的最长回文子序列为 "bb" 。

```

提示：

* `1 <= s.length <= 1000`
* `s` 仅由小写英文字母组成

```cpp
class Solution {
 public:
  int longestPalindromeSubseq(string s) {
    if (!s.size()) return 0;
    vector<vector<int>> dp(s.size(), vector<int>(s.size()));
    for (int i = 0; i < s.size(); i++) {
      dp[i][i] = 1;
    }

    for (int start = s.size() - 1; start >= 0; start--) {
      for (int end = start + 1; end < s.size(); end++) {
        if (s[start] == s[end])
          dp[start][end] = dp[start + 1][end - 1] + 2;
        else
          dp[start][end] = max(dp[start + 1][end], dp[start][end - 1]);
      }
    }
    print2D(dp);
    // fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    return dp.front().back();
  }
};
```

-------------

## 打家劫舍 III

小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为 `root` 。
除了 `root` 之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 如果 两个直接相连的房子在同一天晚上被打劫 ，房屋将自动报警。
给定二叉树的 `root` 。返回 在不触动警报的情况下 ，小偷能够盗取的最高金额 。

示例 1:
![](https://assets.leetcode.com/uploads/2021/03/10/rob1-tree.jpg)

```

输入: root = [3,2,3,null,3,null,1]
输出: 7 
解释: 小偷一晚能够盗取的最高金额 3 + 3 + 1 = 7
```

示例 2:
![](https://assets.leetcode.com/uploads/2021/03/10/rob2-tree.jpg)

```

输入: root = [3,4,5,1,3,null,1]
输出: 9
解释: 小偷一晚能够盗取的最高金额 4 + 5 = 9

```

提示：

* 树的节点数在 `[1, 104]` 范围内
* `0 <= Node.val <= 104`

```cpp
class Solution {
 public:
  unordered_map<TreeNode*, int> mem{};
  int backtrack(TreeNode* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return root->val;
    if (mem.count(root)) return mem[root];

    // if not choose root
    int max_val = 0;
    max_val = max(max_val, backtrack(root->left) + backtrack(root->right));

    // if choose root;
    int sums = 0;
    if (root->left) {
      sums += backtrack(root->left->left) + backtrack(root->left->right);
    }
    if (root->right) {
      sums += backtrack(root->right->left) + backtrack(root->right->right);
    }
    sums += root->val;

    // find max value
    max_val = max(max_val, sums);
    mem[root] = max_val;
    return max_val;
  }
  int rob(TreeNode* root) { return backtrack(root); }
};
```

-------------

## 二叉搜索树中第K小的元素

给定一个二叉搜索树的根节点 `root` ，和一个整数 `k` ，请你设计一个算法查找其中第 `k`个最小元素（从 1 开始计数）。

示例 1：
![](https://assets.leetcode.com/uploads/2021/01/28/kthtree1.jpg)

```

输入：root = [3,1,4,null,2], k = 1
输出：1

```

示例 2：
![](https://assets.leetcode.com/uploads/2021/01/28/kthtree2.jpg)

```

输入：root = [5,3,6,2,4,null,null,1], k = 3
输出：3

```

提示：

* 树中的节点数为 `n` 。
* `1 <= k <= n <= 104`
* `0 <= Node.val <= 104`

进阶：如果二叉搜索树经常被修改（插入/删除操作）并且你需要频繁地查找第 `k` 小的值，你将如何优化算法？

```cpp
class Solution {
 public:
  int find(TreeNode *root, int &k) {
    if (!root) return 0;
    int top_k_from_left = find(root->left, k);
    // This is mean that we are already full use of k.
    // so the top k will be the left branch.
    if (k == 0) return top_k_from_left;
    k -= 1;
    // if k == 1 this means that the root is the answer.
    if (k == 0) return root->val;
    // we can continue to search in the right branch.
    // the k is not initalized value.
    return find(root->right, k);
  }

  int kthSmallest(TreeNode *root, int k) { return find(root, k); }
};
```

-------------

## 统计全为 1 的正方形子矩阵

给你一个 `m * n` 的矩阵，矩阵中的元素不是 `0` 就是 `1`，请你统计并返回其中完全由 `1` 组成的 正方形 子矩阵的个数。

示例 1：

```
输入：matrix =
[
  [0,1,1,1],
  [1,1,1,1],
  [0,1,1,1]
]
输出：15
解释： 
边长为 1 的正方形有 10 个。
边长为 2 的正方形有 4 个。
边长为 3 的正方形有 1 个。
正方形的总数 = 10 + 4 + 1 = 15.

```

示例 2：

```
输入：matrix = 
[
  [1,0,1],
  [1,1,0],
  [1,1,0]
]
输出：7
解释：
边长为 1 的正方形有 6 个。 
边长为 2 的正方形有 1 个。
正方形的总数 = 6 + 1 = 7.

```

提示：

* `1 <= arr.length <= 300`
* `1 <= arr[0].length <= 300`
* `0 <= arr[i][j] <= 1`

```cpp
class Solution {
 public:
  int countSquares(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix.at(0).size();
    vector<vector<int>> dp(n, vector<int>(m));
    int square_cnt = 0;

    // count the first element once.
    dp.at(0).at(0) = matrix.at(0).at(0);
    square_cnt += dp.at(0).at(0);

    for (int i = 1; i < m; i++) {
      dp.at(0).at(i) = matrix.at(0).at(i);
      square_cnt += dp.at(0).at(i);
    }
    for (int i = 1; i < n; i++) {
      dp.at(i).at(0) = matrix.at(i).at(0);
      square_cnt += dp.at(i).at(0);
    }

    for (int col = 1; col < n; col++) {
      for (int row = 1; row < m; row++) {
        if (matrix.at(col).at(row)) {
          dp.at(col).at(row) =
              min(min(dp.at(col - 1).at(row - 1), dp.at(col).at(row - 1)),
                  dp.at(col - 1).at(row)) +
              1;
        } else {
          dp.at(col).at(row) = 0;
        }
        square_cnt += dp.at(col).at(row);
      }
    }

    // fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    return square_cnt;
  }
};
```

-------------

## 删除链表的倒数第 N 个结点

给你一个链表，删除链表的倒数第 `n`个结点，并且返回链表的头结点。

示例 1：
![](https://assets.leetcode.com/uploads/2020/10/03/remove_ex1.jpg)

```

输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]

```

示例 2：

```

输入：head = [1], n = 1
输出：[]

```

示例 3：

```

输入：head = [1,2], n = 1
输出：[1]

```

提示：

* 链表中结点的数目为 `sz`
* `1 <= sz <= 30`
* `0 <= Node.val <= 100`
* `1 <= n <= sz`

进阶：你能尝试使用一趟扫描实现吗？

```cpp
class Solution {
 public:
  ListNode* removeNthFromEnd(ListNode* head, int k) {
    if (!head) return nullptr;
    if (!k) return nullptr;
    ListNode *slow = head, *fast = head;
    int count = 0;
    while (fast != nullptr && count < k) {
      fast = fast->next;
      count++;
    }
    if (!fast) {
      if (count == k) {
        ListNode* del = head;
        head = head->next;
        delete del;
        return head;
      }
      return head;
    };

    for (; fast->next != nullptr; slow = slow->next, fast = fast->next)
      ;
    ListNode* del = slow->next;
    slow->next = slow->next->next;
    delete del;
    return head;
  }
};
```

-------------

## 拼车

车上最初有 `capacity` 个空座位。车 只能向一个方向行驶（也就是说，不允许掉头或改变方向）
给定整数 `capacity` 和一个数组 `trips` ,  `trip[i] = [numPassengersi, fromi, toi]` 表示第 `i` 次旅行有 `numPassengersi` 乘客，接他们和放他们的位置分别是 `fromi` 和 `toi` 。这些位置是从汽车的初始位置向东的公里数。
当且仅当你可以在所有给定的行程中接送所有乘客时，返回 `true`，否则请返回 `false`。

示例 1：

```

输入：trips = [[2,1,5],[3,3,7]], capacity = 4
输出：false

```

示例 2：

```

输入：trips = [[2,1,5],[3,3,7]], capacity = 5
输出：true

```

提示：

* `1 <= trips.length <= 1000`
* `trips[i].length == 3`
* `1 <= numPassengersi <= 100`
* `0 <= fromi < toi <= 1000`
* `1 <= capacity <= 105`

```cpp
class Solution {
 public:
  bool carPooling(vector<vector<int>>& trips, int capacity) {
    int nums_pass = 0, from_ = 0, to_ = 0;
    vector<int> diff(1001);
    for (vector<int>& tr : trips) {
      nums_pass = tr[0];
      from_ = tr[1];
      to_ = tr[2];
      diff[from_] += nums_pass;
      diff[to_] += -nums_pass;
    }
    // fmt::print("{}\n", diff);
    int total_sum = 0;
    for (int& x : diff) {
      total_sum += x;
      if (total_sum > capacity) return false;
    }
    return true;
  }
};
```

-------------

## 盛最多水的容器

给定一个长度为 `n` 的整数数组 `height` 。有 `n` 条垂线，第 `i` 条线的两个端点是 `(i, 0)` 和 `(i, height[i])` 。
找出其中的两条线，使得它们与 `x` 轴共同构成的容器可以容纳最多的水。
返回容器可以储存的最大水量。
说明：你不能倾斜容器。

示例 1：
![](https://aliyun-lc-upload.oss-cn-hangzhou.aliyuncs.com/aliyun-lc-upload/uploads/2018/07/25/question_11.jpg)

```

输入：[1,8,6,2,5,4,8,3,7]
输出：49 
解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
```

示例 2：

```

输入：height = [1,1]
输出：1

```

提示：

* `n == height.length`
* `2 <= n <= 105`
* `0 <= height[i] <= 104`

```cpp
class Solution {
 public:
  int maxArea(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int area_max = 0;
    while (left < right) {
      area_max =
          max(area_max, min(height[left], height[right]) * (right - left));
      if (height[left] > height[right])
        right--;
      else
        left++;
    }
    return area_max;
  }
};
```

-------------

## 阶乘函数后 K 个零

 `f(x)` 是 `x!` 末尾是 0 的数量。回想一下 `x! = 1 * 2 * 3 * ... * x`，且 `0! = 1` 。

* 例如， `f(3) = 0` ，因为 `3! = 6` 的末尾没有 0 ；而 `f(11) = 2` ，因为 `11!= 39916800` 末端有 2 个 0 。

给定 `k`，找出返回能满足 `f(x) = k` 的非负整数 `x` 的数量。

示例 1：

```

输入：k = 0输出：5解释：0!, 1!, 2!, 3!, 和 4! 均符合 k = 0 的条件。

```

示例 2：

```

输入：k = 5
输出：0
解释：没有匹配到这样的 x!，符合 k = 5 的条件。
```

示例 3:

```

输入: k = 3
输出: 5

```

提示:

* `0 <= k <= 109`

```cpp
class Solution {
 public:
  long trailingZeroes(long n) {
    long res = 0;
    for (long d = n; d / 5 > 0; d = d / 5) {
      res += d / 5;
    }
    return res;
  }

  long left_bound(int target) {
    long lo = 0, hi = LONG_MAX - 1, mid = 0;
    while (lo <= hi) {
      mid = lo + (hi - lo) / 2;
      if (trailingZeroes(mid) == target) {
        hi = mid - 1;
      } else if (trailingZeroes(mid) < target) {
        lo = mid + 1;
      } else if (trailingZeroes(mid) > target) {
        hi = mid - 1;
      }
    }
    return lo;
  }

  long right_bound(int target) {
    long lo = 0, hi = LONG_MAX - 1, mid = 0;
    while (lo <= hi) {
      mid = lo + (hi - lo) / 2;
      if (trailingZeroes(mid) == target) {
        lo = mid + 1;
      } else if (trailingZeroes(mid) < target) {
        lo = mid + 1;
      } else if (trailingZeroes(mid) > target) {
        hi = mid - 1;
      }
    }
    return hi;
  }

  int preimageSizeFZF(int K) {
    // fmt::print("{}\n", right_bound(K));
    // fmt::print("{}\n", left_bound(K));
    return (int)(right_bound(K) - left_bound(K) + 1);
  }
};
```

-------------

## 完全二叉树的节点个数

给你一棵 完全二叉树 的根节点 `root` ，求出该树的节点个数。
[完全二叉树](https://baike.baidu.com/item/%E5%AE%8C%E5%85%A8%E4%BA%8C%E5%8F%89%E6%A0%91/7773232?fr=aladdin) 的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 `h` 层，则该层包含 `1~ 2h` 个节点。

示例 1：
![](https://assets.leetcode.com/uploads/2021/01/14/complete.jpg)

```

输入：root = [1,2,3,4,5,6]
输出：6

```

示例 2：

```

输入：root = []
输出：0

```

示例 3：

```

输入：root = [1]
输出：1

```

提示：

* 树中节点的数目范围是`[0, 5 * 104]`
* `0 <= Node.val <= 5 * 104`
* 题目数据保证输入的树是 完全二叉树

进阶：遍历树来统计节点是一种时间复杂度为 `O(n)` 的简单解决方案。你可以设计一个更快的算法吗？

```cpp
class Solution {
 public:
  int trailingZeroes(int n) {
    int res = 0;
    for (int d = n; d / 5 > 0; d = d / 5) {
      res += d / 5;
    }
    return res;
  }
};
```

-------------

## 目标和

给你一个非负整数数组 `nums` 和一个整数 `target` 。
向数组中的每个整数前添加 `'+'` 或 `'-'` ，然后串联起所有整数，可以构造一个 表达式 ：

* 例如，`nums = [2, 1]` ，可以在 `2` 之前添加 `'+'` ，在 `1` 之前添加 `'-'` ，然后串联起来得到表达式 `"+2-1"` 。

返回可以通过上述方法构造的、运算结果等于 `target` 的不同 表达式 的数目。

示例 1：

```

输入：nums = [1,1,1,1,1], target = 3
输出：5
解释：一共有 5 种方法让最终目标和为 3 。
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3

```

示例 2：

```

输入：nums = [1], target = 1
输出：1

```

提示：

* `1 <= nums.length <= 20`
* `0 <= nums[i] <= 1000`
* `0 <= sum(nums[i]) <= 1000`
* `-1000 <= target <= 1000`

```cpp
class Solution {
 public:
  /*
  assume that
  set A include all positive.
  set B include all negative.
  sum(A) - sum(B) == target
  sum(A) - sum(B) - sum(B) == target - sum(B)
  - 2 * sum(B) = target - sum(B) -sum(A)
  2 * sum(B) = sum(nums) - target
  */
  int pack(vector<int>& nums, int target) {
    int n = nums.size();
    vector<vector<int>> dp(n + 1, vector<int>(target + 1));

    for (int k = 0; k <= n; k++) dp[k][0] = 1;

    for (int i = 1; i <= n; i++) {
      for (int j = 0; j <= target; j++) {
        if (j >= nums[i - 1])
          dp[i][j] = dp[i - 1][j - nums[i - 1]] + dp[i - 1][j];
        else
          dp[i][j] = dp[i - 1][j];
      }
    }
    // print2D(dp);
    // fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    return dp.back().back();
  }

  int findTargetSumWays(vector<int>& nums, int target) {
    int total_sum = 0;
    for (int x : nums) {
      total_sum += x;
    }
    if (total_sum < target || (total_sum - target) % 2) return 0;
    return pack(nums, (total_sum - target) / 2);
  }
};
```

-------------

## 分割等和子集

给你一个 只包含正整数 的 非空 数组 `nums` 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

示例 1：

```

输入：nums = [1,5,11,5]
输出：true
解释：数组可以分割成 [1, 5, 5] 和 [11] 。
```

示例 2：

```

输入：nums = [1,2,3,5]
输出：false
解释：数组不能分割成两个元素和相等的子集。

```

提示：

* `1 <= nums.length <= 200`
* `1 <= nums[i] <= 100`

```cpp
class Solution {
 public:
  bool canPartition(vector<int>& nums) {
    int total_sum = 0;
    for (int x : nums) {
      total_sum += x;
    }
    if (total_sum % 2) return false;
    int half_total_sum = total_sum / 2;
    vector<vector<bool>> dp(nums.size() + 1, vector<bool>(half_total_sum + 1));
    dp[0][0] = true;
    for (int i = 1; i <= nums.size(); i++) {
      dp[i][0] = true;
    }

    for (int i = 1; i <= nums.size(); i++) {
      for (int j = 1; j <= half_total_sum; j++) {
        if (j - nums[i - 1] >= 0)
          dp[i][j] = dp[i - 1][j - nums[i - 1]] || dp[i - 1][j];
        else
          dp[i][j] = dp[i - 1][j];
      }
    }
    // print2D(dp);
    return dp.back().back();
  }
};
```

-------------

## 最大正方形

在一个由 `'0'` 和 `'1'` 组成的二维矩阵内，找到只包含 `'1'` 的最大正方形，并返回其面积。

示例 1：
![](https://assets.leetcode.com/uploads/2020/11/26/max1grid.jpg)

```

输入：matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
输出：4

```

示例 2：
![](https://assets.leetcode.com/uploads/2020/11/26/max2grid.jpg)

```

输入：matrix = [["0","1"],["1","0"]]
输出：1

```

示例 3：

```

输入：matrix = [["0"]]
输出：0

```

提示：

* `m == matrix.length`
* `n == matrix[i].length`
* `1 <= m, n <= 300`
* `matrix[i][j]` 为 `'0'` 或 `'1'`

```cpp
class Solution {
 public:
  int maximalSquare(vector<vector<char>>& matrix) {
    int n = matrix.size();
    int m = matrix.at(0).size();
    vector<vector<int>> dp(n, vector<int>(m));
    int max_value = 0;

    for (int i = 0; i < m; i++) {
      dp.at(0).at(i) = matrix.at(0).at(i) - '0';
      max_value = max_value < dp.at(0).at(i) ? dp.at(0).at(i) : max_value;
    }
    for (int i = 0; i < n; i++) {
      dp.at(i).at(0) = matrix.at(i).at(0) - '0';
      max_value = max_value < dp.at(i).at(0) ? dp.at(i).at(0) : max_value;
    }

    for (int col = 1; col < n; col++) {
      for (int row = 1; row < m; row++) {
        if (matrix.at(col).at(row) - '0') {
          dp.at(col).at(row) =
              min(min(dp.at(col - 1).at(row - 1), dp.at(col).at(row - 1)),
                  dp.at(col - 1).at(row)) +
              1;
        } else {
          dp.at(col).at(row) = 0;
        }
        max_value =
            max_value < dp.at(col).at(row) ? dp.at(col).at(row) : max_value;
      }
    }

    // fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    return max_value * max_value;
  }
};
```

-------------

## 零钱兑换

给你一个整数数组 `coins` ，表示不同面额的硬币；以及一个整数 `amount` ，表示总金额。
计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 `-1` 。
你可以认为每种硬币的数量是无限的。

示例 1：

```

输入：coins = [1, 2, 5], amount = 11
输出：3 
解释：11 = 5 + 5 + 1
```

示例 2：

```

输入：coins = [2], amount = 3
输出：-1
```

示例 3：

```

输入：coins = [1], amount = 0
输出：0

```

提示：

* `1 <= coins.length <= 12`
* `1 <= coins[i] <= 231 - 1`
* `0 <= amount <= 104`

```cpp
class Solution {
 public:
  int INF = std::numeric_limits<int>::max();
  int dp_min = INF;
  int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INF);
    dp.at(0) = 0;
    for (int a = 1; a < amount + 1; ++a) {
      for (int c : coins) {
        if (a >= c) {
          dp.at(a) = min(dp.at(a), dp.at(a - c) + 1);
        }
      }
    }
    return dp.at(amount) == INF ? -1 : dp.at(amount);
  }
};
```

-------------

## 全排列 II

给定一个可包含重复数字的序列 `nums` ，按任意顺序 返回所有不重复的全排列。

示例 1：

```

输入：nums = [1,1,2]
输出：
[[1,1,2],
 [1,2,1],
 [2,1,1]]

```

示例 2：

```

输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

```

提示：

* `1 <= nums.length <= 8`
* `-10 <= nums[i] <= 10`

```cpp
class Solution {
 public:
  vector<vector<int>> res = {};
  unordered_map<int, int> visited;

  vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<int> s{};
    for (int i : nums) visited[i]++;
    std::sort(nums.begin(), nums.end());
    backtrack(nums, s, visited);
    return res;
  }

  void backtrack(vector<int>& nums, vector<int> solution,
                 unordered_map<int, int> visited) {
    if (solution.size() == nums.size()) {
      res.push_back(solution);
      return;
    }

    for (int j = 0; j < nums.size(); ++j) {
      if (visited[nums[j]] == 0 || j > 0 && nums[j - 1] == nums[j]) continue;
      visited[nums[j]]--;
      solution.push_back(nums[j]);
      backtrack(nums, solution, visited);
      solution.pop_back();
      visited[nums[j]]++;
    }
  }
};
```

-------------

## 最长递增子序列

给你一个整数数组 `nums` ，找到其中最长严格递增子序列的长度。
子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，`[3,6,2,7]` 是数组 `[0,3,1,6,2,2,7]` 的子序列。

示例 1：

```

输入：nums = [10,9,2,5,3,7,101,18]
输出：4
解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。

```

示例 2：

```

输入：nums = [0,1,0,3,2,3]
输出：4

```

示例 3：

```

输入：nums = [7,7,7,7,7,7,7]
输出：1

```

提示：

* `1 <= nums.length <= 2500`
* `-104 <= nums[i] <= 104`

进阶：

* 你能将算法的时间复杂度降低到 `O(n log(n))` 吗?

```cpp
class Solution {
 public:
  int lengthOfLIS(vector<int>& nums) {
    vector<int> dp(nums.size() + 1, 1);
    for (int i = 0; i < nums.size(); i++) {
      for (int j = 0; j <= i; j++) {
        if (nums[j] < nums[i]) {
          dp[i] = max(dp[i], dp[j] + 1);
        }
      }
    }
    return *max_element(dp.begin(), dp.end());
  }
  int lengthOfLIS_nlogn(vector<int>& nums) {
    vector<vector<int>> top(nums.size(), vector<int>());
    int piles = 0;
    for (int i = 0; i < nums.size(); i++) {
      int poker = nums[i];

      int left = 0, right = piles;
      while (right > 0 && left < right) {
        int mid = left + (right - left) / 2;
        if (top[mid].back() == poker) {
          right = mid;
        } else if (top[mid].back() > poker) {
          right = mid;
        } else if (top[mid].back() < poker) {
          left = mid + 1;
        }
      }

      if (left == piles) piles++;
      // top[left] = poker;
      top[left].push_back(poker);
    }
    // fmt::print("{}\n", top);
    return piles;
  }
};
```

-------------

## 使括号有效的最少添加

只有满足下面几点之一，括号字符串才是有效的：

* 它是一个空字符串，或者
* 它可以被写成 `AB` （`A` 与 `B` 连接）, 其中 `A` 和 `B` 都是有效字符串，或者
* 它可以被写作 `(A)`，其中 `A` 是有效字符串。

给定一个括号字符串 `s` ，在每一次操作中，你都可以在字符串的任何位置插入一个括号

* 例如，如果 `s = "()))"` ，你可以插入一个开始括号为 `"(()))"` 或结束括号为 `"())))"` 。

返回 为使结果字符串 `s` 有效而必须添加的最少括号数。

示例 1：

```

输入：s = "())"
输出：1

```

示例 2：

```

输入：s = "((("
输出：3

```

提示：

* `1 <= s.length <= 1000`
* `s` 只包含 `'('` 和 `')'` 字符。

```cpp
class Solution {
 public:
  int minAddToMakeValid(string s) {
    stack<char> st;
    vector<char> tmp;
    unordered_map<char, char> map = {{']', '['}, {'}', '{'}, {')', '('}};
    for (char c : s) {
      if (st.empty())
        st.push(c);
      else if (c == '{' || c == '(' || c == '[') {
        st.push(c);
      } else {
        while (!st.empty() && st.top() != map[c]) {
          tmp.push_back(st.top());
          st.pop();
        }
        if (st.empty())
          st.push(c);
        else
          st.pop();
        for (char c : tmp) {
          st.push(c);
        }
        tmp.clear();
      }
    }
    return st.size();
  }

  int minAddToMakeValid_simple(string s) {
    // res 记录插入次数
    int res = 0;
    // need 变量记录右括号的需求量
    int need = 0;

    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '(') {
        // 对右括号的需求 + 1
        need++;
      }

      if (s[i] == ')') {
        // 对右括号的需求 - 1
        need--;

        if (need == -1) {
          need = 0;
          // 需插入一个左括号
          res++;
        }
      }
    }

    return res + need;
  }
};
```

-------------

## 课程表

你这个学期必须选修 `numCourses` 门课程，记为 `0` 到 `numCourses - 1` 。
在选修某些课程之前需要一些先修课程。 先修课程按数组 `prerequisites` 给出，其中 `prerequisites[i] = [ai, bi]` ，表示如果要学习课程 `ai` 则 必须 先学习课程  `bi`。

* 例如，先修课程对 `[0, 1]` 表示：想要学习课程 `0` ，你需要先完成课程 `1` 。

请你判断是否可能完成所有课程的学习？如果可以，返回 `true` ；否则，返回 `false` 。

示例 1：

```

输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。
```

示例 2：

```

输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
输出：false
解释：总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。
```

提示：

* `1 <= numCourses <= 2000`
* `0 <= prerequisites.length <= 5000`
* `prerequisites[i].length == 2`
* `0 <= ai, bi < numCourses`
* `prerequisites[i]` 中的所有课程对 互不相同

```cpp

class Solution {
 public:
  void buildGraph(vector<vector<int>>& graph, int numCourses,
                  vector<vector<int>>& prerequisites) {
    graph.resize(numCourses);
    for (auto& edge : prerequisites) {
      int from = edge[1], to = edge[0];
      // 添加一条从 from 指向 to 的有向边
      // 边的方向是「被依赖」关系，即修完课程 from 才能修课程 to
      graph[from].push_back(to);
    }
  }

  void hasCycle_dfs(vector<vector<int>>& graph, int s, vector<bool>& visited,
                    vector<bool>& onPath, bool& has_cycle) {
    if (onPath[s]) {
      // 发现环
      has_cycle = true;
      return;
    }

    if (visited[s]) {
      // 已访问过,无需再访问
      return;
    }

    // 标记当前节点为已访问
    visited[s] = true;

    // 标记当前节点在路径上
    onPath[s] = true;

    // 递归访问相邻节点
    for (int node : graph[s]) {
      hasCycle_dfs(graph, node, visited, onPath, has_cycle);
    }

    // 当前节点访问结束,移出路径
    onPath[s] = false;
  }

  bool canFinish_DFS(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph{};
    vector<bool> visited(numCourses, false);
    vector<bool> onPath(numCourses, false);
    bool has_cycle = false;

    buildGraph(graph, numCourses, prerequisites);

    for (int i = 0; i < numCourses; i++) {
      if (!visited[i]) hasCycle_dfs(graph, i, visited, onPath, has_cycle);
    }

    return !has_cycle;
  }

  bool hasCycle_bfs(vector<vector<int>>& graph) {
    vector<int> inDegree(graph.size(), 0);
    for (auto& neighbors : graph) {
      for (int neighbor : neighbors) {
        inDegree[neighbor]++;
      }
    }

    queue<int> q;
    unordered_set<int> visited;
    for (int i = 0; i < inDegree.size(); i++) {
      if (inDegree[i] == 0) {
        q.push(i);
        visited.insert(i);
      }
    }

    int count = 0;
    while (!q.empty()) {
      int node = q.front();
      q.pop();
      count++;
      for (int neighbor : graph[node]) {
        if (!visited.count(neighbor)) {
          inDegree[neighbor]--;
          if (inDegree[neighbor] == 0) {
            q.push(neighbor);
            visited.insert(neighbor);
          }
        }
      }
    }
    return count == graph.size();
  }

  bool canFinish_BFS(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph{};
    buildGraph(graph, numCourses, prerequisites);
    return hasCycle_bfs(graph);
  }

  bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    const string mode = "BFS";
    if (mode == "DFS")
      return canFinish_DFS(numCourses, prerequisites);
    else
      return canFinish_BFS(numCourses, prerequisites);
  }
};

```

-------------

## 找出字符串中第一个匹配项的下标

给你两个字符串 `haystack` 和 `needle` ，请你在 `haystack` 字符串中找出 `needle` 字符串的第一个匹配项的下标（下标从 0 开始）。如果 `needle` 不是 `haystack` 的一部分，则返回  `-1`。

示例 1：

```

输入：haystack = "sadbutsad", needle = "sad"
输出：0
解释："sad" 在下标 0 和 6 处匹配。
第一个匹配项的下标是 0 ，所以返回 0 。

```

示例 2：

```

输入：haystack = "leetcode", needle = "leeto"
输出：-1
解释："leeto" 没有在 "leetcode" 中出现，所以返回 -1 。

```

提示：

* `1 <= haystack.length, needle.length <= 104`
* `haystack` 和 `needle` 仅由小写英文字符组成

```cpp
class Solution {
 public:
  string pat{};
  vector<vector<int>> dp{};
  void KMP(const string &pattern) {
    int all_char_len = 256;
    pat = pattern;
    int M = pat.size();
    dp.assign(M, vector<int>(all_char_len, 0));
    dp[0][pat[0]] = 1;
    int X = 0;
    for (int j = 1; j < M; j++) {
      for (int c = 0; c < all_char_len; c++) dp[j][c] = dp[X][c];
      dp[j][pat.at(j)] = j + 1;
      X = dp[X][pat.at(j)];
    }
    // fmt::print("{}\n", dp);
  }

  int search(const string &txt) {
    int N = txt.size();
    int M = pat.size();
    int j = 0;
    for (int i = 0; i < N; i++) {
      j = dp[j][txt.at(i)];
      if (j == M) return i - M + 1;
    }
    return -1;
  }

  int strStr(string &haystack, string &needle) {
    KMP(needle);
    return search(haystack);
  }
};
```

-------------

## 被围绕的区域

给你一个 `m x n` 的矩阵 `board` ，由若干字符 `'X'` 和 `'O'` ，找到所有被 `'X'` 围绕的区域，并将这些区域里所有的 `'O'` 用 `'X'` 填充。

示例 1：
![](https://assets.leetcode.com/uploads/2021/02/19/xogrid.jpg)

```

输入：board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
输出：[["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
解释：被围绕的区间不会存在于边界上，换句话说，任何边界上的 'O' 都不会被填充为 'X'。 任何不在边界上，或不与边界上的 'O' 相连的 'O' 最终都会被填充为 'X'。如果两个元素在水平或垂直方向相邻，则称它们是“相连”的。

```

示例 2：

```

输入：board = [["X"]]
输出：[["X"]]

```

提示：

* `m == board.length`
* `n == board[i].length`
* `1 <= m, n <= 200`
* `board[i][j]` 为 `'X'` 或 `'O'`

```cpp
class UnionFind {
 public:
  UnionFind() = delete;
  UnionFind(int n) : count(n) {
    parent.reserve(n);
    for (int i = 0; i < n; i++) {
      parent.emplace_back(i);
    }
  }

  void Union(int p, int q) {
    int rootP = find(p);
    int rootQ = find(q);

    if (rootP == rootQ) return;
    parent[rootQ] = rootP;
    count--;
  }

  bool connected(int p, int q) { return find(p) == find(q); }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  int get_count() const { return count; }

 private:
  int count;
  vector<int> parent;
};

class Solution {
 public:
  int get_index(int row, int col, int m) { return col * m + row; }

  void solve(vector<vector<char>>& board) {
    int n = board.size();
    int m = board[0].size();
    UnionFind uf{n * m + 1};
    int dummy = m * n;
    for (int col = 0; col < n; col++) {
      if (board[col][0] == 'O') uf.Union(dummy, col * m + 0);
      if (board[col][m - 1] == 'O') uf.Union(dummy, col * m + m - 1);
    }
    for (int row = 0; row < m; row++) {
      if (board[0][row] == 'O') uf.Union(dummy, row);
      if (board[n - 1][row] == 'O') uf.Union(dummy, m * (n - 1) + row);
    }

    vector<pair<int, int>> actions = {
        {-1, 0},
        {0, -1},
        {1, 0},
        {0, 1},
    };
    int x = 0, y = 0;
    for (int col = 1; col < n - 1; col++) {
      for (int row = 1; row < m - 1; row++) {
        for (auto& p : actions) {
          x = p.first, y = p.second;
          if (board[col][row] == 'O' && board[col + y][row + x] == 'O') {
            uf.Union(get_index(row, col, m), get_index(row + x, col + y, m));
          }
        }
      }
    }

    for (int col = 0; col < n; col++) {
      for (int row = 0; row < m; row++) {
        if (board[col][row] == 'O' &&
            !uf.connected(dummy, get_index(row, col, m)))
          board[col][row] = 'X';
      }
    }
  }
};
```

-------------

## 正则表达式匹配

给你一个字符串 `s` 和一个字符规律 `p`，请你来实现一个支持 `'.'` 和 `'*'` 的正则表达式匹配。

* `'.'` 匹配任意单个字符
* `'*'` 匹配零个或多个前面的那一个元素

所谓匹配，是要涵盖 整个字符串 `s`的，而不是部分字符串。

示例 1：

```

输入：s = "aa", p = "a"
输出：false
解释："a" 无法匹配 "aa" 整个字符串。

```

示例 2:

```

输入：s = "aa", p = "a*"
输出：true
解释：因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。

```

示例 3：

```

输入：s = "ab", p = ".*"
输出：true
解释：".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。

```

提示：

* `1 <= s.length <= 20`
* `1 <= p.length <= 20`
* `s` 只包含从 `a-z` 的小写字母。
* `p` 只包含从 `a-z` 的小写字母，以及字符 `.` 和 `*`。
* 保证每次出现字符 `*` 时，前面都匹配到有效的字符

```cpp
class Solution {
 public:
  bool match(const string &s, const string &p, int i, int j) {
    if (i == 0) {
      return false;
    }
    if (p[j - 1] == '.') {
      return true;
    }
    return s[i - 1] == p[j - 1];
  }

  /*
  f[i][j]=
    if (p[j] != ‘*’)
      f[i−1][j−1]    matches(s[i],p[j])
      false          otherwise
    else
      f[i−1][j] (match many times) or f[i][j−2] (match 0 times)   matches(s[i],p[j−1])
      f[i][j−2]                                                   otherwise
  */

  bool isMatch(string s, string p) {
    vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1, false));
    dp[0][0] = true;
    for (int i = 0; i <= s.size(); i++) {
      for (int j = 1; j <= p.size(); j++) {
        if (p[j - 1] != '*')
          if (match(s, p, i, j))
            dp[i][j] = dp[i - 1][j - 1];
          else
            dp[i][j] = false;
        else if (match(s, p, i, j - 1))
          dp[i][j] = dp[i][j - 2] || dp[i - 1][j];
        else
          dp[i][j] = dp[i][j - 2];
      }
    }
    print2D(dp);
    return dp.back().back();
  }
};
```

-------------

## 验证回文串

如果在将所有大写字符转换为小写字符、并移除所有非字母数字字符之后，短语正着读和反着读都一样。则可以认为该短语是一个 回文串 。
字母和数字都属于字母数字字符。
给你一个字符串 `s`，如果它是 回文串 ，返回 `true`；否则，返回`false`。

示例 1：

```

输入: s = "A man, a plan, a canal: Panama"
输出：true
解释："amanaplanacanalpanama" 是回文串。

```

示例 2：

```

输入：s = "race a car"
输出：false
解释："raceacar" 不是回文串。

```

示例 3：

```

输入：s = " "
输出：true
解释：在移除非字母数字字符之后，s 是一个空字符串 "" 。
由于空字符串正着反着读都一样，所以是回文串。

```

提示：

* `1 <= s.length <= 2 * 105`
* `s` 仅由可打印的 ASCII 字符组成

```cpp
class Solution {
 public:
  bool isPalindrome(string& s) {
    char r[s.size() + 1];
    int j;
    int i;
    for (i = 0, j = 0; j < s.size(); j++) {
      if (s[j] >= 'a' && s[j] <= 'z') {
        r[i] = s[j];
        i++;
      } else if (s[j] >= 'A' && s[j] <= 'Z') {
        r[i] = s[j] | ' ';  // note 'A' | ' ' = 'a'
        // r[i] = s[j] + ('a' - 'A');
        i++;
      } else if (s[j] >= '0' && s[j] <= '9') {
        r[i] = s[j];
        i++;
      }
    }
    r[i] = 0;
    string rs = &r[0];
    // fmt::print("{}\n", rs);
    int f = 0, b = rs.size() - 1;
    while (f < b) {
      if (rs[f] != r[b]) return false;
      f++;
      b--;
    }
    return true;
  }
};
```

-------------

## 课程表 II

现在你总共有 `numCourses` 门课需要选，记为 `0` 到 `numCourses - 1`。给你一个数组 `prerequisites` ，其中 `prerequisites[i] = [ai, bi]` ，表示在选修课程 `ai` 前 必须 先选修 `bi` 。

* 例如，想要学习课程 `0` ，你需要先完成课程 `1` ，我们用一个匹配来表示：`[0,1]` 。

返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序，你只要返回 任意一种 就可以了。如果不可能完成所有课程，返回 一个空数组 。

示例 1：

```

输入：numCourses = 2, prerequisites = [[1,0]]
输出：[0,1]
解释：总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 [0,1] 。

```

示例 2：

```

输入：numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
输出：[0,2,1,3]
解释：总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和课程 2。并且课程 1 和课程 2 都应该排在课程 0 之后。
因此，一个正确的课程顺序是 [0,1,2,3] 。另一个正确的排序是 [0,2,1,3] 。
```

示例 3：

```

输入：numCourses = 1, prerequisites = []
输出：[0]

```

提示：

* `1 <= numCourses <= 2000`
* `0 <= prerequisites.length <= numCourses * (numCourses - 1)`
* `prerequisites[i].length == 2`
* `0 <= ai, bi < numCourses`
* `ai != bi`
* 所有`[ai, bi]` 互不相同

```cpp
class Solution {
 public:
  void buildGraph(vector<vector<int>>& graph, int numCourses,
                  vector<vector<int>>& prerequisites) {
    graph.resize(numCourses);
    for (auto& edge : prerequisites) {
      int from = edge[1], to = edge[0];
      // 添加一条从 from 指向 to 的有向边
      // 边的方向是「被依赖」关系，即修完课程 from 才能修课程 to
      graph[from].push_back(to);
    }
  }
  void topology_order_dfs(vector<vector<int>>& graph, int s,
                          vector<bool>& visited, vector<bool>& onPath,
                          bool& has_cycle, vector<int>& res) {
    if (onPath[s]) {
      // 发现环
      has_cycle = true;
      return;
    }

    if (visited[s]) {
      // 已访问过,无需再访问
      return;
    }

    // 标记当前节点为已访问
    visited[s] = true;

    // 标记当前节点在路径上
    onPath[s] = true;

    // 递归访问相邻节点
    for (int node : graph[s]) {
      topology_order_dfs(graph, node, visited, onPath, has_cycle, res);
    }

    // 当前节点访问结束,移出路径
    onPath[s] = false;
    res.push_back(s);
  }

  vector<int> findOrder_DFS(int numCourses,
                            vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph{};
    vector<bool> visited(numCourses, false);
    vector<bool> onPath(numCourses, false);
    vector<int> res;
    bool has_cycle = false;

    buildGraph(graph, numCourses, prerequisites);
    // print2D(graph);
    for (int i = 0; i < numCourses && !has_cycle; i++) {
      if (!visited[i]) {
        topology_order_dfs(graph, i, visited, onPath, has_cycle, res);
      }
    }

    if (has_cycle) {
      return {};
    }

    reverse(res.begin(), res.end());
    return res;
  }

  vector<int> topology_order_bfs(vector<vector<int>>& graph) {
    vector<int> in_degree(graph.size(), 0);
    for (auto& neighbors : graph) {
      for (int neighbor : neighbors) {
        in_degree[neighbor]++;
      }
    }

    queue<int> q;
    unordered_set<int> visited;
    for (int i = 0; i < in_degree.size(); i++) {
      if (in_degree[i] == 0) {
        q.push(i);
        visited.insert(i);
      }
    }

    vector<int> res;
    while (!q.empty()) {
      int node = q.front();
      q.pop();
      res.push_back(node);
      for (int neighbor : graph[node]) {
        in_degree[neighbor]--;
        if (in_degree[neighbor] == 0) {
          q.push(neighbor);
          visited.insert(neighbor);
        }
      }
    }

    if (res.size() != graph.size()) {
      return {};
    }

    return res;
  }

  vector<int> findOrder_BFS(int numCourses,
                            vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph{};
    buildGraph(graph, numCourses, prerequisites);
    return topology_order_bfs(graph);
  }

  vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    const string mode = "BFS";
    if (mode == "DFS")
      return findOrder_DFS(numCourses, prerequisites);
    else
      return findOrder_BFS(numCourses, prerequisites);
  }
};
```

-------------

## 全排列

给定一个不含重复数字的数组 `nums` ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。

示例 1：

```

输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

```

示例 2：

```

输入：nums = [0,1]
输出：[[0,1],[1,0]]

```

示例 3：

```

输入：nums = [1]
输出：[[1]]

```

提示：

* `1 <= nums.length <= 6`
* `-10 <= nums[i] <= 10`
* `nums` 中的所有整数 互不相同

```cpp
class Solution {
 public:
  vector<vector<int>> res = {};
  vector<vector<int>> permute(vector<int>& nums) {
    vector<int> s{};
    backtrack(nums, s);
    return res;
  }

  void backtrack(vector<int>& nums, vector<int> solution) {
    if (solution.size() == nums.size()) {
      res.push_back(solution);
      return;
    }
    for (int c : nums) {
      if (find(solution.begin(), solution.end(), c) != solution.end()) continue;
      solution.push_back(c);
      backtrack(nums, solution);
      solution.pop_back();
    }
  }
};
```

-------------

## 有效的括号

给定一个只包括 `'('`，`')'`，`'{'`，`'}'`，`'['`，`']'` 的字符串 `s` ，判断字符串是否有效。
有效字符串需满足：

1. 左括号必须用相同类型的右括号闭合。
2. 左括号必须以正确的顺序闭合。
3. 每个右括号都有一个对应的相同类型的左括号。

示例 1：

```

输入：s = "()"
输出：true

```

示例 2：

```

输入：s = "()[]{}"
输出：true

```

示例 3：

```

输入：s = "(]"
输出：false

```

提示：

* `1 <= s.length <= 104`
* `s` 仅由括号 `'()[]{}'` 组成

```cpp
class Solution {
 public:
  bool isValid(string str) {
    stack<char> left;
    for (char c : str) {
      if (c == '(' || c == '{' || c == '[')
        left.push(c);
      else {  // 字符 c 是右括号
        if (!left.empty() && leftOf(c) == left.top())
          left.pop();
        else
          // 和最近的左括号不匹配
          return false;
      }
    }
    // 是否所有的左括号都被匹配了
    return left.empty();
  }

  char leftOf(char c) {
    if (c == '}') return '{';
    if (c == ')') return '(';
    return '[';
  }
};
```

-------------

## 删除二叉搜索树中的节点

给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的 key对应的节点，并保证二叉搜索树的性质不变。返回二叉搜索树（有可能被更新）的根节点的引用。
一般来说，删除节点可分为两个步骤：

1. 首先找到需要删除的节点；
2. 如果找到了，删除它。

示例 1:
![](https://assets.leetcode.com/uploads/2020/09/04/del_node_1.jpg)

```

输入：root = [5,3,6,2,4,null,7], key = 3
输出：[5,4,6,2,null,null,7]
解释：给定需要删除的节点值是 3，所以我们首先找到 3 这个节点，然后删除它。
一个正确的答案是 [5,4,6,2,null,null,7], 如下图所示。
另一个正确答案是 [5,2,6,null,4,null,7]。

![](https://assets.leetcode.com/uploads/2020/09/04/del_node_supp.jpg)

```

示例 2:

```

输入: root = [5,3,6,2,4,null,7], key = 0
输出: [5,3,6,2,4,null,7]
解释: 二叉树不包含值为 0 的节点

```

示例 3:

```

输入: root = [], key = 0
输出: []
```

提示:

* 节点数的范围 `[0, 104]`.
* `-105 <= Node.val <= 105`
* 节点值唯一
* `root` 是合法的二叉搜索树
* `-105 <= key <= 105`

进阶： 要求算法时间复杂度为 O(h)，h 为树的高度。

```cpp
class Solution {
 public:
  TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return root;
    if (root->val == key) {
      if (!root->left && !root->right) return nullptr;
      if (!root->left && root->right) return root->right;
      if (!root->right && root->left) return root->left;
      TreeNode* min_n = root->right;
      while (min_n->left != nullptr) min_n = min_n->left;
      root->val = min_n->val;
      root->right = deleteNode(root->right, min_n->val);
    } else if (root->val > key) {
      root->left = deleteNode(root->left, key);
    } else if (root->val < key) {
      root->right = deleteNode(root->right, key);
    }
    return root;
  }
};
```

-------------

## 判断二分图

存在一个 无向图 ，图中有 `n` 个节点。其中每个节点都有一个介于 `0` 到 `n - 1` 之间的唯一编号。给你一个二维数组 `graph` ，其中 `graph[u]` 是一个节点数组，由节点 `u` 的邻接节点组成。形式上，对于 `graph[u]` 中的每个 `v` ，都存在一条位于节点 `u` 和节点 `v` 之间的无向边。该无向图同时具有以下属性：

* 不存在自环（`graph[u]` 不包含 `u`）。
* 不存在平行边（`graph[u]` 不包含重复值）。
* 如果 `v` 在 `graph[u]` 内，那么 `u` 也应该在 `graph[v]` 内（该图是无向图）
* 这个图可能不是连通图，也就是说两个节点 `u` 和 `v` 之间可能不存在一条连通彼此的路径。

二分图 定义：如果能将一个图的节点集合分割成两个独立的子集 `A` 和 `B` ，并使图中的每一条边的两个节点一个来自 `A` 集合，一个来自 `B` 集合，就将这个图称为 二分图 。
如果图是二分图，返回 `true`；否则，返回 `false` 。

示例 1：
![](https://assets.leetcode.com/uploads/2020/10/21/bi2.jpg)

```

输入：graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
输出：false
解释：不能将节点分割成两个独立的子集，以使每条边都连通一个子集中的一个节点与另一个子集中的一个节点。
```

示例 2：
![](https://assets.leetcode.com/uploads/2020/10/21/bi1.jpg)

```

输入：graph = [[1,3],[0,2],[1,3],[0,2]]
输出：true
解释：可以将节点分成两组: {0, 2} 和 {1, 3} 。
```

提示：

* `graph.length == n`
* `1 <= n <= 100`
* `0 <= graph[u].length < n`
* `0 <= graph[u][i] <= n - 1`
* `graph[u]` 不会包含 `u`
* `graph[u]` 的所有值 互不相同
* 如果 `graph[u]` 包含 `v`，那么 `graph[v]` 也会包含 `u`

```cpp
class Solution {
 public:
  bool dfs(vector<vector<int>>& graph, vector<int>& color, int node,
           vector<bool>& visited) {
    for (int neighbor : graph[node]) {
      if (!visited[neighbor]) {
        color[neighbor] = -color[node];
        visited[neighbor] = true;
        if (!dfs(graph, color, neighbor, visited)) {
          return false;
        }
      } else if (color[neighbor] == color[node]) {
        return false;
      }
    }
    return true;
  }

  bool isBipartite(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> color(n, 0);
    vector<bool> visited(n, false);

    for (int i = 0; i < n; ++i) {
      if (color[i] == 0 && !visited[i]) {
        color[i] = 1;
        visited[i] = true;
        if (!dfs(graph, color, i, visited)) {
          return false;
        }
      }
    }
    return true;
  }
};
```

-------------

## 下一个更大元素 II

给定一个循环数组 `nums` （ `nums[nums.length - 1]` 的下一个元素是 `nums[0]` ），返回 `nums` 中每个元素的 下一个更大元素 。
数字 `x` 的 下一个更大的元素 是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 `-1` 。

示例 1:

```

输入: nums = [1,2,1]
输出: [2,-1,2]
解释: 第一个 1 的下一个更大的数是 2；
数字 2 找不到下一个更大的数； 
第二个 1 的下一个最大的数需要循环搜索，结果也是 2。

```

示例 2:

```

输入: nums = [1,2,3,4,3]
输出: [2,3,4,-1,4]

```

提示:

* `1 <= nums.length <= 104`
* `-109 <= nums[i] <= 109`

```cpp
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
```

-------------

## 滑动窗口最大值

给你一个整数数组 `nums`，有一个大小为 `k`的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 `k` 个数字。滑动窗口每次只向右移动一位。
返回 滑动窗口中的最大值 。

示例 1：

```

输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]
解释：
滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

```

示例 2：

```

输入：nums = [1], k = 1
输出：[1]

```

提示：

* `1 <= nums.length <= 105`
* `-104 <= nums[i] <= 104`
* `1 <= k <= nums.length`

```cpp
template <typename T>
class MonotonicQueue {
 public:
  deque<T> q;
  MonotonicQueue() : q(){};
  ~MonotonicQueue() = default;
  // void Print() const { fmt::print("{}\n", q); }
  void push(T& elem) {
    while (!q.empty() && q.back() < elem) q.pop_back();
    q.push_back(elem);
  }
  void pop(T& elem) {
    if (q.front() == elem) q.pop_front();
  }
  T& max() { return q.front(); }
};

class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    MonotonicQueue<int> window;
    vector<int> res;
    for (int i = 0; i < nums.size(); i++) {
      if (i < k - 1) {
        window.push(nums[i]);
      } else {
        // window.Print();
        window.push(nums[i]);
        res.push_back(window.max());
        window.pop(nums[i - k + 1]);
      }
    }
    // fmt::print("{}\n", res);
    return res;
  }
};
```

-------------

## 寻找两个正序数组的中位数

给定两个大小分别为 `m` 和 `n` 的正序（从小到大）数组 `nums1` 和 `nums2`。请你找出并返回这两个正序数组的 中位数 。
算法的时间复杂度应该为 `O(log (m+n))` 。

示例 1：

```

输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并数组 = [1,2,3] ，中位数 2

```

示例 2：

```

输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5

```

提示：

* `nums1.length == m`
* `nums2.length == n`
* `0 <= m <= 1000`
* `0 <= n <= 1000`
* `1 <= m + n <= 2000`
* `-106 <= nums1[i], nums2[i] <= 106`

```cpp
class Solution {
 public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    if (nums1.size() > nums2.size()) {
      return findMedianSortedArrays(nums2, nums1);
    }
    int m = nums1.size(), n = nums2.size();
    int left = 0, right = m;
    int median1 = 0, median2 = 0;
    while (left <= right) {
      // the mid of bi-search.
      int i = (left + right) / 2;
      // the middle of two arrays for index of the second array.
      // since the total numbers is constant, we can get j
      // (the index of second array) from i.
      // this means the (left set - the right set) == 1 if (m + n) % 2 != 0.
      int j = (m + n + 1) / 2 - i;

      // 1 3 | 5
      // 2 4 | 6 7

      int nums_im1 = (i == 0 ? INT_MIN : nums1[i - 1]);  // 3
      int nums_i = (i == m ? INT_MAX : nums1[i]);        // 5
      int nums_jm1 = (j == 0 ? INT_MIN : nums2[j - 1]);  // 4
      int nums_j = (j == n ? INT_MAX : nums2[j]);        // 6

      if (nums_im1 <= nums_j) {
        median1 = max(nums_im1, nums_jm1);
        median2 = min(nums_i, nums_j);
        left = i + 1;
      } else {
        right = i - 1;
      }
    }
    return (m + n) % 2 == 0 ? (median1 + median2) / 2.0 : median1;
  }
};
```

-------------

## 验证二叉搜索树

给你一个二叉树的根节点 `root` ，判断其是否是一个有效的二叉搜索树。
有效 二叉搜索树定义如下：

* 节点的左子树只包含 小于 当前节点的数。
* 节点的右子树只包含 大于 当前节点的数。
* 所有左子树和右子树自身必须也是二叉搜索树。

示例 1：
![](https://assets.leetcode.com/uploads/2020/12/01/tree1.jpg)

```

输入：root = [2,1,3]
输出：true

```

示例 2：
![](https://assets.leetcode.com/uploads/2020/12/01/tree2.jpg)

```

输入：root = [5,1,4,null,null,3,6]
输出：false
解释：根节点的值是 5 ，但是右子节点的值是 4 。

```

提示：

* 树中节点数目范围在`[1, 104]` 内
* `-231 <= Node.val <= 231 - 1`

```cpp
class Solution {
 public:
  bool isValidBST_helper(TreeNode *root, TreeNode *min, TreeNode *max) {
    if (!root) return true;
    if (min && min->val >= root->val) return false;
    if (max && max->val <= root->val) return false;
    return isValidBST_helper(root->left, min, root) &&
           isValidBST_helper(root->right, root, max);
  }
  bool isValidBST(TreeNode *root) {
    return isValidBST_helper(root, nullptr, nullptr);
  }
};
```

-------------

## 零钱兑换 II

给你一个整数数组 `coins` 表示不同面额的硬币，另给一个整数 `amount` 表示总金额。
请你计算并返回可以凑成总金额的硬币组合数。如果任何硬币组合都无法凑出总金额，返回 `0` 。
假设每一种面额的硬币有无限个。
题目数据保证结果符合 32 位带符号整数。

示例 1：

```

输入：amount = 5, coins = [1, 2, 5]
输出：4
解释：有四种方式可以凑成总金额：
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1

```

示例 2：

```

输入：amount = 3, coins = [2]
输出：0
解释：只用面额 2 的硬币不能凑成总金额 3 。

```

示例 3：

```

输入：amount = 10, coins = [10] 
输出：1

```

提示：

* `1 <= coins.length <= 300`
* `1 <= coins[i] <= 5000`
* `coins` 中的所有值 互不相同
* `0 <= amount <= 5000`

```cpp
class Solution {
 public:
  int change(int amount, vector<int>& coins) {
    vector<vector<int>> dp(amount + 1, vector<int>(coins.size() + 1));
    for (int j = 1; j <= coins.size(); ++j) {
      dp.at(0).at(j) = 1;
    }
    for (int a = 0; a <= amount; ++a) {
      dp.at(a).at(0) = 0;
    }
    for (int a = 1; a <= amount; ++a) {
      for (int j = 1; j <= coins.size(); ++j) {
        if (a > coins.at(j - 1))
          dp.at(a).at(j) =
              dp.at(a).at(j - 1) + dp.at(a - coins.at(j - 1)).at(j);
        else if (a == coins.at(j - 1))
          dp.at(a).at(j) = dp.at(a).at(j - 1) + 1;
        else
          dp.at(a).at(j) = dp.at(a).at(j - 1);
      }
    }
    print2D(dp);
    return dp.at(amount).at(coins.size());
  }
};
```

-------------

## 打开转盘锁

你有一个带有四个圆形拨轮的转盘锁。每个拨轮都有10个数字： `'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'` 。每个拨轮可以自由旋转：例如把 `'9'` 变为 `'0'`，`'0'` 变为 `'9'` 。每次旋转都只能旋转一个拨轮的一位数字。
锁的初始数字为 `'0000'` ，一个代表四个拨轮的数字的字符串。
列表 `deadends` 包含了一组死亡数字，一旦拨轮的数字和列表里的任何一个元素相同，这个锁将会被永久锁定，无法再被旋转。
字符串 `target` 代表可以解锁的数字，你需要给出解锁需要的最小旋转次数，如果无论如何不能解锁，返回 `-1` 。

示例 1:

```

输入：deadends = ["0201","0101","0102","1212","2002"], target = "0202"
输出：6
解释：
可能的移动序列为 "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202"。
注意 "0000" -> "0001" -> "0002" -> "0102" -> "0202" 这样的序列是不能解锁的，
因为当拨动到 "0102" 时这个锁就会被锁定。

```

示例 2:

```

输入: deadends = ["8888"], target = "0009"
输出：1
解释：把最后一位反向旋转一次即可 "0000" -> "0009"。

```

示例 3:

```

输入: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
输出：-1
解释：无法旋转到目标数字且不被锁定。

```

提示：

* `1 <= deadends.length <= 500`
* `deadends[i].length == 4`
* `target.length == 4`
* `target` 不在 `deadends` 之中
* `target` 和 `deadends[i]` 仅由若干位数字组成

```cpp
class Solution {
 public:
  string plusOne(string current, int j) {
    if (current[j] == '9')
      current[j] = '0';
    else
      current[j] += 1;
    return current;
  }

  string minusOne(string current, int j) {
    if (current[j] == '0')
      current[j] = '9';
    else
      current[j] -= 1;
    return current;
  }

  int BFS(string start, string target, unordered_set<string> visited) {
    queue<string> q;
    visited.insert(start);
    q.push(start);
    int step = 0;

    string cur = "";
    string p = "";
    string m = "";
    while (!q.empty()) {
      int sz = q.size();
      for (int i = 0; i < sz; ++i) {
        cur = q.front();
        q.pop();

        if (cur == target) {
          return step;
        }
        for (int i = 0; i <= 3; i++) {
          p = plusOne(cur, i);
          if (visited.count(p) == 0) {
            q.push(p);
            visited.insert(p);
          }
          m = minusOne(cur, i);
          if (visited.count(m) == 0) {
            q.push(m);
            visited.insert(m);
          }
        }
      }
      step++;
    }
    return -1;
  }

  int openLock(vector<string> &deadends, string target) {
    unordered_set<string> deadends_set(deadends.begin(), deadends.end());
    if ("0000" == target) return 0;

    if (deadends_set.count("0000")) return -1;

    return BFS("0000", target, deadends_set);
  }
};
```

-------------

## 合并 K 个升序链表

给你一个链表数组，每个链表都已经按升序排列。
请你将所有链表合并到一个升序链表中，返回合并后的链表。

示例 1：

```
输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6

```

示例 2：

```
输入：lists = []
输出：[]

```

示例 3：

```
输入：lists = [[]]
输出：[]

```

提示：

* `k == lists.length`
* `0 <= k <= 10^4`
* `0 <= lists[i].length <= 500`
* `-10^4 <= lists[i][j] <= 10^4`
* `lists[i]` 按 升序 排列
* `lists[i].length` 的总和不超过 `10^4`

```cpp
struct Compare {
  bool operator()(const pair<int, int> a, const pair<int, int> b) {
    return a.first > b.first;
  }
};

// Use the heap to find the min value among k values.
class Solution {
 public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (!lists.size()) return nullptr;
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    ListNode dummy(-20000);
    vector<ListNode*> ptrs(lists);
    for (int i = 0; i < lists.size(); i++) {
      if (ptrs[i]) pq.push(make_pair(ptrs[i]->val, i));
    }

    ListNode* construct_ptr = &dummy;

    while (!pq.empty()) {
      auto cur = pq.top();
      pq.pop();
      construct_ptr->next = new ListNode(cur.first);
      construct_ptr = construct_ptr->next;
      if (ptrs[cur.second]) {
        ptrs[cur.second] = ptrs[cur.second]->next;
        if (ptrs[cur.second])
          pq.push(make_pair(ptrs[cur.second]->val, cur.second));
      }
    }
    return dummy.next;
  }
};
```

-------------

## 找到小镇的法官

小镇里有 `n` 个人，按从 `1` 到 `n` 的顺序编号。传言称，这些人中有一个暗地里是小镇法官。
如果小镇法官真的存在，那么：

1. 小镇法官不会信任任何人。
2. 每个人（除了小镇法官）都信任这位小镇法官。
3. 只有一个人同时满足属性 1 和属性 2 。

给你一个数组 `trust` ，其中 `trust[i] = [ai, bi]` 表示编号为 `ai` 的人信任编号为 `bi` 的人。
如果小镇法官存在并且可以确定他的身份，请返回该法官的编号；否则，返回 `-1` 。

示例 1：

```

输入：n = 2, trust = [[1,2]]
输出：2

```

示例 2：

```

输入：n = 3, trust = [[1,3],[2,3]]
输出：3

```

示例 3：

```

输入：n = 3, trust = [[1,3],[2,3],[3,1]]
输出：-1

```

提示：

* `1 <= n <= 1000`
* `0 <= trust.length <= 104`
* `trust[i].length == 2`
* `trust` 中的所有`trust[i] = [ai, bi]` 互不相同
* `ai != bi`
* `1 <= ai, bi <= n`

```cpp
class Solution {
public:
    int knows_cnt = 0;
    vector<vector<int>> graph;
    void buildGraph(int n, vector<vector<int>> trust) {
      int cand = 0;
      int other = 0;
      graph = vector<vector<int>>(n + 1, vector<int>(n + 1));
      for (auto &t : trust){
        cand = t[0];
        other = t[1];
        graph[cand][other] = 1;
      }
    }

    int knows(int i, int j){
      knows_cnt += 1;
      return graph[i][j];
    }

    int findJudge(int n, vector<vector<int>>& trust) {
      buildGraph(n, trust);
      int cand = 1;
      for (int other = 1; other <= n; other++){
        // if candidate knows other, the candidate is not the 
        // celebrity. or if others do no know the candidate,
        // then the candidate will not be the celebrity.
        // the candidate should not change in the other situation. 
        if (knows(cand, other) || !knows(other, cand)){
          cand = other;
        }
      }
      // we need to validate the candidate is celebrity.
      for (int i = 1; i <= n; i++){
        if (cand != i){
          if (!knows(i, cand) || knows(cand, i)) {
            return -1;
          }
        }
      }
      return cand;
    }
};
```

-------------

## 考场就座

在考场里，一排有 `N` 个座位，分别编号为 `0, 1, 2, ..., N-1` 。
当学生进入考场后，他必须坐在能够使他与离他最近的人之间的距离达到最大化的座位上。如果有多个这样的座位，他会坐在编号最小的座位上。(另外，如果考场里没有人，那么学生就坐在 0 号座位上。)
返回 `ExamRoom(int N)` 类，它有两个公开的函数：其中，函数 `ExamRoom.seat()` 会返回一个 `int` （整型数据），代表学生坐的位置；函数 `ExamRoom.leave(int p)` 代表坐在座位 `p` 上的学生现在离开了考场。每次调用 `ExamRoom.leave(p)` 时都保证有学生坐在座位 `p` 上。

示例：

```
输入：["ExamRoom","seat","seat","seat","seat","leave","seat"], [[10],[],[],[],[],[4],[]]
输出：[null,0,9,4,2,null,5]
解释：
ExamRoom(10) -> null
seat() -> 0，没有人在考场里，那么学生坐在 0 号座位上。
seat() -> 9，学生最后坐在 9 号座位上。
seat() -> 4，学生最后坐在 4 号座位上。
seat() -> 2，学生最后坐在 2 号座位上。
leave(4) -> null
seat() -> 5，学生最后坐在 5 号座位上。

```

提示：

1. `1 <= N <= 10^9`
2. 在所有的测试样例中 `ExamRoom.seat()` 和 `ExamRoom.leave()` 最多被调用 `10^4` 次。
3. 保证在调用 `ExamRoom.leave(p)` 时有学生正坐在座位 `p` 上。

```cpp
// https://github.com/Alwaysproblem/fucking-algorithm/blob/master/%E9%AB%98%E9%A2%91%E9%9D%A2%E8%AF%95%E7%B3%BB%E5%88%97/%E5%BA%A7%E4%BD%8D%E8%B0%83%E5%BA%A6.md
/*
 * The idea of this is find the longest the duration.
 * The middle point of that duration is seat allocated.
 * when students leave, the duration ends with this student
 * and that starts with the student should merge into one.
 * 
 * -1 []  []  []  []  []  []  []  []  []  [] 10
 *    0   1   2   3   4   5   6   7   8   9
 * 
 * 0: we add -1 and 10.
 * 1: we choose 0.
 * 2: we choose the end of [0 - 10], 9.
 * 3: we choost the middle of [0 - 9], (9 - 0) // 2 + 0 = 4
 * 4: we have the [0 - 4] and [4 - 9]. sort with (4 - 0) // 2 == (9 - 4) // 2 because it equal so we choose the smaller index, 2.
 * 5: we have the [0 - 2], [2 - 4], [4 - 9] and sort with (y - x) // 2. [4 - 9][0 - 2][2 - 4] and find the largest and cut the middle, 5.
 * 6: if student 4 leaving, [0 - 2], [2 - 4], [4 - 5], [5 - 9]. it will be [0 - 2], [2 - 5], [5 - 9].
 * 
 * 
 * NB:
 * if x == -1 then the distance return y
 * if y == N(10 in example above) then the distance return N - 1 - x.
 * In cpp, the key_compare object must be not changed.
 * so we push the N at last of vector.
 */
class ExamRoom {
 public:
  struct Compare {
    bool operator()(const vector<int>& n1, const vector<int>& n2) const {
      int distA = distance(n1);
      int distB = distance(n2);
      if (distA == distB) return n1[0] < n2[0];
      // the larger distance will be in the front.
      return distA > distB;
    }
  };
  unordered_map<int, vector<int>> startsMap;
  unordered_map<int, vector<int>> endsMap;
  set<vector<int>, Compare> pq;
  int N;

  ExamRoom(int n) : startsMap(), endsMap(), pq(), N(n) {
    addInterval({-1, N, N});
    // fmt::print("{}\n", startsMap);
    // fmt::print("{}\n", endsMap);
    // fmt::print("{}\n", pq);
  }

  void addInterval(vector<int>&& intv) {
    if (!intv.size()) {
      cout << "addInterval: intv size = 0" << endl;
    }
    pq.emplace(intv);
    startsMap[intv[0]] = intv;
    endsMap[intv[1]] = intv;
    // fmt::print("addInterval\n");
    // fmt::print("{}\n", startsMap);
    // fmt::print("{}\n", endsMap);
    // fmt::print("{}\n", pq);
  }

  void addInterval(vector<int>& intv) { addInterval(std::move(intv)); }

  void removeInterval(vector<int>& intv) {
    return removeInterval(std::move(intv));
  }

  void removeInterval(vector<int>&& intv) {
    if (!intv.size()) {
      cout << "removeInterval: intv size = 0" << endl;
    }
    startsMap.erase(intv[0]);
    endsMap.erase(intv[1]);
    pq.erase(intv);
    // fmt::print("removeInterval\n");
    // fmt::print("{}\n", startsMap);
    // fmt::print("{}\n", endsMap);
    // fmt::print("{}\n", pq);
  }

  static int distance(const vector<int>& intv) {
    int x = intv[0];
    int y = intv[1];
    if (x == -1) return y;
    // record the N since the campare object is
    // constant after declaration.
    if (y == intv[2]) return intv[2] - 1 - x;
    return (y - x) / 2;
  }

  int seat() {
    // fmt::print("allocated seat:\n");
    vector<int> longest = *(pq.begin());
    int seat_pos = -1;
    int x = longest[0];
    int y = longest[1];
    removeInterval(longest);
    if (x == -1) {
      seat_pos = 0;
    } else if (y == N) {
      seat_pos = N - 1;
    } else {
      seat_pos = x + (y - x) / 2;
    }
    addInterval({x, seat_pos, N});
    addInterval({seat_pos, y, N});
    return seat_pos;
  }

  void leave(int p) {
    // fmt::print("{} is leaving:\n", p);
    if (startsMap.find(p) == startsMap.end() &&
        endsMap.find(p) == endsMap.end()) {
      // fmt::print(
      // "{} can not be found in"
      // " both startsMap, endsMap\n",
      // p);
      return;
    }
    auto s = startsMap.find(p)->second;
    auto e = endsMap.find(p)->second;
    int y = s[1];
    int x = e[0];
    // fmt::print("s: {}\n", s);
    // fmt::print("e: {}\n", e);
    removeInterval(s);
    removeInterval(e);
    addInterval({x, y, N});
    // fmt::print("Done\n", p);
  }
};
```

-------------

## 买卖股票的最佳时机

给定一个数组 `prices` ，它的第 `i` 个元素 `prices[i]` 表示一支给定股票第 `i` 天的价格。
你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。
返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 `0` 。

示例 1：

```

输入：[7,1,5,3,6,4]
输出：5
解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。

```

示例 2：

```

输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 没有交易完成, 所以最大利润为 0。

```

提示：

* `1 <= prices.length <= 105`
* `0 <= prices[i] <= 104`

```cpp
/*
* 首先，还是一样的思路：如何穷举？
* 
* 动态规划核心套路
* 说过，动态规划算法本质上就是穷举「状态」，然后在「选择」中选择最优解。
* 
* 那么对于这道题，我们具体到每一天，看看总共有几种可能的「状态」，再找出每个「状态」对应的「选择」。
* 我们要穷举所有「状态」，穷举的目的是根据对应的「选择」更新状态。
* 听起来抽象，你只要记住「状态」和「选择」两个词就行，下面实操一下就很容易明白了。
* 
* ```text
* for 状态1 in 状态1的所有取值：
*     for 状态2 in 状态2的所有取值：
*         for ...
*             dp[状态1][状态2][...] = 择优(选择1，选择2...)
* ```
* 每天都有三种「选择」：买入、卖出、无操作，我们用 buy, sell, rest
* 表示这三种选择。
* 
* 但问题是，并不是每天都可以任意选择这三种选择的，因为 sell 必须在 buy 之后，
* buy 必须在 sell 之后。那么 rest 操作还应该分两种状态，
* 一种是 buy 之后的 rest（持有了股票），一种是 sell 之后的 rest（没有持有股票）。
* 而且别忘了，我们还有交易次数 k 的限制，就是说你 buy 还只能在 k > 0
* 的前提下操作。
* 
* 这个问题的「状态」有三个，第一个是天数，第二个是允许交易的最大次数，
* 第三个是当前的持有状态（即之前说的 rest 的状态，我们不妨用 1 表示持有，0
* 表示没有持有）。 然后我们用一个三维数组就可以装下这几种状态的全部组合：
* 
* ```
* dp[i][k][0 or 1]
* 0 <= i <= n - 1, 1 <= k <= K
* n 为天数，大 K 为交易数的上限，0 和 1 代表是否持有股票。
* 此问题共 n × K × 2 种状态，全部穷举就能搞定。
* 
* for 0 <= i < n:
*     for 1 <= k <= K:
*         for s in {0, 1}:
*             dp[i][k][s] = max(buy, sell, rest)
* ```
* 
* 而且我们可以用自然语言描述出每一个状态的含义，比如说 dp[3][2][1] 的含义就是：
* 今天是第三天，我现在手上持有着股票，至今最多进行 2 次交易。再比如 dp[2][3][0]
* 的含义： 今天是第二天，我现在手上没有持有股票，至今最多进行 3 次交易。
* 
* 我们想求的最终答案是 dp[n - 1][K][0]，即最后一天，最多允许 K
* 次交易，最多获得多少利润。
* 
* 读者可能问为什么不是 dp[n - 1][K][1]？因为 dp[n - 1][K][1]
* 代表到最后一天手上还持有股票， dp[n - 1][K][0]
* 表示最后一天手上的股票已经卖出去了，很显然后者得到的利润一定大于前者。
* 
* 我们来写一下状态转移方程：
* 
* dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
*               max( 今天选择 rest,        今天选择 sell       )
* 
* 解释：今天我没有持有股票，有两种可能，我从这两种可能中求最大利润：
* 
* 1、我昨天就没有持有，且截至昨天最大交易次数限制为 k；然后我今天选择
* rest，所以我今天还是没有持有，最大交易次数限制依然为 k。
* 
* 2、我昨天持有股票，且截至昨天最大交易次数限制为 k；但是今天我 sell
* 了，所以我今天没有持有股票了，最大交易次数限制依然为 k。
* 
* dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
*               max( 今天选择 rest,         今天选择 buy         )
* 
* 解释：今天我持有着股票，最大交易次数限制为
* k，那么对于昨天来说，有两种可能，我从这两种可能中求最大利润：
* 
* 1、我昨天就持有着股票，且截至昨天最大交易次数限制为 k；然后今天选择
* rest，所以我今天还持有着股票，最大交易次数限制依然为 k。
* 
* 2、我昨天本没有持有，且截至昨天最大交易次数限制为 k - 1；但今天我选择
* buy，所以今天我就持有股票了，最大交易次数限制为 k。
* 
* 这个解释应该很清楚了，如果 buy，就要从利润中减去 prices[i]，如果
* sell，就要给利润增加 prices[i]。今天的最大利润就是这两种可能选择中较大的那个。
* 
* 现在，我们已经完成了动态规划中最困难的一步：状态转移方程。如果之前的内容你都可以理解，那么你已经可以秒杀所有问题了，
* 只要套这个框架就行了。不过还差最后一点点，就是定义 base case，即最简单的情况。
* 
* ```
* dp[-1][...][0] = 0
* 解释：因为 i 是从 0 开始的，所以 i = -1 意味着还没有开始，这时候的利润当然是 0。
* 
* dp[-1][...][1] = -infinity
* 解释：还没开始的时候，是不可能持有股票的。
* 因为我们的算法要求一个最大值，所以初始值设为一个最小值，方便取最大值。
* 
* dp[...][0][0] = 0
* 解释：因为 k 是从 1 开始的，所以 k = 0 意味着根本不允许交易，这时候利润当然是
* 0。
* 
* dp[...][0][1] = -infinity
* 解释：不允许交易的情况下，是不可能持有股票的。
* 因为我们的算法要求一个最大值，所以初始值设为一个最小值，方便取最大值。
* ```
* 
* 把上面的状态转移方程总结一下：
* 
* ```
* base case：
* dp[-1][...][0] = dp[...][0][0] = 0
* dp[-1][...][1] = dp[...][0][1] = -infinity
* 
* 状态转移方程：
* dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
* dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
* ```
* 
*/
class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int N = prices.size();
    vector<vector<int>> dp(N + 1, vector<int>(2));
    dp[0][0] = 0;
    dp[0][1] = -prices[0];
    for (int i = 1; i <= N; i++) {
      dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1]);
      // dp[i-1][k-1][0] = 0
      dp[i][1] = max(dp[i - 1][1], -prices[i - 1]);
    }
    print2D(dp);
    return dp[N][0];
  }
};
```

-------------

## 买卖股票的最佳时机 II

给你一个整数数组 `prices` ，其中 `prices[i]` 表示某支股票第 `i` 天的价格。
在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。
返回 你能获得的 最大 利润 。

示例 1：

```

输入：prices = [7,1,5,3,6,4]
输出：7
解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。
     随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6 - 3 = 3 。
     总利润为 4 + 3 = 7 。
```

示例 2：

```

输入：prices = [1,2,3,4,5]
输出：4
解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。
     总利润为 4 。
```

示例 3：

```

输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 交易无法获得正利润，所以不参与交易可以获得最大利润，最大利润为 0 。
```

提示：

* `1 <= prices.length <= 3 * 104`
* `0 <= prices[i] <= 104`

```cpp
/*
* dp[n][k][1] 的含义就是：
* 今天是第n天，至今最多进行 k 次交易 并且我现在手上持有着股票。
* 再比如 dp[n][k][0]:
* 今天是第n天，至今最多进行 k 次交易 并且我现在手上没有股票。
* 
* ```
* base case：
* dp[-1][...][0] = dp[...][0][0] = 0
* dp[-1][...][1] = dp[...][0][1] = -infinity
* 
* 状态转移方程：
* dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
* dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
* ```
* 
* This problem k is Infinity, so k - 1 = k = infinity.
* dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
* dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])
*/
class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int N = prices.size();
    vector<vector<int>> dp(N + 1, vector<int>(2));
    dp[0][0] = 0;
    dp[0][1] = -prices[0];
    for (int i = 1; i <= N; i++) {
      dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i - 1]);
      dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i - 1]);
    }
    // print2D(dp);
    return dp[N][0];
  }
};
```

-------------

## 买卖股票的最佳时机 III

给定一个数组，它的第`i` 个元素是一支给定的股票在第 `i`天的价格。
设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔交易。
注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

示例 1:

```

输入：prices = [3,3,5,0,0,3,1,4]
输出：6
解释：在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。
     随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3 。
```

示例 2：

```

输入：prices = [1,2,3,4,5]
输出：4
解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。   
     注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。   
     因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。

```

示例 3：

```

输入：prices = [7,6,4,3,1] 
输出：0 
解释：在这个情况下, 没有交易完成, 所以最大利润为 0。
```

示例 4：

```

输入：prices = [1]
输出：0

```

提示：

* `1 <= prices.length <= 105`
* `0 <= prices[i] <= 105`

```cpp
/*
* dp[n][k][1] 的含义就是：
* 今天是第n天，至今最多进行 k 次交易 并且我现在手上持有着股票。
* 再比如 dp[n][k][0]:
* 今天是第n天，至今最多进行 k 次交易 并且我现在手上没有股票。
* 
* ```
* base case：
* dp[-1][...][0] = dp[...][0][0] = 0
* dp[-1][...][1] = dp[...][0][1] = -infinity
* 
* 状态转移方程：
* dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
* dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
* ```
* 
*/
class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int N = prices.size();
    int K = 2;
    vector<vector<vector<int>>> dp(N + 1,
                                   vector<vector<int>>(K + 1, vector<int>(2)));

    for (int k = 0; k <= K; k++) {
      dp[0][k][0] = 0;
      dp[0][k][1] = -prices[0];
    }

    for (int i = 1; i <= N; i++) {
      for (int k = 1; k <= K; k++) {
        dp[i][k][0] = max(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i - 1]);
        dp[i][k][1] = max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices[i - 1]);
      }
    }
    return dp[N][K][0];
  }
};
```

-------------

## 买卖股票的最佳时机含冷冻期

给定一个整数数组`prices`，其中第 `prices[i]` 表示第 `i` 天的股票价格 。​
设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

* 卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

示例 1:

```

输入: prices = [1,2,3,0,2]
输出: 3 
解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]
```

示例 2:

```

输入: prices = [1]
输出: 0

```

提示：

* `1 <= prices.length <= 5000`
* `0 <= prices[i] <= 1000`

```cpp
/*
 * dp[n][k][1] 的含义就是：
 * 今天是第n天，至今最多进行 k 次交易 并且我现在手上持有着股票。
 * 再比如 dp[n][k][0]:
 * 今天是第n天，至今最多进行 k 次交易 并且我现在手上没有股票。
 *
 * ```
 * base case：
 * dp[-1][...][0] = dp[...][0][0] = 0
 * dp[-1][...][1] = dp[...][0][1] = -infinity
 *
 * 状态转移方程：
 * dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
 * dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
 * ```
 * This problem k is Infinity, so k - 1 = k = infinity.
 * But we have a cool down time (S + 1)
 * dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
 * dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i])
 *                              ^
 *                            这里表明了 T + 1 这个概念
 */
class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int N = prices.size();
    vector<vector<int>> dp(N + 1, vector<int>(2));
    dp[0][0] = 0;
    dp[0][1] = -prices[0];
    for (int i = 1; i <= N; i++) {
      dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1]);
      if (i - 2 >= 0)
        dp[i][1] = max(dp[i - 1][1], dp[i - 2][0] - prices[i - 1]);
      else
        dp[i][1] = dp[i - 1][1];
    }
    // print2D(dp);
    return dp[N][0];
  }
};
```

-------------

## 买卖股票的最佳时机含手续费

给定一个整数数组 `prices`，其中 `prices[i]`表示第 `i` 天的股票价格 ；整数 `fee` 代表了交易股票的手续费用。
你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。
返回获得利润的最大值。
注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。

示例 1：

```

输入：prices = [1, 3, 2, 8, 4, 9], fee = 2
输出：8
解释：能够达到的最大利润:  
在此处买入 prices[0] = 1
在此处卖出 prices[3] = 8
在此处买入 prices[4] = 4
在此处卖出 prices[5] = 9
总利润: ((8 - 1) - 2) + ((9 - 4) - 2) = 8
```

示例 2：

```

输入：prices = [1,3,7,5,10,3], fee = 3
输出：6

```

提示：

* `1 <= prices.length <= 5 * 104`
* `1 <= prices[i] < 5 * 104`
* `0 <= fee < 5 * 104`

```cpp
/*
 * dp[n][k][1] 的含义就是：
 * 今天是第n天，至今最多进行 k 次交易 并且我现在手上持有着股票。
 * 再比如 dp[n][k][0]:
 * 今天是第n天，至今最多进行 k 次交易 并且我现在手上没有股票。
 *
 * ```
 * base case：
 * dp[-1][...][0] = dp[...][0][0] = 0
 * dp[-1][...][1] = dp[...][0][1] = -infinity
 *
 * 状态转移方程：
 * dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
 * dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
 * ```
 *
 * This problem k is Infinity, so k - 1 = k = infinity.
 * dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
 * dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])
 * Here we need to be charge the transaction fee for every order.
 * only if we buy the stock and pay the fee. so:
 * dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
 * dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i] - fee)
 */
class Solution {
 public:
  int maxProfit(vector<int>& prices, int fee) {
    int N = prices.size();
    vector<vector<int>> dp(N + 1, vector<int>(2));
    dp[0][0] = 0;
    dp[0][1] = -prices[0] - fee;
    for (int i = 1; i <= N; i++) {
      dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1]);
      dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i - 1] - fee);
    }
    // print2D(dp);
    return dp[N][0];
  }
};
```

-------------

## 买卖股票的最佳时机 IV

给你一个整数数组 `prices` 和一个整数 `k` ，其中 `prices[i]` 是某支给定的股票在第 `i`天的价格。
设计一个算法来计算你所能获取的最大利润。你最多可以完成 `k` 笔交易。也就是说，你最多可以买 `k` 次，卖 `k` 次。
注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

示例 1：

```

输入：k = 2, prices = [2,4,1]
输出：2
解释：在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4) 的时候卖出，这笔交易所能获得利润 = 4-2 = 2 。
```

示例 2：

```

输入：k = 2, prices = [3,2,6,5,0,3]
输出：7
解释：在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6) 的时候卖出, 这笔交易所能获得利润 = 6-2 = 4 。
     随后，在第 5 天 (股票价格 = 0) 的时候买入，在第 6 天 (股票价格 = 3) 的时候卖出, 这笔交易所能获得利润 = 3-0 = 3 。
```

提示：

* `1 <= k <= 100`
* `1 <= prices.length <= 1000`
* `0 <= prices[i] <= 1000`

```cpp
/*
 * dp[n][k][1] 的含义就是：
 * 今天是第n天，至今最多进行 k 次交易 并且我现在手上持有着股票。
 * 再比如 dp[n][k][0]:
 * 今天是第n天，至今最多进行 k 次交易 并且我现在手上没有股票。
 *
 * ```
 * base case：
 * dp[-1][...][0] = dp[...][0][0] = 0
 * dp[-1][...][1] = dp[...][0][1] = -infinity
 *
 * 状态转移方程：
 * dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
 * dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
 * ```
 *
 */
class Solution {
 public:
  int maxProfit(int K, vector<int>& prices) {
    int N = prices.size();
    vector<vector<vector<int>>> dp(N + 1,
                                   vector<vector<int>>(K + 1, vector<int>(2)));

    for (int k = 0; k <= K; k++) {
      dp[0][k][0] = 0;
      dp[0][k][1] = -prices[0];
    }

    for (int i = 1; i <= N; i++) {
      for (int k = 1; k <= K; k++) {
        dp[i][k][0] = max(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i - 1]);
        dp[i][k][1] = max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices[i - 1]);
      }
    }
    return dp[N][K][0];
  }
};
```

-------------

## 两数之和 II - 输入有序数组

给你一个下标从 1 开始的整数数组 `numbers` ，该数组已按非递减顺序排列 ，请你从数组中找出满足相加之和等于目标数 `target` 的两个数。如果设这两个数分别是 `numbers[index1]` 和 `numbers[index2]` ，则 `1 <= index1 < index2 <= numbers.length` 。
以长度为 2 的整数数组 `[index1, index2]` 的形式返回这两个整数的下标 `index1`和`index2`。
你可以假设每个输入 只对应唯一的答案 ，而且你 不可以 重复使用相同的元素。
你所设计的解决方案必须只使用常量级的额外空间。

示例 1：

```

输入：numbers = [2,7,11,15], target = 9
输出：[1,2]
解释：2 与 7 之和等于目标数 9 。因此 index1 = 1, index2 = 2 。返回 [1, 2] 。
```

示例 2：

```

输入：numbers = [2,3,4], target = 6
输出：[1,3]
解释：2 与 4 之和等于目标数 6 。因此 index1 = 1, index2 = 3 。返回 [1, 3] 。
```

示例 3：

```

输入：numbers = [-1,0], target = -1
输出：[1,2]
解释：-1 与 0 之和等于目标数 -1 。因此 index1 = 1, index2 = 2 。返回 [1, 2] 。

```

提示：

* `2 <= numbers.length <= 3 * 104`
* `-1000 <= numbers[i] <= 1000`
* `numbers` 按 非递减顺序 排列
* `-1000 <= target <= 1000`
* 仅存在一个有效答案

```cpp
// sorted List for nums
// 双指针算法
class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    // 左右指针
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
      int sum = nums[lo] + nums[hi];
      // 根据 sum 和 target 的比较，移动左右指针
      if (sum < target) {
        lo++;
      } else if (sum > target) {
        hi--;
      } else if (sum == target) {
        return {lo + 1, hi + 1};
      }
    }
    return {};
  }
};
```
