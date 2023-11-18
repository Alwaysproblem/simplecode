/*
 * @lc app=leetcode.cn id=921 lang=cpp
 *
 * [921] 使括号有效的最少添加
 * title: minimum-add-to-make-parentheses-valid
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
// @lc code=end

int main() {
  string s = "()))((";
  Solution sol;
  auto v = sol.minAddToMakeValid(s);
  fmt::print("{}\n", v);
  return 0;
}
