/*
 * @lc app=leetcode.cn id=20 lang=cpp
 *
 * [20] 有效的括号
 * title: valid-parentheses
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
// @lc code=end

int main() {
  string s = "((())){[}";
  Solution sol;
  auto v = sol.isValid(s);
  fmt::print("{}\n", v);
  return 0;
}
