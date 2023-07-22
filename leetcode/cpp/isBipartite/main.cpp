/*
 * @lc app=leetcode.cn id=785 lang=cpp
 *
 * [785] 判断二分图
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
// @lc code=end

int main() {
  vector<vector<int>> graph = {{1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2}};
  Solution sol;
  auto v = sol.isBipartite(graph);
  fmt::print("{}\n", v);
  return 0;
}
