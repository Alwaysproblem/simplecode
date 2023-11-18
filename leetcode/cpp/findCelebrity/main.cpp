/*
 * @lc app=leetcode.cn id=997 lang=cpp
 *
 * [997] 找到小镇的法官
 * title: find-the-town-judge
 */

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
 public:
  int knows_cnt = 0;
  vector<vector<int>> graph;
  void buildGraph(int n, vector<vector<int>> trust) {
    int cand = 0;
    int other = 0;
    graph = vector<vector<int>>(n + 1, vector<int>(n + 1));
    for (auto& t : trust) {
      cand = t[0];
      other = t[1];
      graph[cand][other] = 1;
    }
  }

  int knows(int i, int j) {
    knows_cnt += 1;
    return graph[i][j];
  }

  int findJudge(int n, vector<vector<int>>& trust) {
    buildGraph(n, trust);
    int cand = 1;
    for (int other = 1; other <= n; other++) {
      // if candidate knows other, the candidate is not the
      // celebrity. or if others do no know the candidate,
      // then the candidate will not be the celebrity.
      // the candidate should not change in the other situation.
      if (knows(cand, other) || !knows(other, cand)) {
        cand = other;
      }
    }
    // we need to validate the candidate is celebrity.
    for (int i = 1; i <= n; i++) {
      if (cand != i) {
        if (!knows(i, cand) || knows(cand, i)) {
          return -1;
        }
      }
    }
    return cand;
  }
};
// @lc code=end

int main() {
  vector<vector<int>> trust = {{1, 2}};
  int n = 2;
  Solution sol;
  auto v = sol.findJudge(n, trust);
  fmt::print("{}\n", v);
  fmt::print("{}\n", sol.knows_cnt);
  return 0;
}
