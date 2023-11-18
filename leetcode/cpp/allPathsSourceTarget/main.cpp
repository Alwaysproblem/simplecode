/*
 * @lc app=leetcode.cn id=797 lang=cpp
 *
 * [797] 所有可能的路径
 * title: all-paths-from-source-to-target
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

// @lc code=end

int main() {
  Solution s;
  // vector<vector<int>> graph = {{2}, {}, {1}};
  vector<vector<int>> graph = {{4, 3, 1}, {3, 2, 4}, {}, {4}, {}};
  // vector<vector<int>> graph = {{4, 3, 1}, {3, 2, 4}, {3}, {4}, {}};
  vector<vector<int>> res = s.allPathsSourceTarget(graph);
  fmt::print("{}\n", res);
  return 0;
}
